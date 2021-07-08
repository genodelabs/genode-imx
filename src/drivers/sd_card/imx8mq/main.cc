/*
 * \brief  i.MX8 SD-card driver Linux port
 * \author Stefan Kalkowski
 * \date   2021-06-29
 */

/*
 * Copyright (C) 2021 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#include <base/attached_rom_dataspace.h>
#include <base/component.h>
#include <base/env.h>

#include <lx_emul/init.h>
#include <lx_emul/page_virt.h>
#include <lx_kit/env.h>
#include <lx_kit/init.h>
#include <lx_user/io.h>

#include <genode_c_api/block.h>

using namespace Genode;
using Buffer = Lx_kit::Mem_allocator::Buffer;


extern "C" struct genode_attached_dataspace *
allocate_peer_buffer(size_t size)
{
	Buffer & buffer = Lx_kit::env().memory.alloc_buffer(size);

	/*
	 * We have to call virt_to_pages eagerly here,
	 * to get contingous page objects registered
	 */
	lx_emul_virt_to_pages(buffer.local_addr<void>(), size >> 12);
	return genode_attached_dataspace_ptr(buffer);
}


extern "C" void free_peer_buffer(struct genode_attached_dataspace * ptr)
{
	Attached_dataspace * ds =  static_cast<Attached_dataspace*>(ptr);
	Lx_kit::env().memory.free(*static_cast<Buffer*>(ds));
}


struct Main : private Entrypoint::Io_progress_handler
{
	Env                  & env;
	Attached_rom_dataspace dtb_rom        { env, "dtb"           };
	Signal_handler<Main>   signal_handler { env.ep(), *this,
	                                        &Main::handle_signal };
	Sliced_heap            sliced_heap    { env.ram(), env.rm()  };

	/**
	 * Entrypoint::Io_progress_handler
	 */
	void handle_io_progress() override
	{
		genode_block_notify_peers();
	}

	void handle_signal()
	{
		lx_user_handle_io();
		Lx_kit::env().scheduler.schedule();
	}

	Main(Env & env) : env(env)
	{
		Lx_kit::initialize(env);

		genode_block_init(genode_env_ptr(env),
		                  genode_allocator_ptr(sliced_heap),
		                  genode_signal_handler_ptr(signal_handler),
		                  allocate_peer_buffer, free_peer_buffer);

		lx_emul_start_kernel(dtb_rom.local_addr<void>());

		env.ep().register_io_progress_handler(*this);
	}
};


void Component::construct(Env & env) {
	static Main main(env); }
