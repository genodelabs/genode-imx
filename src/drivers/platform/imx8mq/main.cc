/*
 * \brief  Platform driver for i.MX 8MQ SoC
 * \author Stefan Kalkowski
 * \date   2020-04-12
 */

/*
 * Copyright (C) 2020 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#include <base/component.h>

#include <ccm.h>
#include <gpc.h>
#include <src.h>
#include <root.h>

namespace Driver { struct Main; };

struct Driver::Main
{
	void update_config();

	Env                  & env;
	Heap                   heap           { env.ram(), env.rm()   };
	Sliced_heap            sliced_heap    { env.ram(), env.rm()   };
	Attached_rom_dataspace config         { env, "config"         };
	Device_model           devices        { heap                  };
	Ccm                    ccm            { env, devices.clocks() };
	Gpc                    gpc            { env, devices.powers() };
	Src                    src            { env, devices.resets() };
	Signal_handler<Main>   config_handler { env.ep(), *this,
	                                      &Main::update_config };
	Driver::Root           root           { env, sliced_heap, config, devices };

	Main(Genode::Env & e)
	: env(e)
	{
		devices.update(config.xml());
		config.sigh(config_handler);
		env.parent().announce(env.ep().manage(root));
	}
};


void Driver::Main::update_config()
{
	config.update();
	devices.update(config.xml());
	root.update_policy();
}

void Component::construct(Genode::Env &env) {
	static Driver::Main main(env); }
