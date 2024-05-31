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


Driver::Ccm::Frac_pll::Frac_pll(Clocks & clocks, Name name, Byte_range_ptr const &range)
: Clock(clocks, name), Mmio(range), _clocks(clocks)
{
	write<Config_reg_0::Bypass>(0);
	write<Config_reg_0::Out_enable>(1);
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
	write<Config_reg_0::Power_down>(1);
}


/********************************
 ** Root_clock immplementation **
 ********************************/

void Driver::Ccm::Root_clock::rate(Rate rate)
{
	uint8_t       pre_div   = 0;
	uint8_t       post_div  = 0;
	unsigned long deviation = ~0UL;

	unsigned long parent_rate =
		_ref_clks[read<Target_reg::Ref_sel>()].ref.rate().value;

	for (uint8_t pre = 0; deviation && (pre < (1U<<3)); pre++) {
		for (uint8_t post = 0; deviation && (post < (1U<<6)); post++) {
			unsigned long diff = (parent_rate / (pre+1)) / (post+1);
			diff = (diff > rate.value) ? diff - rate.value
			                           : rate.value - diff;
			if (diff < deviation) {
				pre_div   = pre;
				post_div  = post;
				deviation = diff;
			}
		}
	}

	write<Target_reg::Pre_div>(pre_div);
	write<Target_reg::Post_div>(post_div);
};


void Driver::Ccm::Root_clock::parent(Name name)
{
	for (unsigned i = 0; i < REF_CLK_MAX; i++) {
		if (_ref_clks[i].ref.name == name) {
			/**
			 * enable parent before setting it,
			 * otherwise the system stalls
			 */
			_ref_clks[i].ref.enable();
			write<Target_reg::Ref_sel>(i);
			return;
		}
	}

	warning("Reference clock ", name, " cannot be set");
}


Driver::Clock::Rate Driver::Ccm::Root_clock::rate() const
{
	unsigned long parent_rate =
		_ref_clks[read<Target_reg::Ref_sel>()].ref.rate().value;
	unsigned pre  = read<Target_reg::Pre_div>()+1;
	unsigned post = read<Target_reg::Post_div>()+1;
	return {parent_rate / pre / post};
}


void Driver::Ccm::Root_clock::_enable()
{
	/* enable the parent clock */
	_ref_clks[read<Target_reg::Ref_sel>()].ref.enable();
	write<Target_reg::Enable>(1);
}


void Driver::Ccm::Root_clock::_disable()
{
	/*
	 * the parent clock cannot be disabled implictly,
	 * because it can be used by several root clocks,
	 * we need reference-counting first to implement this.
	 */
	write<Target_reg::Enable>(0);
}


/***************************************
 ** Root_clock_divider implementation **
 ***************************************/

void Driver::Ccm::Root_clock_divider::rate(Rate rate)
{
	uint32_t div = (uint32_t) ((_parent.rate().value / rate.value) - 1);
	if (div > 64) {
		Genode::error("Cannot set divider ", name, " to ", div);
		return;
	}
	write<Target_reg::Post_div>(div);
}


Driver::Clock::Rate Driver::Ccm::Root_clock_divider::rate() const
{
	return {_parent.rate().value / (read<Target_reg::Post_div>()+1)};
};


/**************************
 ** Gate immplementation **
 **************************/

void Driver::Ccm::Gate::_enable()
{
	/* enable the parent clock implictly */
	_parent.enable();
	write<Ccgr>(0x3);
}


void Driver::Ccm::Gate::_disable()
{
	/* disable the parent clock implictly */
	_parent.disable();
	write<Ccgr>(0x0);
}


/*******************
 ** CCM interface **
 *******************/

Driver::Ccm::Ccm(Genode::Env & env, Clocks & clocks)
	: env(env), clocks(clocks)
{
	audio_pll1_clk.disable();
	audio_pll2_clk.disable();
	gpu_pll_clk.disable();
	vpu_pll_clk.disable();
	system_pll3_clk.disable();
	video_pll2_clk.disable();

	/* turn off all unnecessary root clocks */
	arm_m4_clk_root.disable();
	vpu_a53_clk_root.disable();
	gpu_core_clk_root.disable();
	gpu_shader_clk_root.disable();
	enet_axi_clk_root.disable();
	nand_usdhc_bus_clk_root.disable();
	vpu_bus_clk_root.disable();
	display_axi_clk_root.disable();
	display_apb_clk_root.disable();
	display_rtrm_clk_root.disable();
	usb_bus_clk_root.disable();
	gpu_axi_clk_root.disable();
	gpu_ahb_clk_root.disable();
	audio_ahb_clk_root.disable();
	mipi_dsi_esc_rx_clk_root.disable();
	vpu_g1_clk_root.disable();
	vpu_g2_clk_root.disable();
	display_dtrc_clk_root.disable();
	display_dc8000_clk_root.disable();
	pcie1_ctrl_clk_root.disable();
	pcie1_phy_clk_root.disable();
	pcie1_aux_clk_root.disable();
	dc_pixel_clk_root.disable();
	lcdif_pixel_clk_root.disable();
	sai1_clk_root.disable();
	sai2_clk_root.disable();
	sai3_clk_root.disable();
	sai4_clk_root.disable();
	sai5_clk_root.disable();
	sai6_clk_root.disable();
	spdif1_clk_root.disable();
	spdif2_clk_root.disable();
	enet_ref_clk_root.disable();
	enet_timer_clk_root.disable();
	enet_phy_ref_clk_root.disable();
	nand_clk_root.disable();
	qspi_clk_root.disable();
	usdhc1_clk_root.disable();
	usdhc2_clk_root.disable();
	i2c1_clk_root.disable();
	i2c2_clk_root.disable();
	i2c3_clk_root.disable();
	i2c4_clk_root.disable();
	uart2_clk_root.disable();
	uart3_clk_root.disable();
	uart4_clk_root.disable();
	usb_core_ref_clk_root.disable();
	usb_phy_ref_clk_root.disable();
	ecspi1_clk_root.disable();
	ecspi2_clk_root.disable();
	pwm1_clk_root.disable();
	pwm2_clk_root.disable();
	pwm3_clk_root.disable();
	pwm4_clk_root.disable();
	gpt1_clk_root.disable();
	gpt2_clk_root.disable();
	gpt3_clk_root.disable();
	gpt4_clk_root.disable();
	gpt5_clk_root.disable();
	gpt6_clk_root.disable();
	trace_clk_root.disable();
	wdog_clk_root.disable();
	wrclk_clk_root.disable();
	ipp_do_clko1clk_root.disable();
	ipp_do_clko2_clk_root.disable();
	mipi_dsi_core_clk_root.disable();
	mipi_dsi_phy_ref_clk_root.disable();
	mipi_dsi_dbi_clk_root.disable();
	old_mipi_dsi_esc_clk_root.disable();
	mipi_csi1_core_clk_root.disable();
	mipi_csi1_phy_ref_clk_root.disable();
	mipi_csi1_esc_clk_root.disable();
	mipi_csi2_core_clk_root.disable();
	mipi_csi2_phy_ref_clk_root.disable();
	mipi_csi2_esc_clk_root.disable();
	pcie2_ctrl_clk_root.disable();
	pcie2_phy_clk_root.disable();
	pcie2_aux_clk_root.disable();
	ecspi3_clk_root.disable();
	old_mipi_dsi_esc_rx_clk_root.disable();
	display_hdmi_clk_root.disable();

	/* increase NOC clock for better DDR performance */
	noc_clk_root.parent("system_pll1_clk");
	noc_clk_root.rate({800000000});

	pllout.write<Pllout_monitor::Config::Ref_sel>(Pllout_monitor::Config::Ref_sel::SYS_PLL1);
	pllout.write<Pllout_monitor::Sccg_divider::System_pll_1>(0b111);
	pllout.write<Pllout_monitor::Config::Enable>(1);
}
