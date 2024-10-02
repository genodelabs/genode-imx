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
		if (count == 2048) {
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
                                        bool                  verbose,
                                        bool const            never_disable)
:
	Clock(clocks, name),
	_mmio(clocks, range),
	_verbose(verbose),
	_never_disable(never_disable)
{
	_mmio.write<Pll14xx::Gen_ctrl::Bypass>(0);

	/*
	 * Enable within the clock tree if clock is on,
	 * because there are potentially root-clocks enabled and configured to use
	 * this PLL, disable it in the end when all clocks are initialized
	 */
	if (_mmio.read<Pll14xx::Gen_ctrl::Reset>()) enable();
	else _disable();

	if (_verbose)
		log("New PLL1443=", name,
		    " Ref_clk=", _mmio.read<Pll14xx::Gen_ctrl::Ref_clk_select>(),
		    " bypass=", _mmio.read<Pll14xx::Gen_ctrl::Bypass>(),
		    " reset=", _mmio.read<Pll14xx::Gen_ctrl::Reset>(),
		    " Gating_enable=", _mmio.read<Pll14xx::Gen_ctrl::Enable_1443>(),
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
	_mmio.wait_for_lock();

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
                                        bool                  verbose,
                                        bool const            never_disable)
:
	Clock(clocks, name),
	_mmio(clocks, range),
	_verbose(verbose),
	_never_disable(never_disable)
{
	_mmio.write<Pll14xx::Gen_ctrl::Bypass>(0);

	/*
	 * Enable within the clock tree if clock is on,
	 * because there are potentially root-clocks enabled and configured to use
	 * this PLL, disable it in the end when all clocks are initialized
	 */
	if (_mmio.read<Pll14xx::Gen_ctrl::Reset>()) enable();
	else _disable();

	if (_verbose)
		log("New PLL1416=", name,
		    " Ref_clk=", _mmio.read<Pll14xx::Gen_ctrl::Ref_clk_select>(),
		    " bypass=", _mmio.read<Pll14xx::Gen_ctrl::Bypass>(),
		    " reset=", _mmio.read<Pll14xx::Gen_ctrl::Reset>(),
		    " Gating_enable=", _mmio.read<Pll14xx::Gen_ctrl::Enable_1416>(),
		    " Lock_signal=", _mmio.read<Pll14xx::Gen_ctrl::Lock_signal>());
}


/*******************
 ** CCM interface **
 *******************/

Driver::Ccm::Ccm(Genode::Env       &env,
                 Clocks            &clocks,
                 bool               verbose)
: env { env }, clocks { clocks }, verbose { verbose }
{
	/*
	 * Now we can safely disable clocks. If there are still root-clocks
	 * depending on it, ref-counting will protect us from disabling it
	 */
	audio_pll1_clk.disable();
	audio_pll2_clk.disable();
	gpu_pll_clk.disable();
	vpu_pll_clk.disable();
	system_pll3_clk.disable();
}
