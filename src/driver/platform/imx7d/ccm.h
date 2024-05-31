/*
 * \brief  Clock control module register description
 * \author Stefan Kalkowski
 * \date   2022-10-25
 */

/*
 * Copyright (C) 2022 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _DRIVERS__PLATFORM__IMX7D__CCM_H_
#define _DRIVERS__PLATFORM__IMX7D__CCM_H_

#include <os/attached_mmio.h>
#include <clock.h>

namespace Driver { struct Ccm; }

struct Driver::Ccm : Genode::Attached_mmio<0x4714>
{
	template <unsigned NR>
	struct Ccgr : Register<0x4000 + NR*0x10, 32>
	{
		struct Domain_0 :
			Register<0x4000 + NR*0x10, 32>::template Bitfield<0, 2> { };
	};

	template <unsigned NR>
	struct Enet_clock : public Clock
	{
		Ccm & _ccm;

		Enet_clock(Clocks                 & clocks,
		           Clock::Name const      & name,
		           Ccm                    & ccm)
		: Clock(clocks, name), _ccm(ccm) {}

		void _enable() override {
			_ccm.write<typename Ccgr<NR>::Domain_0>(0x3); }

		void _disable() override {
			_ccm.write<typename Ccgr<NR>::Domain_0>(0); }

		Rate rate() const override {
			return Rate { 100000000 }; }
	};

	struct Simple_clock : public Clock
	{
		Rate _rate;

		Simple_clock(Clocks            & clocks,
		             Clock::Name const & name,
		             Rate                rate)
		: Clock(clocks, name), _rate(rate) {}

		Rate rate() const override { return _rate; }
	};

	Clocks        & _clocks;
	Enet_clock<112> _enet_1 { _clocks, "enet1_time_clk_root", *this};
	Enet_clock<113> _enet_2 { _clocks, "enet2_time_clk_root", *this};

	Simple_clock _ipg_clk_root          { _clocks, "ipg_clk_root",          { 196363636 } };
	Simple_clock _enet_pll_div8         { _clocks, "enet_pll_div8",         { 125000000 } };
	Simple_clock _enet_phy_ref_clk_root { _clocks, "enet_phy_ref_clk_root", { 24000000  } };
	Simple_clock _enet_axi_clk_root     { _clocks, "enet_axi_clk_root",     { 196363636 } };

	enum {
		CCM_MMIO_BASE = 0x30380000,
		CCM_MMIO_SIZE = 0x00010000,
	};

	Ccm(Genode::Env &env, Clocks & clocks)
	: Attached_mmio(env, {(char *)CCM_MMIO_BASE, CCM_MMIO_SIZE}),
	  _clocks(clocks) { }
};

#endif /* _DRIVERS__PLATFORM__IMX7D__CCM_H_ */
