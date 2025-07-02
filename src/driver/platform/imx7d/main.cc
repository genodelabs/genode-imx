/*
 * \brief  Platform driver for i.MX7D SoC
 * \author Stefan Kalkowski
 * \date   2022-10-25
 */

/*
 * Copyright (C) 2022 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#include <base/component.h>

#include <ccm.h>
#include <common.h>

namespace Driver { struct Main; };

struct Driver::Main
{
	Env                  & _env;
	Attached_rom_dataspace _config_rom     { _env, "config"        };
	Common                 _common         { _env, _config_rom     };
	Signal_handler<Main>   _config_handler { _env.ep(), *this,
	                                         &Main::_handle_config };

	Ccm ccm { _env, _common.devices().clocks() };

	void _handle_config();

	Main(Genode::Env & e)
	: _env(e)
	{
		_config_rom.sigh(_config_handler);
		_handle_config();
		_common.announce_service();
	}
};


void Driver::Main::_handle_config()
{
	_config_rom.update();
	_common.handle_config(_config_rom.node());
}


void Component::construct(Genode::Env &env) {
	static Driver::Main main(env); }
