/*
 * \brief  System reset controller register description
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

#ifndef _DRIVERS__PLATFORM__IMX53__SRC_H_
#define _DRIVERS__PLATFORM__IMX53__SRC_H_

#include <os/attached_mmio.h>
#include <reset.h>

namespace Driver { struct Src; }

struct Driver::Src : Genode::Attached_mmio<0x4>
{
	struct Ctrl_reg : Register<0x0, 32>
	{
		struct Ipu_rst : Bitfield<3, 1> { };
	};

	Resets & _resets;

	struct Ipu_reset : Reset
	{
		Src & _src;

		Ipu_reset(Resets & resets, Src & src)
		: Reset(resets, "ipu"), _src(src) {}

		void _deassert() override {
			_src.write<Ctrl_reg::Ipu_rst>(1); }
	};

	Ipu_reset _ipu { _resets, *this };

	enum {
		SRC_MMIO_BASE = 0x53fd0000,
		SRC_MMIO_SIZE = 0x00004000,
	};

	Src(Genode::Env &env, Resets & resets)
	: Attached_mmio(env, {(char *)SRC_MMIO_BASE, SRC_MMIO_SIZE}),
	  _resets(resets) {}
};

#endif /* _DRIVERS__PLATFORM__IMX53__SRC_H_ */
