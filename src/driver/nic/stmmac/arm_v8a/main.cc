/*
 * \brief  ST Microelectronics DMMAC Ethernet driver
 * \author Stefan Kalkowski
 * \date   2024-05-28
 */

/*
 * Copyright (C) 2024 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#include <base/component.h>
#include <base/attached_rom_dataspace.h>
#include <lx_kit/init.h>
#include <lx_kit/env.h>
#include <lx_emul/init.h>
#include <lx_emul/nic.h>
#include <lx_user/io.h>
#include <genode_c_api/uplink.h>

#include <net/mac_address.h>

namespace Stmmac_driver {
	using namespace Genode;
	struct Main;
}

static Genode::uint8_t mac_address[6];

struct Stmmac_driver::Main
{
	struct Driver
	{
		Driver(Env &env, Signal_handler<Main> &handler, void *dtb)
		{
			Lx_kit::initialize(env, handler);

			genode_uplink_init(genode_env_ptr(env),
			                   genode_allocator_ptr(Lx_kit::env().heap),
			                   genode_signal_handler_ptr(handler));

			lx_emul_start_kernel(dtb);
		}
	};

	Env &_env;

	Attached_rom_dataspace _config  { _env, "config" };

	bool _mac_by_rom { _config.node().attribute_value("mac_address_by_rom",
	                                                  false) };

	Attached_rom_dataspace _dtb { _env, "nic.dtb" };

	Constructible<Attached_rom_dataspace> _mac { };
	Constructible<Driver>                 _driver { };

	/**
	 * Signal handler triggered by activity of the uplink connection
	 */
	Signal_handler<Main> _signal_handler { _env.ep(), *this, &Main::_handle_signal };

	Signal_handler<Main> _mac_handler { _env.ep(), *this, &Main::_handle_mac };

	void _handle_signal()
	{
		lx_user_handle_io();
		Lx_kit::env().scheduler.execute();
		genode_uplink_notify_peers();
	}

	void _handle_mac()
	{
		using Mac_address = Net::Mac_address;

		if (_driver.constructed())
			return;

		_mac->update();
		_mac->node().with_sub_node("nic", [&] (Node const &node) {
			Mac_address m { node.attribute_value("mac", Mac_address()) };
			memcpy(mac_address, m.addr, 6);
			_driver.construct(_env, _signal_handler, _dtb.local_addr<void>());
		}, [&] { });
	}

	Main(Env &env)
	:
		_env(env)
	{
		if (_mac_by_rom) {
			_mac.construct(env, "mac");
			_mac->sigh(_mac_handler);
			_handle_mac();
		} else
			_driver.construct(_env, _signal_handler, _dtb.local_addr<void>());
	}
};


void Component::construct(Genode::Env &env)
{
	static Stmmac_driver::Main main(env);
}


extern "C" void lx_emul_get_mac_address(void *buf)
{
	Genode::memcpy(buf, mac_address, 6);
}
