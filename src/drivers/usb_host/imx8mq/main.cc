/*
 * \brief  i.MX8 USB-card driver Linux port
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

#include <usb.h>


using namespace Genode;


extern "C" struct genode_attached_dataspace *
genode_usb_allocate_peer_buffer(unsigned long size)
{
	Attached_dataspace & ds = Lx_kit::env().memory.alloc_dataspace(size);

	/*
	 * We have to call virt_to_pages eagerly here,
	 * to get contingous page objects registered
	 */
	lx_emul_virt_to_pages(ds.local_addr<void>(), size >> 12);
	return genode_attached_dataspace_ptr(ds);
}


extern "C" void genode_usb_free_peer_buffer(struct genode_attached_dataspace * ptr)
{
	Lx_kit::env().memory.free(static_cast<Attached_dataspace*>(ptr));
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
		genode_usb_notify_peers();
	}

	void handle_signal()
	{
		lx_user_handle_io();
		Lx_kit::env().scheduler.schedule();
	}

	Main(Env & env) : env(env)
	{
		Lx_kit::initialize(env);

		genode_usb_init(genode_env_ptr(env),
		                genode_allocator_ptr(sliced_heap),
		                genode_signal_handler_ptr(signal_handler),
		                &genode_usb_rpc_callbacks_obj);

		lx_emul_start_kernel(dtb_rom.local_addr<void>());

		env.ep().register_io_progress_handler(*this);
	}
};


void Component::construct(Env & env) {
	static Main main(env); }
