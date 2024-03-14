/*
 * \brief  Platform driver for i.MX 8MP SoC
 * \author Stefan Kalkowski
 * \author Alice Domage
 * \date   2024-03-27
 */

/*
 * Copyright (C) 2024 Genode Labs GmbH
 * Copyright (C) 2024 gapfruit ag
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#include <base/component.h>

#include <ccm.h>
#include <gpc.h>
#include <src.h>
#include <common.h>

namespace Driver { struct Main; };

struct Driver::Main
{
	Env                  & _env;
	Attached_rom_dataspace _config_rom     { _env, "config"        };
	bool                   _verbose        { _config_rom.xml().attribute_value("verbose", false) };
	Common                 _common         { _env, _config_rom     };
	Signal_handler<Main>   _config_handler { _env.ep(), *this,
	                                         &Main::_handle_config };

	Ccm ccm { _env, _common.devices().clocks(), _verbose };
	Gpc gpc { _env, _common.devices().powers() };
	Src src { _env, _common.devices().resets() };

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
	_common.handle_config(_config_rom.xml());
}


void Component::construct(Genode::Env &env) {
	static Driver::Main main(env); }
