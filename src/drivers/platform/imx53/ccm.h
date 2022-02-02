/*
 * \brief  Clock control module register description
 * \author Nikolay Golikov <nik@ksyslabs.org>
 * \author Stefan Kalkowski <stefan.kalkowski@genode-labs.com>
 * \date   2013-04-29
 */

/*
 * Copyright (C) 2013-2017 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _DRIVERS__PLATFORM__IMX53__CCM_H_
#define _DRIVERS__PLATFORM__IMX53__CCM_H_

#include <os/attached_mmio.h>
#include <clock.h>

namespace Driver { struct Ccm; }

struct Driver::Ccm : Genode::Attached_mmio
{
	/**
	 * Control divider register
	 */
	struct Ccdr : Register<0x4, 32>
	{
		struct Ipu_hs_mask : Bitfield <21, 1> { };
	};

	/**
	 * Serial Clock Multiplexer Register 2
	 */
	struct Cscmr2 : Register<0x20, 32> {};

	/**
	 * D1 Clock Divider Register
	 */
	struct Cdcdr : Register<0x30, 32> {};

	/**
	 * Low power control register
	 */
	struct Clpcr : Register<0x54, 32>
	{
		struct Bypass_ipu_hs : Bitfield<18, 1> { };
	};

	struct Ccgr1 : Register<0x6c, 32>
	{
		struct I2c_1 : Bitfield<18, 2> { };
		struct I2c_2 : Bitfield<20, 2> { };
		struct I2c_3 : Bitfield<22, 2> { };
	};

	struct Ccgr5 : Register<0x7c, 32>
	{
		struct Ipu : Bitfield<10, 2> { };
	};

	struct Ipu_clock : public Clock
	{
		Ccm & _ccm;

		Ipu_clock(Clocks & clocks, Ccm & ccm)
			: Clock(clocks, "ipu"), _ccm(ccm) {}

		void _enable() override
		{
			_ccm.write<Ccgr5::Ipu>(3);
			_ccm.write<Ccdr::Ipu_hs_mask>(0);
			_ccm.write<Clpcr::Bypass_ipu_hs>(0);
			_ccm.write<Cscmr2>(0xa2b32f0b);
			_ccm.write<Cdcdr>(0x14370092);
		}

		void _disable() override
		{
			_ccm.write<Ccgr5::Ipu>(0);
			_ccm.write<Ccdr::Ipu_hs_mask>(1);
			_ccm.write<Clpcr::Bypass_ipu_hs>(1);
		}
	};

	struct I2c_clock : public Clock
	{
		Ccm                    & _ccm;
		typename Ccgr1::access_t _mask;
		typename Ccgr1::access_t _on;

		I2c_clock(Clocks                 & clocks,
		          Clock::Name const      & name,
		          Ccm                    & ccm,
		          typename Ccgr1::access_t mask,
		          typename Ccgr1::access_t on)
		: Clock(clocks, name), _ccm(ccm), _mask(mask), _on(on) {}

		void _enable() override
		{
			typename Ccgr1::access_t v = _ccm.read<Ccgr1>();
			v &= _mask;
			v &= _on;
			_ccm.write<Ccgr1>(v);
		}
	};

	Clocks  & _clocks;
	Ipu_clock _ipu  { _clocks, *this };
	I2c_clock _i2c1 { _clocks, "i2c1", *this, Ccgr1::I2c_1::mask(), 3};
	I2c_clock _i2c2 { _clocks, "i2c2", *this, Ccgr1::I2c_2::mask(), 3};
	I2c_clock _i2c3 { _clocks, "i2c3", *this, Ccgr1::I2c_3::mask(), 3};

	enum {
		CCM_MMIO_BASE = 0x53fd4000,
		CCM_MMIO_SIZE = 0x00004000,
	};

	Ccm(Genode::Env &env, Clocks & clocks)
	: Genode::Attached_mmio(env, CCM_MMIO_BASE, CCM_MMIO_SIZE),
	  _clocks(clocks) { }
};

#endif /* _DRIVERS__PLATFORM__IMX53__CCM_H_ */
