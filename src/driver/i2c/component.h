/*
 * \brief  I2C session component
 * \author Jean-Adrien Domage <jean-adrien.domage@gapfruit.com>
 * \date   2021-02-26
 */

/*
 * Copyright (C) 2013-2021 Genode Labs GmbH
 * Copyright (C) 2021 gapfruit AG
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _I2C_DRIVER__COMPONENT_H_
#define _I2C_DRIVER__COMPONENT_H_

#include <os/session_policy.h>
#include <root/component.h>
#include <i2c_session/i2c_session.h>
#include "i2c_interface.h"

namespace I2c {
	using namespace Genode;
	class Session_component;
	class Root;
}


class I2c::Session_component : public Rpc_object<I2c::Session>
{
	private:

		Rpc_entrypoint   &_ep;
		I2c::Driver_base &_driver;
		uint8_t const     _device_address;

	public:

		Session_component(Rpc_entrypoint   &ep,
		                  I2c::Driver_base &driver,
		                  uint8_t           device_address)
		:
			_ep(ep), _driver(driver), _device_address(device_address)
		{ }

		void transmit(Transaction & t) override {
			_driver.transmit(_device_address, t); }
};


class I2c::Root : public Root_component<I2c::Session_component>
{
	private:

		Rpc_entrypoint   &_ep;
		I2c::Driver_base &_driver;
		Attached_rom_dataspace const & _config_rom;

	protected:

		Create_result _create_session(char const *args) override
		{
			char device_name_c_string[I2c::Device_name::capacity()] { };
			Arg_string::find_arg(args, "label").string(device_name_c_string, sizeof(device_name_c_string), "");
			Device_name const device_name(device_name_c_string);

			Session_component *session_ptr = nullptr;

			with_matching_policy(device_name, _config_rom.node(),

				[&] (Node const &policy) {

					uint8_t const device_address = policy.attribute_value("bus_address", static_cast<uint8_t>(0));

					/* address 0x0 is reserved, so if we return 0x0 it is an error */
					if (device_address == 0) {
						warning("Session with label '", device_name,
						        "' could not be created, no such policy");
						return;
					}

					session_ptr = new (md_alloc())
						I2c::Session_component(_ep, _driver, device_address);
				},
				[&] { }
			);

			if (session_ptr)
				return *session_ptr;
			else
				throw Service_denied();
		}

	public:

		Root(Rpc_entrypoint &ep, Allocator &md_alloc,
		     I2c::Driver_base &driver, Attached_rom_dataspace const &config_rom)
		:
			Root_component<I2c::Session_component>(&ep, &md_alloc),
			_ep(ep), _driver(driver), _config_rom(config_rom)
		{ }
};

#endif /* _I2C_DRIVER__COMPONENT_H_ */
