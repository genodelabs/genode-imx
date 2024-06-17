/*
 * \brief  Reset_controller driver for imx8
 * \author Alice Domage <alice.domage@gapfruit.com>
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
#include <os/attached_mmio.h>

namespace Driver {
	using namespace Genode;
	struct Watchdog;
}


struct Driver::Watchdog : Genode::Attached_mmio<0x10000>
{
	struct Control : Mmio::Register<0x00, 16>
	{
		struct WDE : Bitfield<2, 1> { };
		struct WDA : Bitfield<5, 1> { };
		struct SRE : Bitfield<6, 1> { };
	};

	enum { WATCHDOG_MMIO_BASE = 0x30280000 };

	Watchdog(Env &env)
	: Attached_mmio<SIZE>(env, { (char*)WATCHDOG_MMIO_BASE, SIZE }) {}

	void reset()
	{
		write<Control::SRE>(1);
		write<Control::WDE>(1);
		write<Control::WDA>(0);
	}
};

#endif /* __PLATFORM__IMX__WATCHDOG_H_ */
