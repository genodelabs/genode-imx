/*
 * \brief  Central clock module for i.MX8MP
 * \author Stefan Kalkowski
 * \author Alice Domage
 * \date   2024-03-20
 */

/*
 * Copyright (C) 2024 Genode Labs GmbH
 * Copyright (C) 2024 gapfruit ag
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#include <ccm.h>


/***************
 ** Math util **
 ***************/

namespace Genode {

	template<typename T1, typename T2, typename T3>
	static inline T1 clamp(T1 in, T2 min, T3 max) {
		if (in < min) return min;
		if (in > max) return max;
		return in;
	}

}


/**********************************
 ** Frac1446_pll immplementation **
 **********************************/

Driver::Ccm::Pll14xx::Config Driver::Ccm::Frac_pll1443::_read() const
{
	Pll14xx::Config cfg;
	cfg.pdiv = _mmio.read<Pll14xx::Fdiv_ctl0::Pre_div>();
	cfg.mdiv = _mmio.read<Pll14xx::Fdiv_ctl0::Main_div>();
	cfg.sdiv = _mmio.read<Pll14xx::Fdiv_ctl0::Post_div>();
	cfg.kdiv = static_cast<int16_t>(_mmio.read<Pll14xx::Fdiv_ctl1::Dsm>());
	cfg.rate = _compute_rate(cfg);

	if (_verbose) {
		log(__FUNCTION__, " PLL=", name, " pdiv=", cfg.pdiv,
			" mdiv=", cfg.mdiv,
			" sdiv=", cfg.sdiv,
			" kdiv=", cfg.kdiv,
			" rate=", cfg.rate.value);
	}

	return cfg;
}


Genode::int16_t Driver::Ccm::Frac_pll1443::_compute_kdiv(Driver::Ccm::Pll14xx::Config &cfg, Rate fout) const
{
	uint64_t fin = _mmio.parent_rate().value;

	int64_t kdiv = ((fout.value * ((cfg.pdiv * 65536) << cfg.sdiv) + fin / 2 ) / fin) - (cfg.mdiv * 65536);

	return static_cast<int16_t>(clamp(kdiv, MIN_KDIV, MAX_KDIV));
}


Driver::Ccm::Frac_pll1443::Rate Driver::Ccm::Frac_pll1443::_compute_rate(Driver::Ccm::Pll14xx::Config &cfg) const
{
	uint64_t fout = _mmio.parent_rate().value;
	fout *= (cfg.mdiv * 65536 + cfg.kdiv); // TODO: sign conversion
	uint64_t pdiv = cfg.pdiv;
	pdiv *= 65536;
	fout = fout / (pdiv << cfg.sdiv);
	return { fout };
}


Driver::Ccm::Pll14xx::Config Driver::Ccm::Frac_pll1443::_compute(Rate fout) const
{
	/**
	 * Formula for Fraction PLLOUT from the reference manual
	 *  - FOUT = ( (m + k / 65536) * FIN) / p * 2^s)
	 *  - Where 1 <= p <= 63 and 64 <= m <= 1023 and 0 <= s <= 6 and -32768 <= k <= 32767
	 *  - Where p, m and s are unsigned integers, k is a two's complement integers
	 *  - Where, FOUT is the output frequency, FIN is the input frequency
	 *  - Where p is the division value for pre-divider
	 *  - Where m is the division value for main-divider
	 *  - Where s is the scaler value (aka post-divider)
	 *  - Where k is the DSM value
	 */

	/* Read current pll configuration */
	Pll14xx::Config cfg = _read();

	/* verify if k can be recomputed, resulting in a glitch free clk reconfiguration */
	Pll14xx::Config min_kdiv_cfg { .pdiv = cfg.pdiv, .mdiv = cfg.mdiv, .sdiv = cfg.sdiv, .kdiv = MIN_KDIV };
	Pll14xx::Config max_kdiv_cfg { .pdiv = cfg.pdiv, .mdiv = cfg.mdiv, .sdiv = cfg.sdiv, .kdiv = MAX_KDIV };
	Rate min_rate = _compute_rate(min_kdiv_cfg);
	Rate max_rate = _compute_rate(max_kdiv_cfg);

	if (fout.value <= max_rate.value && fout.value >= min_rate.value) {
		int16_t kdiv = _compute_kdiv(cfg, fout);
		cfg.kdiv = kdiv;
		cfg.rate = _compute_rate(cfg);
		return cfg;
	}

	Pll14xx::Config calc_cfg { cfg };
	int64_t deviation = -1UL >> 1;

	/* Calculate best values */
	for (calc_cfg.pdiv = 0; calc_cfg.pdiv <= 64; ++calc_cfg.pdiv) {

		for (calc_cfg.sdiv = 0; calc_cfg.sdiv <= 6; ++calc_cfg.sdiv) {

			uint64_t fin = _mmio.parent_rate().value;

			/* m = (fout * p * 2^s) / fin*/
			calc_cfg.mdiv = (fout.value * (calc_cfg.pdiv << calc_cfg.sdiv)) / fin;
			calc_cfg.mdiv = clamp(calc_cfg.mdiv, 64UL, 1023UL);

			/* re-calc k and compute rate */
			calc_cfg.kdiv = _compute_kdiv(calc_cfg, fout);
			calc_cfg.rate = _compute_rate(calc_cfg);

			/* calc deviation */
			int64_t dist = static_cast<int64_t>(fout.value - calc_cfg.rate.value);
			dist &= (-1UL >> 1);
			if (dist < deviation) {
				deviation = dist;
				cfg = calc_cfg;
				if (!deviation)
					return cfg;
			}
		}
	}
	return cfg;
}


void Driver::Ccm::Frac_pll1443::rate(Rate fout)
{
	/* recompute pll configuration */
	Pll14xx::Config cfg = _compute(fout);

	/* if and only if sdiv and kdiv changed */
	if (cfg.pdiv == _mmio.read<Pll14xx::Fdiv_ctl0::Pre_div>()
	    && cfg.mdiv == _mmio.read<Pll14xx::Fdiv_ctl0::Main_div>()) {
		_mmio.write<Pll14xx::Fdiv_ctl0::Post_div>(static_cast<uint32_t>(cfg.sdiv)); /* 0 <= sdiv <= 6 */
		_mmio.write<Pll14xx::Fdiv_ctl1::Dsm>(cfg.kdiv);
		return;
	}

	/* enable reset & by-pass */
	_mmio.write<Pll14xx::Gen_ctrl::Reset>(Pll14xx::Gen_ctrl::Reset::RESET);
	_mmio.write<Pll14xx::Gen_ctrl::Bypass>(1);

	/* reconfigure pll */
	_mmio.write<Pll14xx::Fdiv_ctl0::Pre_div>(static_cast<uint32_t>(cfg.pdiv));
	_mmio.write<Pll14xx::Fdiv_ctl0::Main_div>(static_cast<uint32_t>(cfg.mdiv));
	_mmio.write<Pll14xx::Fdiv_ctl0::Post_div>(static_cast<uint32_t>(cfg.sdiv)); /* 0 <= sdiv <= 6 */
	_mmio.write<Pll14xx::Fdiv_ctl1::Dsm>(cfg.kdiv);

	/* from there, the clock needs 3 cycles to be stabilized */

	/* disable reset */
	_mmio.write<Pll14xx::Gen_ctrl::Reset>(Pll14xx::Gen_ctrl::Reset::NO_RESET);

	/*
	 * Wait the PLL to achieved lock, ts output frequency and phase are
	 * synchronized with its input reference within acceptable tolerances.
	 */
	unsigned count = 0;
	while(!_mmio.read<Pll14xx::Gen_ctrl::Lock_signal>())
	{
		/* not using Timer::one_shot_timout is on purpose */
		if (count == 1024) {
			warning(" PLL=", name, " did not achieved lock.");
			break;
		}
		++count;
	}

	/* disable by-pass */
	_mmio.write<Pll14xx::Gen_ctrl::Bypass>(0);
	if (_verbose)
		log("Pll=", name, " new rate=", cfg.rate.value);
}


Driver::Clock::Rate Driver::Ccm::Frac_pll1443::rate() const
{
	Pll14xx::Config cfg = _read();
	if (_verbose)
		log("Pll=", name, " rate=", cfg.rate.value);
	return { cfg.rate };
}


Driver::Ccm::Frac_pll1443::Frac_pll1443(Clocks               &clocks,
                                        Name                  name,
                                        Byte_range_ptr const &range,
                                        bool                  verbose)
: Clock(clocks, name), _mmio(clocks, range), _verbose(verbose)
{
	if (_verbose)
		log("New PLL1443=", name,
		    " Ref_clk=", _mmio.read<Pll14xx::Gen_ctrl::Ref_clk_select>(),
		    " bypass=", _mmio.read<Pll14xx::Gen_ctrl::Bypass>(),
		    " reset=", _mmio.read<Pll14xx::Gen_ctrl::Reset>(),
		    " Gating_enable=", _mmio.read<Pll14xx::Gen_ctrl::Gating_enable>(),
		    " Lock_signal=", _mmio.read<Pll14xx::Gen_ctrl::Lock_signal>());
}


/**********************************
 ** Frac1446_pll immplementation **
 **********************************/

/* Fout = (Fin * m) / (p * 2^s)
 * - Where 1 <= p <= 63 and 64 <= m <= 1023 and 0 <= s <= 6
 * - Where p, m and s are unsigned integers
 * - Where, Fout is the output frequency, Fin is the input frequency
 * - Where p is the division value for pre-divider
 * - Where m is the division value for main-divider
 * - Where s is the scaler value (aka post-divider)
 */
static Driver::Ccm::Pll14xx::Config const pll1446_pre_calc_tbl[] {
	{ { 1800000000U }, 3, 225, 0, 0 },
	{ { 1600000000U }, 3, 200, 0, 0 },
	{ { 1500000000U }, 3, 375, 1, 0 },
	{ { 1400000000U }, 3, 350, 1, 0 },
	{ { 1200000000U }, 3, 300, 1, 0 },
	{ { 1200000000U }, 2, 200, 1, 0 },
	{ { 1000000000U }, 3, 250, 1, 0 },
	{ { 800000000U },  3, 200, 1, 0 },
	{ { 800000000U },  3, 400, 2, 0 },
	{ { 750000000U },  2, 250, 2, 0 },
	{ { 700000000U },  3, 350, 2, 0 },
	{ { 600000000U },  3, 300, 2, 0 },
};


void Driver::Ccm::Frac_pll1416::rate(Driver::Clock::Rate rate)
{
	Pll14xx::Config cfg {};

	for (Pll14xx::Config const &elem: pll1446_pre_calc_tbl) {
		if (rate.value == elem.rate.value) {
			cfg = elem;
		}
	}

	if (cfg.rate.value == 0UL) {
		error("PLL=", name, " rate=", rate.value, " could not be set.");
		return;
	}

	/* enable reset & by-pass */
	_mmio.write<Pll14xx::Gen_ctrl::Reset>(Pll14xx::Gen_ctrl::Reset::RESET);
	_mmio.write<Pll14xx::Gen_ctrl::Bypass>(1);

	/* reconfigure pll */
	_mmio.write<Pll14xx::Fdiv_ctl0::Pre_div>(static_cast<uint32_t>(cfg.pdiv));
	_mmio.write<Pll14xx::Fdiv_ctl0::Main_div>(static_cast<uint32_t>(cfg.mdiv));
	_mmio.write<Pll14xx::Fdiv_ctl0::Post_div>(static_cast<uint32_t>(cfg.sdiv)); /* 0 <= sdiv <= 6 */

	/* from there, the clock needs 3 cycles to be stabilized */

	/* disable reset */
	_mmio.write<Pll14xx::Gen_ctrl::Reset>(Pll14xx::Gen_ctrl::Reset::NO_RESET);

	/*
	 * Wait the PLL to achieved lock, ts output frequency and phase are
	 * synchronized with its input reference within acceptable tolerances.
	 */
	unsigned count = 0;
	while(!_mmio.read<Pll14xx::Gen_ctrl::Lock_signal>())
	{
		/* not using Timer::one_shot_timout is on purpose */
		if (count == 1024) {
			warning(" PLL=", name, " did not achieved lock.");
			break;
		}
		++count;
	}

	/* disable by-pass */
	_mmio.write<Pll14xx::Gen_ctrl::Bypass>(0);
	if (_verbose)
		log("Pll=", name, " new rate=", cfg.rate.value);
}


Driver::Clock::Rate Driver::Ccm::Frac_pll1416::rate() const
{
	Pll14xx::Config cfg {};
	cfg.pdiv = _mmio.read<Pll14xx::Fdiv_ctl0::Pre_div>();
	cfg.mdiv = _mmio.read<Pll14xx::Fdiv_ctl0::Main_div>();
	cfg.sdiv = _mmio.read<Pll14xx::Fdiv_ctl0::Post_div>();

	for (Pll14xx::Config const &elem: pll1446_pre_calc_tbl) {
		if (cfg == elem) {
			if (_verbose)
				log("Pll=", name, " rate=", elem.rate.value);
			return elem.rate;
		}
	}

	error("PLL=", name,
	      " pdiv=", cfg.pdiv,
	      " mdiv=", cfg.mdiv,
	      " sdiv=", cfg.sdiv,
	      " no such pre-calculated settings, rate() will return 0.");
	return Rate { 0 };
}


Driver::Ccm::Frac_pll1416::Frac_pll1416(Clocks               &clocks,
                                        Name                  name,
                                        Byte_range_ptr const &range,
                                        bool                  verbose)
: Clock { clocks, name }, _mmio { clocks, range }, _verbose { verbose }
{
	if (_verbose)
		log("New PLL1416=", name,
		    " Ref_clk=", _mmio.read<Pll14xx::Gen_ctrl::Ref_clk_select>(),
		    " bypass=", _mmio.read<Pll14xx::Gen_ctrl::Bypass>(),
		    " reset=", _mmio.read<Pll14xx::Gen_ctrl::Reset>(),
		    " Gating_enable=", _mmio.read<Pll14xx::Gen_ctrl::Gating_enable>(),
		    " Lock_signal=", _mmio.read<Pll14xx::Gen_ctrl::Lock_signal>());
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

Driver::Ccm::Ccm(Genode::Env       &env,
                 Clocks            &clocks,
                 bool               verbose)
: env { env }, clocks { clocks }, verbose { verbose }
{
	audio_pll1_clk.disable();
	audio_pll2_clk.disable();
	video_pll_clk.disable();
	gpu_pll_clk.disable();
	vpu_pll_clk.disable();
	system_pll3_clk.disable();

	/* turn off all unnecessary root clocks */
	arm_m7_clk_root.disable();
	ml_clk_root.disable();
	gpu3d_core_clk_r.disable();
	gpu3d_shader_clk_root.disable();
	gpu2d_clk_root.disable();
	audio_axi_clk_root.disable();
	hsio_axi_clk_root.disable();
	media_isp_clk_root.disable();
	main_axi_clk_root.disable();
	enet_axi_clk_root.disable();
	nand_usdhc_bus_clk_root.disable();
	vpu_bus_clk_root.disable();
	media_axi_clk_root.disable();
	media_apb_clk_root.disable();
	hdmi_apb_clk_root.disable();
	hdmi_axi_clk_root.disable();
	gpu_axi_clk_root.disable();
	gpu_ahb_clk_root.disable();
	noc_clk_root.disable();
	noc_io_clk_root.disable();
	ml_axi_clk_root.disable();
	ml_ahb_clk_root.disable();
	ahb_clk_root.disable();
	audio_ahb_clk_root.disable();
	media_disp2_clk_root.disable();
	vpu_g1_clk_root.disable();
	vpu_g2_clk_root.disable();
	can1_clk_root.disable();
	can2_clk_root.disable();
	memrepair_clk_root.disable();
	pcie_phy_clk_root.disable();
	pcie_aux_clk_root.disable();
	i2c5_clk_root.disable();
	i2c6_clk_root.disable();
	sai1_clk_root.disable();
	sai2_clk_root.disable();
	sai3_clk_root.disable();
	sai5_clk_root.disable();
	sai6_clk_root.disable();
	enet_qos_clk_root.disable();
	enet_qos_timer_clk_root.disable();
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
	uart1_clk_root.disable();
	uart2_clk_root.disable();
	uart3_clk_root.disable();
	uart4_clk_root.disable();
	gic_clk_root.disable();
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
	ipp_do_clko1.disable();
	ipp_do_clko2.disable();
	hdmi_fdcc_tst_clk_root.disable();
	hdmi_ref_266m_clk_root.disable();
	usdhc3_clk_root.disable();
	media_cam1_pix_clk_root.disable();
	media_mipi_phy1_ref_clk_root.disable();
	media_disp1_pix_clk_root.disable();
	media_cam2_pix_clk_root.disable();
	media_ldb_clk_root.disable();
	media_mipi_test_byte_clk.disable();
	ecspi3_clk_root.disable();
	pdm_clk_root.disable();
	vpu_vc8000e_clk_root.disable();
	sai7_clk_root.disable();
}
