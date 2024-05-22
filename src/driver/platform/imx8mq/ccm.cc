/*
 * \brief  Central clock module for i.MX8MQ
 * \author Stefan Kalkowski
 * \date   2020-06-12
 */

/*
 * Copyright (C) 2020 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#include <ccm.h>

/******************************
 ** Frac_pll immplementation **
 ******************************/

void Driver::Ccm::Frac_pll::_disable()
{
	if (_never_disable)
		return;

	write<Config_reg_0::Power_down>(1);
}


void Driver::Ccm::Frac_pll::_enable()
{
	if (!read<Config_reg_0::Power_down>()) return;

	write<Config_reg_0::Power_down>(0);

	for (unsigned i = 0; i < 0xfffff; i++) {
		if (read<Config_reg_0::Lock_status>()) { break; }
	}
}


void Driver::Ccm::Frac_pll::parent(Name parent)
{
	if (parent == "25m_ref_clk") {
		write<Config_reg_0::Ref_sel>(Config_reg_0::Ref_sel::REF_CLK_25M);
		return;
	}
	if (parent == "27m_ref_clk") {
		write<Config_reg_0::Ref_sel>(Config_reg_0::Ref_sel::REF_CLK_27M);
		return;
	}
	if (parent == "hdmi_phy_27m_clk") {
		write<Config_reg_0::Ref_sel>(Config_reg_0::Ref_sel::HDMI_PHY_27M);
		return;
	}
	write<Config_reg_0::Ref_sel>(Config_reg_0::Ref_sel::CLK_P_N);
}


void Driver::Ccm::Frac_pll::rate(Rate rate)
{
	static constexpr uint32_t fixed_frac = 1 << 24;

	uint64_t pr = 0;
	_parent([&] (Clock & clock) { pr = clock.rate().value; });

	/* we set output div value to fixed value of 2 */
	uint64_t r = rate.value * 2;
	pr         = pr * 8 /
	             (read<Config_reg_0::Refclk_div_value>() + 1);
	uint32_t div_int  = (uint32_t)((r / pr) & 0b1111111);
	uint32_t div_frac = (uint32_t)(((r - div_int * pr) * fixed_frac) / pr);

	Config_reg_1::access_t v = 0;
	Config_reg_1::Int_div_ctl::set(v, div_int-1);
	Config_reg_1::Frac_div_ctl::set(v, div_frac);
	write<Config_reg_1>(v);

	//write<Config_reg_0::Refclk_div_value>(0);
	write<Config_reg_0::Output_div_value>(0);
	write<Config_reg_0::Newdiv_val>(1);

	/* wait for ack, if powered and not bypassed */
	if (!(read<Config_reg_0::Bypass>() ||
		  read<Config_reg_0::Power_down>())) {
		for (unsigned i = 0; i < 0xfffff; i++) {
			if (read<Config_reg_0::Newdiv_ack>()) { break; }
		}
	}

	write<Config_reg_0::Newdiv_val>(0);
}


Driver::Clock::Rate Driver::Ccm::Frac_pll::rate() const
{
	static constexpr uint32_t fixed_frac = 1 << 24;

	/**
	 * Formula from the reference manual:
	 *  PLLOUT   = REF / DIVR_VAL * 8 * DIVF_VAL / DIVQ_VAL
	 *  DIVF_VAL = 1 + DIVFI + (DIVFF/2^24)
	 */
	uint32_t divq  = (read<Config_reg_0::Output_div_value>() + 1) * 2;
	uint32_t divr  = read<Config_reg_0::Refclk_div_value>() + 1;
	uint32_t divff = read<Config_reg_1::Frac_div_ctl>();
	uint32_t divfi = read<Config_reg_1::Int_div_ctl>();

	uint64_t ref = 0;
	_parent([&] (Clock & clock) { ref = clock.rate().value; });
	ref = ref * 8 / divr;

	return {(ref * (divfi + 1) / divq) +
	        (ref * divff / fixed_frac / divq)};
}


Driver::Ccm::Frac_pll::Frac_pll(Clocks               &clocks,
                                Name                  name,
                                Byte_range_ptr const &range,
                                bool const            never_disable)
:
	Clock(clocks, name),
	Mmio(range),
	_clocks(clocks),
	_never_disable(never_disable)
{
	write<Config_reg_0::Bypass>(0);
	write<Config_reg_0::Out_enable>(1);

	/*
	 * Enable within the clock tree if clock is on,
	 * because there are potentially root-clocks enabled and configured to use
	 * this PLL, disable it in the end when all clocks are initialized
	 */
	if (!read<Config_reg_0::Power_down>()) enable();
}


/******************************
 ** Sccg_pll immplementation **
 ******************************/

void Driver::Ccm::Sccg_pll::parent(Name parent)
{
	if (parent == "25m_ref_clk") {
		write<Config_reg_0::Ref_sel>(Config_reg_0::Ref_sel::REF_CLK_25M);
		return;
	}
	if (parent == "27m_ref_clk") {
		write<Config_reg_0::Ref_sel>(Config_reg_0::Ref_sel::REF_CLK_27M);
		return;
	}
	if (parent == "hdmi_phy_27m_clk") {
		write<Config_reg_0::Ref_sel>(Config_reg_0::Ref_sel::HDMI_PHY_27M);
		return;
	}
	write<Config_reg_0::Ref_sel>(Config_reg_0::Ref_sel::CLK_P_N);
}


static inline bool find_sccg_pll_values(unsigned long parent_rate,
                                        unsigned long rate,
                                        unsigned    & factor,
                                        unsigned    & quotient)
{
	for (unsigned q = 1; q <= 64; q++)
		for (unsigned f = 1; f <= 64; f++) {
			if (rate != (parent_rate * f / q))
					continue;
				factor   = f;
				quotient = q;
				return true;
			}
	return false;
}


void Driver::Ccm::Sccg_pll::rate(Rate rate)
{
	Rate parent_rate = {0};
	_parent([&] (Clock & clock) { parent_rate = clock.rate(); });

	if (rate.value == parent_rate.value) {
		write<Config_reg_0::Bypass2>(1);
		return;
	}

	unsigned f, q;
	if (!find_sccg_pll_values(parent_rate.value, rate.value, f, q)) {
		Genode::error(__func__," not implemented for rate ", rate.value);
		return;
	}

	write<Config_reg_0::Bypass2>(0);
	write<Config_reg_0::Bypass1>(1);
	write<Config_reg_2::Feedback_divf2>(f-1);
	write<Config_reg_2::Ref_divr2>(q-1);
	write<Config_reg_2::Output_div_val>(0);
}


Driver::Clock::Rate Driver::Ccm::Sccg_pll::rate() const
{
	unsigned factor = read<Config_reg_1::Sse>() ? 8 : 2;
	unsigned divf1  = read<Config_reg_2::Feedback_divf1>() + 1;
	unsigned divf2  = read<Config_reg_2::Feedback_divf2>() + 1;
	unsigned divr1  = read<Config_reg_2::Ref_divr1>()      + 1;
	unsigned divr2  = read<Config_reg_2::Ref_divr2>()      + 1;
	unsigned divq   = read<Config_reg_2::Output_div_val>() + 1;

	unsigned long parent_rate = 0;
	_parent([&] (Clock & clock) { parent_rate = clock.rate().value; });

	if (read<Config_reg_0::Bypass2>()) {
		return {parent_rate};
	}

	if (read<Config_reg_0::Bypass1>()) {
		return {(parent_rate * divf2) / (divr2 * divq)};
	}

	return {parent_rate * factor * divf1 * divf2 / (divr1*divr2*divq)};
}


void Driver::Ccm::Sccg_pll::_enable()
{
	if (!read<Config_reg_0::Power_down>()) return;

	write<Config_reg_0::Power_down>(0);

	for (unsigned i = 0; i < 0xfffff; i++) {
		if (read<Config_reg_0::Lock_status>()) { break; }
	}
}


void Driver::Ccm::Sccg_pll::_disable()
{
	if (_never_disable)
		return;

	write<Config_reg_0::Power_down>(1);
}


Driver::Ccm::Sccg_pll::Sccg_pll(Clocks               &clocks,
                                Name                  name,
                                Byte_range_ptr const &range,
                                bool const            never_disable)
:
	Clock(clocks, name),
	Mmio(range),
	_clocks(clocks),
	_never_disable(never_disable)
{
	/*
	 * Enable within the clock tree if clock is on,
	 * because there are potentially root-clocks enabled and configured to use
	 * this PLL, disable it in the end when all clocks are initialized
	 */
	if (!read<Config_reg_0::Power_down>()) enable();
}

/*******************
 ** CCM interface **
 *******************/

Driver::Ccm::Ccm(Genode::Env & env, Clocks & clocks)
	: env(env), clocks(clocks)
{
	/* increase NOC clock for better DDR performance */
	noc_clk_root.parent("system_pll1_clk");
	noc_clk_root.rate({800000000});

	pllout.write<Pllout_monitor::Config::Ref_sel>(Pllout_monitor::Config::Ref_sel::SYS_PLL1);
	pllout.write<Pllout_monitor::Sccg_divider::System_pll_1>(0b111);
	pllout.write<Pllout_monitor::Config::Enable>(1);

	/* Now, disable all PLLs not root-clock depends for the moment */
	audio_pll1_clk.disable();
	audio_pll2_clk.disable();
	video_pll1_clk.disable();
	gpu_pll_clk.disable();
	vpu_pll_clk.disable();
	system_pll3_clk.disable();
	video_pll2_clk.disable();
}
