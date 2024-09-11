/*
 * \brief  Reset_controller driver for imx8mp
 * \author Alice Domage <alice.domage@gapfruit.com>
 * \author Sebastian Sumpf
 * \author Stefan Kalkowski
 * \date   2023-06-07
 */

/*
 * Copyright (C) 2013-2023 Genode Labs GmbH
 * Copyright (C) 2023 gapfruit AG
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef __PLATFORM__IMX__WATCHDOG_H_
#define __PLATFORM__IMX__WATCHDOG_H_

#include <base/env.h>
#include <irq_session/connection.h>
#include <os/attached_mmio.h>

namespace Driver {
	using namespace Genode;
	struct Watchdog;
}


struct Driver::Watchdog : private Genode::Attached_mmio<0xa>
{
	Env &_env;

	Irq_connection              _irq { _env, 110 };
	Io_signal_handler<Watchdog> _irq_handler { _env.ep(), *this,
		&Watchdog::_handle_irq };

	struct Control : Register<0x00, 16>
	{
		struct WDE : Bitfield<2, 1> { };
		struct WDA : Bitfield<5, 1> { };
		struct SRE : Bitfield<6, 1> { };
		struct WT  : Bitfield<8, 8> { };
	};

	struct Service : Register<0x2, 16> { };

	struct Interrupt : Register<0x6, 16>
	{
		/* interrupt status */
		struct WTIS : Bitfield<14, 1> { };
		/* interrupt enable (write once) */
		struct WIE  : Bitfield<15, 1> { };
	};

	void _service()
	{
		/* timeout 128s */
		write<Control::WT>(0xffff);

		/* service sequence */
		write<Service>(0x5555);
		write<Service>(0xaaaa);
	}

	void _handle_irq()
	{
		if (read<Interrupt::WTIS>()) {
			_service();
			write<Interrupt::WTIS>(1);
		}

		_irq.ack_irq();
	}

	enum { WATCHDOG_MMIO_BASE = 0x30280000 };

	Watchdog(Env &env)
	: Attached_mmio<SIZE>(env, { (char*)WATCHDOG_MMIO_BASE, SIZE }),
	  _env(env)
	{
		if (running())
			write<Interrupt::WIE>(1);

		_irq.sigh(_irq_handler);
		_handle_irq();
	}

	void reset()
	{
		write<Control::SRE>(1);
		write<Control::WDE>(1);
		write<Control::WDA>(0);
	}

	bool running() { return read<Control::WDE>(); }
};

#endif /* __PLATFORM__IMX__WATCHDOG_H_ */
