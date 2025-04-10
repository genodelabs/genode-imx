/*
 * \brief  Paravirtualized access to serial device for a Trustzone VM
 * \author Martin Stein
 * \author Benjamin Lamowski
 * \date   2015-10-23
 */

/*
 * Copyright (C) 2015-2023 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _SERIAL_DRIVER_H_
#define _SERIAL_DRIVER_H_

/* Genode includes */
#include <base/attached_ram_dataspace.h>

/* local includes */
#include <vm.h>

namespace Vmm {
	using namespace Genode;
	class Serial_driver;
}


class Vmm::Serial_driver
{
	private:

		enum { BUF_SIZE = 4096 };

		Attached_ram_dataspace _buf;
		addr_t                 _off = 0;

		void _push(char c) { _buf.local_addr<char>()[_off++] = c; }
		void _flush();
		void _send(Vm &vm, Vcpu_state &state);

	public:

		void handle_smc(Vm &vm, Vcpu_state &state);

		Serial_driver(Ram_allocator &ram, Env::Local_rm &local_rm)
		: _buf(ram, local_rm, BUF_SIZE) { }
};

#endif /* _SERIAL_DRIVER_H_ */
