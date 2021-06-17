/*
 * \brief  Lx_emul I2C backend
 * \author Stefan Kalkowski
 * \date   2021-05-22
 */

/*
 * Copyright (C) 2021 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#include <i2c_session/connection.h>
#include <lx_kit/env.h>
#include <lx_emul/i2c.h>

using Transaction = I2c::Session::Transaction;
using Message     = I2c::Session::Message;

static I2c::Connection & i2c()
{
	static I2c::Connection i2c(Lx_kit::env().env);
	return i2c;
}


extern "C" unsigned char lx_emul_i2c_read_byte(unsigned char addr)
{
	Transaction t(Message(Message::WRITE, addr), Message(Message::READ, 0));
	i2c().transmit(t);
	return t.value(1).value(0);
}


extern "C" void lx_emul_i2c_write_bytes(unsigned len, unsigned char * bytes)
{
	Message m(Message::WRITE);
	for (unsigned i = 0; i < len; i++)
		m.add(bytes[i]);
	Transaction t(m);
	i2c().transmit(t);
}
