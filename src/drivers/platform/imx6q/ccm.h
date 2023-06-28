/*
 * \brief  Clock control module register description
 * \author Stefan Kalkowski
 * \date   2022-10-22
 */

/*
 * Copyright (C) 2022 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _DRIVERS__PLATFORM__IMX6Q__CCM_H_
#define _DRIVERS__PLATFORM__IMX6Q__CCM_H_

#include <os/attached_mmio.h>
#include <clock.h>

namespace Driver { struct Ccm; }

struct Driver::Ccm : Genode::Attached_mmio
{
	struct Ccgr1 : Register<0x6c, 32>
	{
		struct Enet_clk_enable : Bitfield<10, 2> { };
	};

	struct Enet_clock : public Clock
	{
		Ccm & _ccm;

		Enet_clock(Clocks                 & clocks,
		           Clock::Name const      & name,
		           Ccm                    & ccm)
		: Clock(clocks, name), _ccm(ccm) {}

		void _enable() override {
			_ccm.write<Ccgr1::Enet_clk_enable>(0x3); }

		void _disable() override {
			_ccm.write<Ccgr1::Enet_clk_enable>(0); }

		Rate rate() const override {
			return Rate { 66000000 }; }
	};

	Clocks           &_clocks;
	Enet_clock        _enet     { _clocks, "enet",    *this };
	Fixed_clock       _enet_ref { _clocks, "enet_ref", { 50000000  } };
	Fixed_clock       _usboh3   { _clocks, "usboh3",   { 66000000  } };
	Fixed_clock       _usbphy1  { _clocks, "usbphy1",  { 480000000 } };
	Fixed_clock       _usbphy2  { _clocks, "usbphy2",  { 480000000 } };

	enum {
		CCM_MMIO_BASE = 0x020c4000,
		CCM_MMIO_SIZE = 0x00004000,
	};

	Ccm(Genode::Env &env, Clocks & clocks)
	: Genode::Attached_mmio(env, CCM_MMIO_BASE, CCM_MMIO_SIZE),
	  _clocks(clocks) { }
};

#endif /* _DRIVERS__PLATFORM__IMX6Q__CCM_H_ */
