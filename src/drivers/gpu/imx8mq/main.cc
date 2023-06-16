/*
 * \brief  i.MX8 Vivante GPU driver Linux port
 * \author Josef Soentgen
 * \date   2021-10-28
 */

/*
 * Copyright (C) 2021 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

/* Genode includes */
#include <base/attached_ram_dataspace.h>
#include <base/attached_rom_dataspace.h>
#include <base/component.h>
#include <base/env.h>
#include <base/heap.h>
#include <base/id_space.h>
#include <base/session_object.h>
#include <base/signal.h>
#include <base/sleep.h>
#include <gpu/info_etnaviv.h>
#include <gpu_session/gpu_session.h>
#include <root/component.h>
#include <session/session.h>

/* emulation includes */
#include <lx_emul/init.h>
#include <lx_emul/task.h>
#include <lx_kit/env.h>
#include <lx_kit/init.h>


/* local includes */
#include "lx_drm.h"

extern Genode::Dataspace_capability genode_lookup_cap(void *, unsigned long long, unsigned long);

namespace Gpu {

	using namespace Genode;

	struct Session_component;
	struct Root;

	using Root_component = Genode::Root_component<Session_component, Genode::Single_client>;

	struct Operation;
	struct Request;
	struct Local_request;

	struct Buffer_space;
	struct Worker_args;

	struct Buffer;
	using Buffer_id = Vram_id;
} /* namespace Gpu */

struct Gpu::Vram { };

struct Gpu::Operation
{
	enum class Type {
		INVALID = 0,
		ALLOC   = 1,
		FREE    = 2,
		MAP     = 3,
		UNMAP   = 4,
		EXEC    = 5,
		WAIT    = 6,
	};

	Type type;

	Virtual_address gpu_vaddr;
	unsigned        mode;

	uint32_t           size;
	Buffer_id          id;
	Sequence_number    seqno;
	Mapping_attributes mapping_attrs;

	int lx_mapping_attrs() const
	{
		if (mapping_attrs.readable)
			return 1;
		else

		if (mapping_attrs.writeable)
			return 2;

		return 0;
	}

	bool valid() const
	{
		return type != Type::INVALID;
	}

	static char const *type_name(Type type)
	{
		switch (type) {
		case Type::INVALID: return "INVALID";
		case Type::ALLOC:   return "ALLOC";
		case Type::FREE:    return "FREE";
		case Type::MAP:     return "MAP";
		case Type::UNMAP:   return "UNMAP";
		case Type::EXEC:    return "EXEC";
		case Type::WAIT:    return "WAIT";
		}
		return "INVALID";
	}

	void print(Genode::Output &out) const
	{
		Genode::print(out, type_name(type));
	}
};


struct Gpu::Request
{
	struct Tag { unsigned long value; };

	Operation operation;

	bool success;

	Tag tag;

	bool valid() const
	{
		return operation.valid();
	}

	void print(Genode::Output &out) const
	{
		Genode::print(out, "tag=",       tag.value, " "
		                   "success=",   success,   " "
		                   "operation=", operation);
	}

	static Gpu::Request create(Operation::Type type)
	{
		static unsigned long tag_counter = 0;

		return Gpu::Request {
			.operation = Operation {
				.type = type,
				.gpu_vaddr = Gpu::Virtual_address { 0 },
				.mode = 0,
				.size = 0,
				.id = Buffer_id { .value = 0 },
				.seqno = Sequence_number { .value = 0 },
				.mapping_attrs = Mapping_attributes::ro(),
			},
			.success = false,
			.tag = Tag { ++tag_counter }
		};
	}

	bool matches(Gpu::Request const &r) const
	{
		return tag.value == r.tag.value;
	}
};


struct Gpu::Local_request
{
	enum class Type { INVALID = 0, OPEN, CLOSE };
	Type type;
	bool success;
};


struct Gpu::Buffer : Vram
{
	Vram_id_space::Element const _elem;

	uint32_t             const handle;
	Dataspace_capability const cap;
	Attached_dataspace         attached_ds;

	Buffer(Vram_id_space   &space,
	       Gpu::Buffer_id  id,
	       uint32_t        handle,
	       Dataspace_capability cap,
	       Region_map &rm)
	:
		_elem       { *this, space, id },
		handle      { handle },
		cap         { cap },
		attached_ds { rm, cap }
	{ }

};


extern "C" void lx_emul_mem_cache_clean_invalidate(const void * addr,
                                                   unsigned long size);

struct Gpu::Buffer_space : Vram_id_space
{
	Allocator &_alloc;

	Buffer_space(Allocator &alloc) : _alloc { alloc } { }

	~Buffer_space() { }

	void *local_addr(Gpu::Buffer_id id)
	{
		void *local_addr = nullptr;
		apply<Buffer>(id, [&] (Buffer &b) {
			local_addr = b.attached_ds.local_addr<void>();
		});

		return local_addr;
	}

	struct Lx_handle
	{
		uint32_t value;
		bool     _valid;

		bool valid() const { return _valid; }
	};

	Lx_handle lookup_and_flush(Gpu::Buffer_id id)
	{
		Lx_handle result { 0, false };

		apply<Buffer>(id, [&] (Buffer &b) {

			lx_emul_mem_cache_clean_invalidate(b.attached_ds.local_addr<void>(),
			                                   b.attached_ds.size());

			result = { b.handle, true };
		});

		return result;
	}

	void insert(Gpu::Buffer_id id, uint32_t handle,
	            Dataspace_capability cap, Region_map &rm)
	{
		// XXX assert id is not assosicated with other handle and
		//     handle is not already present in registry
		new (&_alloc) Buffer(*this, id, handle, cap, rm);
	}

	void remove(Gpu::Buffer_id id)
	{
		bool removed = false;
		apply<Buffer>(id, [&] (Buffer &b) {
			destroy(_alloc, &b);
			removed = true;
		});

		if (!removed)
			Genode::warning("could not remove buffer with id: ", id.value,
			                " - not present in registry");
	}

	Dataspace_capability lookup_buffer(Gpu::Buffer_id id)
	{
		Dataspace_capability cap { };
		apply<Buffer>(id, [&] (Buffer const &b) {
			cap = b.cap;
		});
		return cap;
	}

	template <typename FN>
	void with_handle(Gpu::Buffer_id id, FN const &fn)
	{
		apply<Buffer>(id, [&] (Buffer const &b) {
			fn(b.handle);
		});
	}

	bool managed(Gpu::Buffer_id id)
	{
		bool result = false;
		apply<Buffer>(id, [&] (Buffer const &) {
			result = true;
		});
		return result;
	}
};


struct Gpu::Worker_args
{
	Region_map *rm;

	Gpu::Request *pending_request;
	Gpu::Request *completed_request;

	Gpu::Local_request *local_request;
	void *drm;

	Gpu::Info_etnaviv *info;

	Buffer_space *buffers;

	void *gem_submit;

	bool valid() const
	{
		return buffers != nullptr && info != nullptr;
	}

	template <typename FN> void for_each_pending_request(FN const &fn)
	{
		if (!pending_request || !pending_request->valid()) {
			return;
		}

		*completed_request = fn(*pending_request);
		*pending_request   = Gpu::Request();
	}
};


static int _populate_info(void *drm, Gpu::Info_etnaviv &info)
{
	for (Gpu::Info_etnaviv::Param &p : info.param)
		p = 0;

	Genode::uint8_t params[] = {
		0xff, /* 0x00 inv */
		0x01, /* ETNAVIV_PARAM_GPU_MODEL      */
		0x02, /* ETNAVIV_PARAM_GPU_REVISION   */
		0x03, /* ETNAVIV_PARAM_GPU_FEATURES_0 */
		0x04, /* ETNAVIV_PARAM_GPU_FEATURES_1 */
		0x05, /* ETNAVIV_PARAM_GPU_FEATURES_2 */
		0x06, /* ETNAVIV_PARAM_GPU_FEATURES_3 */
		0x07, /* ETNAVIV_PARAM_GPU_FEATURES_4 */
		0x08, /* ETNAVIV_PARAM_GPU_FEATURES_5 */
		0x09, /* ETNAVIV_PARAM_GPU_FEATURES_6 */
		0x0a, /* ETNAVIV_PARAM_GPU_FEATURES_7 */
		0xff, /* 0x0b inv */
		0xff, /* 0x0c inv */
		0xff, /* 0x0d inv */
		0xff, /* 0x0e inv */
		0xff, /* 0x0f inv */
		0x10, /* ETNAVIV_PARAM_GPU_STREAM_COUNT              */
		0x11, /* ETNAVIV_PARAM_GPU_REGISTER_MAX              */
		0x12, /* ETNAVIV_PARAM_GPU_THREAD_COUNT              */
		0x13, /* ETNAVIV_PARAM_GPU_VERTEX_CACHE_SIZE         */
		0x14, /* ETNAVIV_PARAM_GPU_SHADER_CORE_COUNT         */
		0x15, /* ETNAVIV_PARAM_GPU_PIXEL_PIPES               */
		0x16, /* ETNAVIV_PARAM_GPU_VERTEX_OUTPUT_BUFFER_SIZE */
		0x17, /* ETNAVIV_PARAM_GPU_BUFFER_SIZE               */
		0x18, /* ETNAVIV_PARAM_GPU_INSTRUCTION_COUNT         */
		0x19, /* ETNAVIV_PARAM_GPU_NUM_CONSTANTS             */
		0x1a, /* ETNAVIV_PARAM_GPU_NUM_VARYINGS              */
		0x1b, /* ETNAVIV_PARAM_SOFTPIN_START_ADDR            */
		0xff, /* 0x1c inv */
		0xff, /* 0x1d inv */
		0xff, /* 0x1e inv */
		0xff, /* 0x1f inv */
	};

	static_assert(sizeof(params)/sizeof(params[0]) == 32);

	for (int p = 0; p < 32; p++) {

		if (params[p] == 0xff) {
			continue;
		}

		Genode::uint64_t value;
		int const err = lx_drm_ioctl_etnaviv_gem_param(drm, params[p], &value);
		if (err) {
			return -1;
		}

		info.param[p] = value;
	}
	return 0;
}


static Gpu::Worker_args    _worker_args;
extern struct task_struct *_lx_user_task;


extern "C" void *lx_user_task_args;


extern "C" int run_lx_user_task(void *p)
{
	Gpu::Worker_args &args = *static_cast<Gpu::Worker_args*>(p);

	using namespace Genode;
	using OP = Gpu::Operation::Type;

	while (true) {

		/* wait until we have a valid session */
		if (!args.valid()) {
			lx_emul_task_schedule(true);
			continue;
		}

		Gpu::Buffer_space &buffers = *args.buffers;
		Region_map        &rm      = *args.rm;

		/* handle local requests first */
		if (args.local_request) {
			args.local_request->success = false;
			switch (args.local_request->type) {
			case Gpu::Local_request::Type::OPEN:
				if (!args.drm) {
					args.drm = lx_drm_open();
					if (!args.drm)
						break;

					_populate_info(args.drm, *args.info);

					args.local_request->success = true;
				}
				break;
			case Gpu::Local_request::Type::CLOSE:
				lx_drm_close(args.drm);
				args.drm = nullptr;
				args.local_request->success = true;
				break;
			case Gpu::Local_request::Type::INVALID:
				break;
			}
		}

		auto dispatch_pending = [&] (Gpu::Request r) {

			/* clear request result */
			r.success = false;

			switch (r.operation.type) {
			case OP::ALLOC:
			{
				uint32_t const size = r.operation.size;
				uint32_t handle;

				int err =
					lx_drm_ioctl_etnaviv_gem_new(args.drm, size, &handle);
				if (err) {
					error("lx_drm_ioctl_etnaviv_gem_new failed: ", err);
					break;
				}

				unsigned long long offset;
				err = lx_drm_ioctl_etnaviv_gem_info(args.drm, handle, &offset);
				if (err) {
					error("lx_drm_ioctl_etnaviv_gem_info failed: ", err);
					lx_drm_ioctl_gem_close(args.drm, handle);
					break;
				}

				Dataspace_capability cap =
					genode_lookup_cap(args.drm, offset, size);
				buffers.insert(r.operation.id, handle, cap, rm);

				r.success = true;
				break;
			}
			case OP::FREE:
			{
				bool found = false;
				buffers.with_handle(r.operation.id, [&] (uint32_t const handle) {
					(void)lx_drm_ioctl_gem_close(args.drm, handle);
					found = true;
				});

				if (found) {
					buffers.remove(r.operation.id);
					r.success = true;
				}
				break;
			}
			case OP::EXEC:
			{
				void *gem_submit = buffers.local_addr(r.operation.id);
				if (!gem_submit)
					break;

				int err = 0;
				unsigned nr_bos = lx_drm_gem_submit_bo_count(gem_submit);
				for (unsigned i = 0; i < nr_bos; i++) {
					unsigned *bo_handle = lx_drm_gem_submit_bo_handle(gem_submit, i);
					if (!bo_handle) {
						error("lx_drm_gem_submit_bo_handle: index: ", i,
						       " invalid bo handle");
						err = -1;
						break;
					}
					using LX = Gpu::Buffer_space::Lx_handle;
					Gpu::Buffer_id id { .value = *bo_handle };
					LX handle = buffers.lookup_and_flush(id);
					if (!handle.valid()) {
						error("could not look up handle for id: ", *bo_handle);
						err = -1;
						break;
					}
					/* replace client-local buffer id with kernel-local handle */
					*bo_handle = handle.value;
				}

				Genode::uint32_t fence_id;
				if (!err)
					err = lx_drm_ioctl_etnaviv_gem_submit(args.drm,
					                                     (unsigned long)gem_submit,
					                                     &fence_id);
				if (err) {
					error("lx_drm_ioctl_etnaviv_gem_submit: ", err);
					break;
				}

				r.operation.seqno.value = fence_id;
				r.success = true;

				break;
			}
			case OP::WAIT:
			{
				uint32_t const fence_id = (uint32_t) r.operation.seqno.value;

				if (lx_drm_ioctl_etnaviv_wait_fence(args.drm, fence_id))
					break;

				r.success = true;
				break;
			}
			case OP::MAP:
			{
				buffers.with_handle(r.operation.id, [&] (uint32_t const handle) {
					int const attrs  = r.operation.lx_mapping_attrs();

					if (lx_drm_ioctl_etnaviv_cpu_prep(args.drm, handle, attrs))
						return;

					r.success = true;
				});
				break;
			}
			case OP::UNMAP:
			{
				buffers.with_handle(r.operation.id, [&] (uint32_t const handle) {
					(void)lx_drm_ioctl_etnaviv_cpu_fini(args.drm, handle);
					r.success = true;
				});
				break;
			}
			default:
			break;
			}

			/* return completed request */
			return r;
		};

		args.for_each_pending_request(dispatch_pending);

		lx_emul_task_schedule(true);
	}
}


static void request_already_pending(Gpu::Request const&, Gpu::Request const&) __attribute__((noreturn));
static void request_already_pending(Gpu::Request const &p,
                                    Gpu::Request const &r)
{
	Genode::error("there is already a request pending: ", p,
	              ", cannot schedule request: ", r);
	Genode::sleep_forever();
}


struct Gpu::Session_component : public Genode::Session_object<Gpu::Session>
{
	private:

		Session_component(Session_component const&) = delete;
		Session_component& operator=(Session_component const&) = delete;

		Genode::Env        &_env;
		Genode::Entrypoint &_ep;
		Genode::Heap        _alloc;

		Genode::Region_map &_rm { _env.rm() };

		Genode::Attached_ram_dataspace _info_dataspace {
			_env.ram(), _env.rm(), 4096 };

		Buffer_space _buffers { _alloc };

		Gpu::Info_etnaviv _info { };

		Genode::Signal_context_capability _completion_sigh { };

		char const *_name;

		Gpu::Request _pending_request   { };
		Gpu::Request _completed_request { };

		Gpu::Worker_args &_worker_args;

		bool _managed_id(Gpu::Request const &request)
		{
			using OP = Gpu::Operation::Type;

			switch (request.operation.type) {
			case OP::FREE:  [[fallthrough]];
			case OP::MAP:   [[fallthrough]];
			case OP::UNMAP: [[fallthrough]];
			case OP::EXEC:
				return _buffers.managed(request.operation.id);
			default:
				break;
			}

			return true;
		}

		template <typename SUCC_FN, typename FAIL_FN>
		void _schedule_request(Gpu::Request const &request,
		                       SUCC_FN const &succ_fn,
		                       FAIL_FN const &fail_fn)
		{
			if (_pending_request.valid()) {
				request_already_pending(_pending_request, request);
			}

			/*
			 * Requests referencing not managed handles will be
			 * treated as scheduled but failed.
			 */
			if (!_managed_id(request)) {
				fail_fn();
				return;
			}

			_pending_request = request;
			_worker_args.pending_request   = &_pending_request;
			_worker_args.completed_request = &_completed_request;

			lx_emul_task_unblock(_lx_user_task);
			Lx_kit::env().scheduler.execute();

			for (;;) {
				if (_completed_request.matches(request)
				 && _completed_request.valid())
					break;

				_ep.wait_and_dispatch_one_io_signal();
				Lx_kit::env().scheduler.execute();
			}

			if (_completed_request.success)
				succ_fn(_completed_request);
			else
				fail_fn();
		}

		bool _local_request(Gpu::Local_request::Type type)
		{
			Gpu::Local_request local_request {
				.type = type,
				.success = false,
			};
			_worker_args.local_request = &local_request;

			// XXX must not return prematurely
			lx_emul_task_unblock(_lx_user_task);
			Lx_kit::env().scheduler.schedule();

			bool const success = _worker_args.local_request->success;
			_worker_args.local_request = nullptr;

			return success;
		}

	public:

		struct Could_not_open_drm : Genode::Exception { };

		/**
		 * Constructor
		 */
		Session_component(Genode::Env        &env,
		                  Genode::Entrypoint &ep,
		                  Resources    const &resources,
		                  Label        const &label,
		                  Diag                diag,
		                  char         const *name,
		                  Gpu::Worker_args   &worker_args)
		:
			Session_object { ep, resources, label, diag },
			_env         { env },
			_ep          { ep },
			_alloc       { _env.ram(), _env.rm() },
			_name        { name },
			_worker_args { worker_args }
		{
			_worker_args.rm      = &_rm;
			_worker_args.info    = &_info;
			_worker_args.buffers = &_buffers;

			if (!_local_request(Gpu::Local_request::Type::OPEN)) {
				Genode::warning("could not open DRM session");
				throw Could_not_open_drm();
			}

			void *info = _info_dataspace.local_addr<void>();
			Genode::memcpy(info, &_info, sizeof (_info));
		}

		virtual ~Session_component()
		{
			if (_worker_args.pending_request->valid()) {
				Genode::warning("destructor override currently pending request");
			}

			if (!_local_request(Gpu::Local_request::Type::CLOSE))
				Genode::warning("could not close DRM session - leaking objects");
		}

		char const *name() { return _name; }

		void submit_completion_signal()
		{
			if (_completion_sigh.valid()) {
				Genode::Signal_transmitter(_completion_sigh).submit();
			}
		}

		/***************************
		 ** Gpu session interface **
		 ***************************/

		Genode::Dataspace_capability info_dataspace() const override
		{
			return _info_dataspace.cap();
		}

		Gpu::Sequence_number execute(Gpu::Vram_id id,
		                             Genode::off_t) override
		{
			Gpu::Request r = Gpu::Request::create(Gpu::Operation::Type::EXEC);
			r.operation.id = id;

			Gpu::Sequence_number seqno { .value = 0 };

			auto success = [&] (Gpu::Request const &request) {
				seqno = request.operation.seqno;
			};
			auto fail = [&] () {
				throw Invalid_state();
			};
			_schedule_request(r, success, fail);

			return seqno;
		}

		bool complete(Gpu::Sequence_number seqno) override
		{
			Gpu::Request r = Gpu::Request::create(Gpu::Operation::Type::WAIT);
			r.operation.seqno = seqno;

			bool completed = false;

			auto success = [&] (Gpu::Request const &request) {
				completed = request.success;
			};
			auto fail = [&] () { };
			_schedule_request(r, success, fail);

			return completed;
		}

		void completion_sigh(Genode::Signal_context_capability sigh) override
		{
			_completion_sigh = sigh;
		}

		Genode::Dataspace_capability alloc_vram(Gpu::Vram_id id,
		                                        Genode::size_t size) override
		{
			Genode::Dataspace_capability cap { };

			if (size > ~0U) {
				error("Allocation of buffers > 4G not supported!");
				return cap;
			}

			Gpu::Request r = Gpu::Request::create(Gpu::Operation::Type::ALLOC);
			r.operation.id   = id;
			r.operation.size = (uint32_t) size;

			auto success = [&] (Gpu::Request const &request) {
				cap = _buffers.lookup_buffer(request.operation.id);
			};
			auto fail = [&] () { };
			_schedule_request(r, success, fail);

			return cap;
		}

		void free_vram(Gpu::Vram_id id) override
		{
			Gpu::Request r = Gpu::Request::create(Gpu::Operation::Type::FREE);
			r.operation.id = id;

			auto success = [&] (Gpu::Request const &) { };
			auto fail = [&] () { };
			_schedule_request(r, success, fail);
		}

		Genode::Dataspace_capability map_cpu(Gpu::Vram_id id,
		                                     Gpu::Mapping_attributes attrs) override
		{
			Gpu::Request r = Gpu::Request::create(Gpu::Operation::Type::MAP);
			r.operation.id            = id;
			r.operation.mapping_attrs = attrs;

			Genode::Dataspace_capability cap { };

			auto success = [&] (Gpu::Request const &request) {
				cap = _buffers.lookup_buffer(request.operation.id);
			};
			auto fail = [&] () { };
			_schedule_request(r, success, fail);

			return cap;
		}

		void unmap_cpu(Gpu::Vram_id id) override
		{
			Gpu::Request r = Gpu::Request::create(Gpu::Operation::Type::UNMAP);
			r.operation.id = id;

			auto success = [&] (Gpu::Request const &) { };
			auto fail = [&] () { };
			_schedule_request(r, success, fail);
		}

		bool map_gpu(Gpu::Vram_id, Genode::size_t, Genode::off_t,
		             Gpu::Virtual_address) override
		{
			Genode::warning(__func__, ": not implemented");
			return false;
		}

		void unmap_gpu(Gpu::Vram_id, Genode::off_t, Gpu::Virtual_address) override
		{
			Genode::warning(__func__, ": not implemented");
		}

		bool set_tiling_gpu(Gpu::Vram_id, Genode::off_t, unsigned) override
		{
			Genode::warning(__func__, ": not implemented");
			return false;
		}

		Gpu::Vram_capability export_vram(Gpu::Vram_id) override
		{
			Genode::warning(__func__, ": not implemented");
			return Gpu::Vram_capability();
		}

		void import_vram(Gpu::Vram_capability, Gpu::Vram_id) override
		{
			Genode::warning(__func__, ": not implemented");
		}
};


struct Gpu::Root : Gpu::Root_component
{
	private:

		/*
		 * Noncopyable
		 */
		Root(Root const &) = delete;
		Root &operator = (Root const &) = delete;

		Genode::Env       &_env;
		Genode::Allocator &_alloc;

		uint32_t           _session_id;
		Session_component *_sc;

	protected:

		Session_component *_create_session(char const *args) override
		{
			if (_sc)
				throw Service_denied();

			char *name = (char*)_alloc.alloc(64);
			Genode::String<64> tmp("gpu_worker-", ++_session_id);
			Genode::memcpy(name, tmp.string(), tmp.length());

			Session::Label const label  { session_label_from_args(args) };

			_sc = new (_alloc) Session_component(_env, _env.ep(),
			                                      session_resources_from_args(args),
			                                      label,
			                                      session_diag_from_args(args),
			                                      name,
			                                      _worker_args);
			return _sc;
		}

		void _upgrade_session(Session_component *sc, char const *args) override
		{
			sc->upgrade(ram_quota_from_args(args));
			sc->upgrade(cap_quota_from_args(args));
		}

		void _destroy_session(Session_component *sc) override
		{
			char const *name = sc->name();

			Genode::destroy(_alloc, const_cast<char*>(name));
			Genode::destroy(md_alloc(), sc);
			_sc = nullptr;
		}

	public:

		Root(Genode::Env &env, Genode::Allocator &alloc)
		:
			Root_component { env.ep(), alloc },
			_env           { env },
			_alloc         { alloc },
			_session_id    { 0 },
			_sc            { nullptr }
		{ }

		void completion_signal()
		{
			if (!_sc)
				return;

			_sc->submit_completion_signal();
		}
};


static Genode::Constructible<Gpu::Root> _gpu_root { };


extern "C" void lx_emul_announce_gpu_session(void)
{
	if (!_gpu_root.constructed()) {
		_gpu_root.construct(Lx_kit::env().env, Lx_kit::env().heap);

		Genode::Entrypoint &ep = Lx_kit::env().env.ep();
		Lx_kit::env().env.parent().announce(ep.manage(*_gpu_root));
	}
}


namespace Driver {

	using namespace Genode;

	struct Main;
} /* namespace Driver */


struct Driver::Main
{
	Env                    &_env;
	Attached_rom_dataspace  _config_rom     { _env, "config" };

	using Dtb_name = Genode::String<64>;
	Dtb_name _dtb_name { _config_rom.xml().attribute_value("dtb", Dtb_name("dtb")) };

	Attached_rom_dataspace  _dtb_rom     { _env, _dtb_name.string() };

	Signal_handler<Main>    _signal_handler { _env.ep(), *this,
	                                          &Main::_handle_signal };
	Sliced_heap             _sliced_heap    { _env.ram(), _env.rm() };

	void _handle_signal()
	{
		Lx_kit::env().scheduler.execute();
	}

	Main(Env &env) : _env { env }
	{
		log("--- i.MX 8MQ GPU driver started ---");

		Lx_kit::initialize(_env);
		_env.exec_static_constructors();

		lx_user_task_args = &_worker_args;

		lx_emul_start_kernel(_dtb_rom.local_addr<void>());

		lx_emul_announce_gpu_session();
	}
};


void Component::construct(Genode::Env &env)
{
	static Driver::Main main(env);
}
