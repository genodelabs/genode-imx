/*
 * \brief  System reset controller for i.MX8
 * \author Stefan Kalkowski
 * \author Alice Domage
 * \date   2024-03-27
 */

/*
 * Copyright (C) 2024 Genode Labs GmbH
 * Copyright (C) 2024 gapfruit ag
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

struct Src : Genode::Attached_mmio<0x4c>
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
		struct Phy_global  : Bitfield<1, 1> {};
		struct Phy_button  : Bitfield<2, 1> {};
		struct Apps_enable : Bitfield<6, 1> {};
	};

	struct Pcie_2 : Register<0x48, 32>
	{
		struct Phy_global  : Bitfield<1, 1> {};
		struct Phy_button  : Bitfield<2, 1> {};
		struct Apps_enable : Bitfield<6, 1> {};
	};

	template <typename REG, typename BITFIELD>
	struct Reset_switch : Driver::Reset
	{
		Src                  & src;
		typename REG::access_t on;
		typename REG::access_t off;

		Reset_switch(Src                  & src,
		             Reset::Name const    & name,
		             typename REG::access_t on,
		             typename REG::access_t off)
		:
			Driver::Reset(src.resets, name),
			src(src), on(on), off(off) {}

		void _deassert() override {
			src.write<BITFIELD>(on); }

		void _assert() override {
			src.write<BITFIELD>(off); }
	};

	template <typename REG>
	struct Pcie_phy_switch : Driver::Reset
	{
		Src & src;

		Pcie_phy_switch(Src               & src,
		                Reset::Name const & name)
		: Driver::Reset(src.resets, name), src(src) {}

		void _deassert() override
		{
			src.write<typename REG::Phy_button>(0);
			src.write<typename REG::Phy_global>(0);
		}

		void _assert() override {
			src.write<typename REG::Phy_button>(1);
			src.write<typename REG::Phy_global>(1);
		}
	};

	Reset_switch<Mipi_phy, Mipi_phy::Byte> mipi_dsi_byte { *this, "mipi_dsi_byte", 1, 0 };
	Reset_switch<Mipi_phy, Mipi_phy::Dpi>  mipi_dsi_dpi  { *this, "mipi_dsi_dpi",  1, 0 };
	Reset_switch<Mipi_phy, Mipi_phy::Esc>  mipi_dsi_esc  { *this, "mipi_dsi_esc",  1, 0 };
	Reset_switch<Mipi_phy, Mipi_phy::Pclk> mipi_dsi_pclk { *this, "mipi_dsi_pclk", 1, 0 };

	Reset_switch<Pcie_1, Pcie_1::Apps_enable> pcie_1_core { *this, "pcie_1_core", 1, 0 };
	Pcie_phy_switch<Pcie_1>                   pcie_1_phy  { *this, "pcie_1_phy" };

	Reset_switch<Pcie_2, Pcie_2::Apps_enable> pcie_2_core { *this, "pcie_2_core", 1, 0 };
	Pcie_phy_switch<Pcie_2>                   pcie_2_phy  { *this, "pcie_2_phy" };

	enum {
		SRC_MMIO_BASE = 0x30390000,
		SRC_MMIO_SIZE = 0x10000,
	};

	Src(Genode::Env & env, Driver::Resets & resets)
	: Attached_mmio(env, {(char *)SRC_MMIO_BASE, SRC_MMIO_SIZE}), resets(resets) { };
};

