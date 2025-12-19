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
#include <pin_control_session/connection.h>

#include <net/mac_address.h>

namespace Stmmac_driver {
	using namespace Genode;
	struct Main;
}


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
	bool _phy_reset_control { _config.node().attribute_value("phy_reset_control",
	                                                 false) };
	bool _phy_reset_active_high { _config.node().attribute_value("phy_reset_active_high",
	                                                 false) };

	Attached_rom_dataspace _dtb { _env, "nic.dtb" };

	Constructible<Attached_rom_dataspace>  _mac_rom { };
	Net::Mac_address                       _mac { };
	Constructible<Driver>                  _driver { };
	Constructible<Pin_control::Connection> _pin { };

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
		if (_driver.constructed() || !_mac_rom.constructed())
			return;

		_mac_rom->update();
		_mac_rom->node().with_sub_node("nic", [&] (Node const &node) {
			_mac = { node.attribute_value("mac", Net::Mac_address()) };
			_driver.construct(_env, _signal_handler, _dtb.local_addr<void>());
		}, [&] { });
	}

	Main(Env &env)
	:
		_env(env)
	{
		if (_phy_reset_control)
			_pin.construct(env, "eqos_phy_reset");

		if (_mac_by_rom) {
			_mac_rom.construct(env, "mac");
			_mac_rom->sigh(_mac_handler);
			_handle_mac();
		} else
			_driver.construct(_env, _signal_handler, _dtb.local_addr<void>());
	}

	void with_reset_pin(auto const &fn) {
		if (_pin.constructed()) fn(*_pin, _phy_reset_active_high); }

	void with_mac_address(auto const &fn) { fn(_mac); }
};


static Stmmac_driver::Main& main_singleton(Genode::Env &env = Lx_kit::env().env)
{
	static Stmmac_driver::Main main(env);
	return main;
}


void Component::construct(Genode::Env &env)
{
	main_singleton(env);
}


extern "C" void lx_emul_reset_control_assert(void)
{
	main_singleton().with_reset_pin(
		[] (auto &pin, bool assert_high) {
			pin.state(assert_high); });
}


extern "C" void lx_emul_reset_control_deassert(void)
{
	main_singleton().with_reset_pin(
		[] (auto &pin, bool assert_high) {
			pin.state(!assert_high); });
}


extern "C" void lx_emul_get_mac_address(void *buf)
{
	main_singleton().with_mac_address(
		[&] (auto mac) { Genode::memcpy(buf, mac.addr, 6); });
}
