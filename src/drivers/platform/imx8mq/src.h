/*
 * \brief  System reset controller for i.MX8
 * \author Stefan Kalkowski
 * \date   2021-05-21
 */

/*
 * Copyright (C) 2021 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#pragma once

#include <base/env.h>
#include <base/log.h>
#include <os/attached_mmio.h>
#include <util/string.h>

#include <reset.h>

struct Src : Genode::Attached_mmio
{
	Driver::Resets & resets;

	struct Mipi_phy : Register<0x28, 32>
	{
		struct Byte  : Bitfield<1, 1> {};
		struct Reset : Bitfield<2, 1> {};
		struct Dpi   : Bitfield<3, 1> {};
		struct Esc   : Bitfield<4, 1> {};
		struct Pclk  : Bitfield<5, 1> {};
	};

	struct Pcie_1 : Register<0x2c, 32>
	{
		struct Pcie_phy_global  : Bitfield<1, 1> {};
		struct Pcie_phy_button  : Bitfield<2, 1> {};
		struct Pcie_apps_enable : Bitfield<6, 1> {};
	};

	struct Pcie_2 : Register<0x48, 32> { };

	template <typename REG>
	struct Reset_switch : Driver::Reset
	{
		Src                  & src;
		typename REG::access_t mask;
		typename REG::access_t on;
		typename REG::access_t off;

		Reset_switch(Src                  & src,
		             Reset::Name const    & name,
		             typename REG::access_t mask,
		             typename REG::access_t on,
		             typename REG::access_t off)
		:
			Driver::Reset(src.resets, name),
			src(src), mask(mask), on(on), off(off) {}

		void _deassert() override
		{
			typename REG::access_t v = src.read<REG>();
			v &= mask;
			v &= on;
			src.write<REG>(v);
		}

		void _assert() override
		{
			typename REG::access_t v = src.read<REG>();
			v &= mask;
			v &= off;
			src.write<REG>(v);
		}
	};

	Reset_switch<Mipi_phy> mipi_dsi_byte { *this, "mipi_dsi_byte", Mipi_phy::Byte::mask(), 1, 0 };
	Reset_switch<Mipi_phy> mipi_dsi_dpi  { *this, "mipi_dsi_dpi",  Mipi_phy::Dpi::mask(),  1, 0 };
	Reset_switch<Mipi_phy> mipi_dsi_esc  { *this, "mipi_dsi_esc",  Mipi_phy::Esc::mask(),  1, 0 };
	Reset_switch<Mipi_phy> mipi_dsi_pclk { *this, "mipi_dsi_pclk", Mipi_phy::Pclk::mask(), 1, 0 };

	Reset_switch<Pcie_1> pcie_1_core { *this, "pcie_1_core", Pcie_1::Pcie_apps_enable::mask(), 1, 0 };
	Reset_switch<Pcie_1> pcie_1_phy  { *this, "pcie_1_phy",  Pcie_1::Pcie_phy_button::mask() |
	                                                         Pcie_1::Pcie_phy_global::mask(),  0, 6 };
	Reset_switch<Pcie_2> pcie_2_core { *this, "pcie_2_core", Pcie_1::Pcie_apps_enable::mask(), 1, 0 };
	Reset_switch<Pcie_2> pcie_2_phy  { *this, "pcie_2_phy",  Pcie_1::Pcie_phy_button::mask() |
	                                                         Pcie_1::Pcie_phy_global::mask(),  0, 6 };

	enum {
		SRC_MMIO_BASE = 0x30390000,
		SRC_MMIO_SIZE = 0x10000,
	};

	Src(Genode::Env & env, Driver::Resets & resets)
	: Attached_mmio(env, SRC_MMIO_BASE, SRC_MMIO_SIZE), resets(resets) { };
};

