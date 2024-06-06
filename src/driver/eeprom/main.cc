/*
 * \brief  EEPROM over I2C reader reporting MAC addresses
 * \author Stefan Kalkowski
 * \date   2024-06-04
 */

/*
 * Copyright (C) 2024 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */
 
#include <base/component.h>
#include <i2c_session/connection.h>
#include <os/reporter.h>

using namespace Genode;

struct Main
{
	enum {
		MAC_0_OFFSET = 4,
		MAC_1_OFFSET = 10,
		MAC_LENGTH   = 6
	};

	Env            &_env;
	I2c::Connection _i2c   { _env, "eeprom" };
	Reporter        _mac_0 { _env, "eeprom_entry_0" };
	Reporter        _mac_1 { _env, "eeprom_entry_1" };

	uint8_t _byte(unsigned char off)
	{
		using Transaction = I2c::Session::Transaction;
		using Message     = I2c::Session::Message;

		try {
			Transaction t(Message(Message::WRITE, off),
			              Message(Message::READ, (unsigned char)0U));
			_i2c.transmit(t);
			return (uint8_t)t.value(1).value(0);
		} catch (I2c::Session::Bus_error) {
			error("Bus operation could not be completed.");
			return 0;
		}
	}

	String<32> _read_mac(unsigned char offset)
	{
		return String<32>(Hex(_byte(offset),   Hex::OMIT_PREFIX, Hex::PAD), ":",
		                  Hex(_byte(offset+1), Hex::OMIT_PREFIX, Hex::PAD), ":",
		                  Hex(_byte(offset+2), Hex::OMIT_PREFIX, Hex::PAD), ":",
		                  Hex(_byte(offset+3), Hex::OMIT_PREFIX, Hex::PAD), ":",
		                  Hex(_byte(offset+4), Hex::OMIT_PREFIX, Hex::PAD), ":",
		                  Hex(_byte(offset+5), Hex::OMIT_PREFIX, Hex::PAD));
	}

	Main(Env &env)
	:
		_env(env)
	{
		_mac_0.enabled(true);
		_mac_1.enabled(true);

		try {
			Reporter::Xml_generator xml(_mac_0, [&] () {
				xml.node("nic", [&] () {
					xml.attribute("mac", _read_mac(MAC_0_OFFSET)); });
			});
		} catch (...) { warning("Could not report mac address 0"); }

		try {
			Reporter::Xml_generator xml(_mac_1, [&] () {
				xml.node("nic", [&] () {
					xml.attribute("mac", _read_mac(MAC_1_OFFSET)); });
			});
		} catch (...) { warning("Could not report mac address 1"); }
	}
};


void Component::construct(Genode::Env &env) { static Main main(env); }
