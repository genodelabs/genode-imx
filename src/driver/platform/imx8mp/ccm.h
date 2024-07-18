/*
 * \brief  Central clock module for i.MX8MP
 * \author Stefan Kalkowski
 * \author Alice Domage
 * \date   2024-03-14
 */

/*
 * Copyright (C) 2024 Genode Labs GmbH
 * Copyright (C) 2024 gapfruit ag
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#pragma once

#include <common/ccm.h>

namespace Driver {
	using namespace Genode;

	struct Ccm;
};

/* Clock Control Module */
struct Driver::Ccm
{

	/* Fractional-n implementation for pll */
	/* 
	 * This could could be made common to imx8mq, imx8mp, imx8mm as they
	 * all uses variant of those PLLs.
	 */

	/**
	 * Handle general operation for Pll14xx based clock
	 *  - enabel / disable
	 *  - set parent
	 *  - get parent rate
	 */
	struct Pll14xx: Mmio<0xC>
	{
		struct Gen_ctrl: Register<0x0, 32> {
			struct Ref_clk_select: Bitfield<0, 2> {
				enum Ref_clk { REF_CLK_24M, CLK_PAD };
			};
			struct Bypass: Bitfield<4, 1> {};
			struct Reset: Bitfield<9, 1> {
				enum State { RESET = 0, NO_RESET = 1 };
			};
			struct Enable_1416: Bitfield<11, 1> {};
			struct Enable_1443: Bitfield<13, 1> {};
			struct Lock_signal: Bitfield<31, 1> {};
		};

		struct Fdiv_ctl0: Register<0x4, 32> {
			struct Post_div: Bitfield<0, 3> {};
			struct Pre_div: Bitfield<4, 6> {};
			struct Main_div: Bitfield<12, 10> {};
		};

		struct Fdiv_ctl1: Register<0x8, 32> {
			struct Dsm: Bitfield <0, 16> {};
		};

		struct Config
		{
			Clock::Rate rate { 0 }; /* maybe 0, in shuch case .rate should be ignored */
			uint64_t    pdiv { 0 }; /* pre-divider */
			uint64_t    mdiv { 0 }; /* main divider */
			uint64_t    sdiv { 0 }; /* scaler */
			int16_t     kdiv { 0 }; /* DSM */

			bool operator==(Pll14xx::Config const &other) const
			{ return other.pdiv == pdiv && other.mdiv == mdiv && other.sdiv == sdiv && other.kdiv == kdiv; }
		};

		Clocks &_clocks;

		Pll14xx(Clocks &clocks, Genode::Byte_range_ptr const &range)
		: Mmio(range), _clocks { clocks } {}

		template <typename FN>
		void parent(FN const & fn) const
		{
			Clock::Name pname;
			switch (read<Pll14xx::Gen_ctrl::Ref_clk_select>()) {
				case Pll14xx::Gen_ctrl::Ref_clk_select::REF_CLK_24M: pname = "24m_ref_clk"; break;
				case Pll14xx::Gen_ctrl::Ref_clk_select::CLK_PAD:     pname = "no_clk";      break;
			};
			_clocks.apply(pname, [&] (Clock & clock) { fn(clock); });
		}

		Clock::Name parent(Clock::Name parent)
		{
			if (parent == "24m_ref_clk") {
				write<Gen_ctrl::Ref_clk_select>(Gen_ctrl::Ref_clk_select::REF_CLK_24M);
				return parent;
			}
			write<Gen_ctrl::Ref_clk_select>(Gen_ctrl::Ref_clk_select::CLK_PAD);
			return "clk_pad";
		}

		Clock::Rate parent_rate() const
		{
			uint64_t fin = 0;
			parent([&] (Clock & clock) { fin = clock.rate().value; });
			return { fin };
		}

		void wait_for_lock()
		{
			unsigned count = 0;
			while(!read<Gen_ctrl::Lock_signal>())
			{
				/* not using Timer::one_shot_timout is on purpose */
				if (count == 1024) {
					warning(" PLL did not achieved lock.");
					break;
				}
				++count;
			}
		}

		template <typename T>
		void enable()
		{
			if (read<T>() && read<Gen_ctrl::Reset>())
				return;

			write<Gen_ctrl::Bypass>(1);
			write<Gen_ctrl::Reset>(Gen_ctrl::Reset::NO_RESET);

			wait_for_lock();

			write<Gen_ctrl::Bypass>(0);
			write<T>(1);
		}

		template <typename T>
		void disable()
		{
			write<T>(0);
			write<Gen_ctrl::Reset>(Gen_ctrl::Reset::RESET);
		}
	};

	class Frac_pll1443: public Clock
	{
		private:

			Pll14xx    _mmio;
			bool       _verbose;
			bool const _never_disable;

			static constexpr int64_t MIN_KDIV = -32768;
			static constexpr int64_t MAX_KDIV = 32767;

			Pll14xx::Config _read() const;
			int16_t         _compute_kdiv(Pll14xx::Config &cfg, Rate fout) const;
			Rate            _compute_rate(Pll14xx::Config &cfg) const;
			Pll14xx::Config _compute(Rate rate) const;

		public:

			Frac_pll1443(Clocks               &clocks,
			             Name                  name,
			             Byte_range_ptr const &range,
			             bool                  verbose,
			             bool const            never_disable = false);

			void rate(Rate name)   override;
			Rate rate() const      override;

			void parent(Name name) override
			{
				Name new_parent = _mmio.parent(name);
				if (_verbose)
					log("PLL=", name, " Ref_clk_select=", new_parent);
			}

			void _enable() override {
				_mmio.enable<Pll14xx::Gen_ctrl::Enable_1443>(); }

			void _disable() override
			{
				if (_never_disable)
					return;

				_mmio.disable<Pll14xx::Gen_ctrl::Enable_1443>();
			}
	};

	class Frac_pll1416: public Clock
	{
		private:

			Pll14xx    _mmio;
			bool const _verbose;
			bool const _never_disable;

		public:

			Frac_pll1416(Clocks               &clocks,
			             Name                  name,
			             Byte_range_ptr const &range,
			             bool                  verbose,
			             bool const            never_disable = false);

			virtual void rate(Rate rate) override;
			virtual Rate rate() const    override;

			void parent(Name name) override
			{
				Name new_parent = _mmio.parent(name);
				if (_verbose)
					log("PLL=", name, " Ref_clk_select=", new_parent);
			}

			void _enable() override {
				_mmio.enable<Pll14xx::Gen_ctrl::Enable_1416>(); }

			void _disable() override
			{
				if (_never_disable)
					return;

				_mmio.disable<Pll14xx::Gen_ctrl::Enable_1416>();
			}
	};

	using Root_clock         = ::Ccm::Root_clock;
	using Root_clock_divider = ::Ccm::Root_clock_divider;
	using Gate               = ::Ccm::Gate;

	/* TODO: Spread Spectrum Clock Generator Controller (if necessary) */

	enum {
		CCM_MMIO_BASE        = 0x30380000,
		CCM_MMIO_SIZE        = 0x10000,
		CCM_ANALOG_MMIO_BASE = 0x30360000,
		CCM_ANALOG_MMIO_SIZE = 0x10000,
	};

	Ccm(Genode::Env & env, Clocks & clocks, bool verbose);

	Genode::Env        &env;
	Clocks             &clocks;
	bool               verbose;
	Attached_mmio<0>   ccm_regs        { env, {(char *)CCM_MMIO_BASE, CCM_MMIO_SIZE} };
	Attached_mmio<0>   ccm_analog_regs { env, {(char *)CCM_ANALOG_MMIO_BASE, CCM_ANALOG_MMIO_SIZE} };

	Byte_range_ptr frac_pll_range(unsigned pll) {
		return ccm_analog_regs.range_at(pll); }

	Byte_range_ptr sccg_pll_range(unsigned pll) {
		return ccm_analog_regs.range_at(0x30 + pll*0xc); }

	Byte_range_ptr gate_range(unsigned nr) {
		return ccm_regs.range_at(0x4000 + nr*0x10); }

	Byte_range_ptr root_range(unsigned nr) {
		return ccm_regs.range_at(0x8000 + nr*0x80); }

	Fixed_clock no_clk      { clocks, "no_clk",      {                 0 }};
	Fixed_clock k32_ref_clk { clocks, "32k_ref_clk", {         32 * 1000 }};
	Fixed_clock m24_ref_clk { clocks, "24m_ref_clk", {  24 * 1000 * 1000 }};
	Fixed_clock ext_clk_1   { clocks, "ext_clk_1",   { 133 * 1000 * 1000 }};
	Fixed_clock ext_clk_2   { clocks, "ext_clk_2",   { 133 * 1000 * 1000 }};
	Fixed_clock ext_clk_3   { clocks, "ext_clk_3",   { 133 * 1000 * 1000 }};
	Fixed_clock ext_clk_4   { clocks, "ext_clk_4",   { 133 * 1000 * 1000 }};

	Frac_pll1443 audio_pll1_clk { clocks, "audio_pll1_clk", frac_pll_range(0x00), verbose };
	Frac_pll1443 audio_pll2_clk { clocks, "audio_pll2_clk", frac_pll_range(0x14), verbose };
	Frac_pll1443 video_pll_clk  { clocks, "video_pll1_clk", frac_pll_range(0x28), verbose };
	Frac_pll1443 dram_pll_clk   { clocks, "dram_pll_clk",   frac_pll_range(0x50), verbose, true };

	Frac_pll1416 gpu_pll_clk { clocks, "gpu_pll_clk", frac_pll_range(0x64), verbose };
	Frac_pll1416 vpu_pll_clk { clocks, "vpu_pll_clk", frac_pll_range(0x74), verbose };
	Frac_pll1416 arm_pll_clk { clocks, "arm_pll_clk", frac_pll_range(0x84), verbose, true };

	Frac_pll1416 system_pll1_clk { clocks, "system_pll1_clk", frac_pll_range(0x94),  verbose, true };
	Frac_pll1416 system_pll2_clk { clocks, "system_pll2_clk", frac_pll_range(0x104), verbose, true };
	Frac_pll1416 system_pll3_clk { clocks, "system_pll3_clk", frac_pll_range(0x114), verbose };

	Fixed_divider system_pll1_div20 { clocks, "system_pll1_div20", system_pll1_clk, {20} };
	Fixed_divider system_pll1_div10 { clocks, "system_pll1_div10", system_pll1_clk, {10} };
	Fixed_divider system_pll1_div8  { clocks, "system_pll1_div8",  system_pll1_clk, { 8} };
	Fixed_divider system_pll1_div6  { clocks, "system_pll1_div6",  system_pll1_clk, { 6} };
	Fixed_divider system_pll1_div5  { clocks, "system_pll1_div5",  system_pll1_clk, { 5} };
	Fixed_divider system_pll1_div4  { clocks, "system_pll1_div4",  system_pll1_clk, { 4} };
	Fixed_divider system_pll1_div3  { clocks, "system_pll1_div3",  system_pll1_clk, { 3} };
	Fixed_divider system_pll1_div2  { clocks, "system_pll1_div2",  system_pll1_clk, { 2} };
	Fixed_divider system_pll2_div20 { clocks, "system_pll2_div20", system_pll2_clk, {20} };
	Fixed_divider system_pll2_div10 { clocks, "system_pll2_div10", system_pll2_clk, {10} };
	Fixed_divider system_pll2_div8  { clocks, "system_pll2_div8",  system_pll2_clk, { 8} };
	Fixed_divider system_pll2_div6  { clocks, "system_pll2_div6",  system_pll2_clk, { 6} };
	Fixed_divider system_pll2_div5  { clocks, "system_pll2_div5",  system_pll2_clk, { 5} };
	Fixed_divider system_pll2_div4  { clocks, "system_pll2_div4",  system_pll2_clk, { 4} };
	Fixed_divider system_pll2_div3  { clocks, "system_pll2_div3",  system_pll2_clk, { 3} };
	Fixed_divider system_pll2_div2  { clocks, "system_pll2_div2",  system_pll2_clk, { 2} };

	/* Root_clock automatically extracted from the specification with extract_clock_root.py */
	Root_clock arm_a53_clk_root              { clocks, "arm_a53_clk_root",
	                                           root_range(0), m24_ref_clk,
	                                           arm_pll_clk, system_pll2_div2,
	                                           system_pll2_clk, system_pll1_clk,
	                                           system_pll1_div2, audio_pll1_clk,
	                                           system_pll3_clk, true };
	Root_clock arm_m7_clk_root               { clocks, "arm_m7_clk_root",
	                                           root_range(1), m24_ref_clk,
	                                           system_pll2_div5, system_pll2_div4,
	                                           vpu_pll_clk, system_pll1_clk,
	                                           audio_pll1_clk, video_pll_clk,
	                                           system_pll3_clk };
	Root_clock ml_clk_root                   { clocks, "ml_clk_root",
	                                           root_range(2), m24_ref_clk,
	                                           gpu_pll_clk, system_pll1_clk,
	                                           system_pll3_clk, system_pll2_clk,
	                                           audio_pll1_clk, video_pll_clk,
	                                           audio_pll2_clk };
	Root_clock gpu3d_core_clk_r              { clocks, "gpu3d_core_clk_root",
	                                           root_range(3), m24_ref_clk,
	                                           gpu_pll_clk, system_pll1_clk,
	                                           system_pll3_clk, system_pll2_clk,
	                                           audio_pll1_clk, video_pll_clk,
	                                           audio_pll2_clk };
	Root_clock gpu3d_shader_clk_root        { clocks, "gpu3d_shader_clk_root",
	                                           root_range(4), m24_ref_clk,
	                                           gpu_pll_clk, system_pll1_clk,
	                                           system_pll3_clk, system_pll2_clk,
	                                           audio_pll1_clk, video_pll_clk,
	                                           audio_pll2_clk };
	Root_clock gpu2d_clk_root                { clocks, "gpu2d_clk_root",
	                                           root_range(5), m24_ref_clk,
	                                           gpu_pll_clk, system_pll1_clk,
	                                           system_pll3_clk, system_pll2_clk,
	                                           audio_pll1_clk, video_pll_clk,
	                                           audio_pll2_clk };
	Root_clock audio_axi_clk_root            { clocks, "audio_axi_clk_root",
	                                           root_range(6), m24_ref_clk,
	                                           gpu_pll_clk, system_pll1_clk,
	                                           system_pll3_clk, system_pll2_clk,
	                                           audio_pll1_clk, video_pll_clk,
	                                           audio_pll2_clk };
	Root_clock hsio_axi_clk_root            { clocks, "hsio_axi_clk_root",
	                                           root_range(7), m24_ref_clk,
	                                           system_pll2_div2, system_pll1_clk,
	                                           system_pll2_div10, system_pll2_div5,
	                                           ext_clk_2, ext_clk_4,
	                                           audio_pll2_clk };
	Root_clock media_isp_clk_root            { clocks, "media_isp_clk_root",
	                                           root_range(8), m24_ref_clk,
	                                           system_pll2_clk, system_pll1_clk,
	                                           system_pll3_clk, system_pll1_div20,
	                                           audio_pll2_clk, ext_clk_1,
	                                           system_pll2_div2 };
	Root_clock main_axi_clk_root             { clocks, "main_axi_clk_root",
	                                           root_range(16), m24_ref_clk,
	                                           system_pll2_div3, system_pll1_clk,
	                                           system_pll2_div4, system_pll2_clk,
	                                           audio_pll1_clk, video_pll_clk,
	                                           system_pll1_div8, true };
	Root_clock enet_axi_clk_root             { clocks, "enet_axi_clk_root",
	                                           root_range(17), m24_ref_clk,
	                                           system_pll1_div3, system_pll1_clk,
	                                           system_pll2_div4, system_pll2_div5,
	                                           audio_pll1_clk, video_pll_clk,
	                                           system_pll3_clk };
	Root_clock nand_usdhc_bus_clk_root       { clocks, "nand_usdhc_bus_clk_root",
	                                           root_range(18), m24_ref_clk,
	                                           system_pll1_div3, system_pll1_clk,
	                                           system_pll2_div5, system_pll1_div6,
	                                           system_pll3_clk, system_pll2_div4,
	                                           audio_pll1_clk };
	Root_clock vpu_bus_clk_root              { clocks, "vpu_bus_clk_root",
	                                           root_range(19), m24_ref_clk,
	                                           system_pll1_clk, vpu_pll_clk,
	                                           audio_pll2_clk, system_pll3_clk,
	                                           system_pll2_clk, system_pll2_div5,
	                                           system_pll1_div8 };
	Root_clock media_axi_clk_root            { clocks, "media_axi_clk_root",
	                                           root_range(20), m24_ref_clk,
	                                           system_pll2_clk, system_pll1_clk,
	                                           system_pll3_clk, system_pll1_div20,
	                                           audio_pll2_clk, ext_clk_1,
	                                           system_pll2_div2 };
	Root_clock media_apb_clk_root           { clocks, "media_apb_clk_root",
	                                           root_range(21), m24_ref_clk,
	                                           system_pll2_div8, system_pll1_clk,
	                                           system_pll3_clk, system_pll1_div20,
	                                           audio_pll2_clk, ext_clk_1,
	                                           system_pll1_div6 };
	Root_clock hdmi_apb_clk_root             { clocks, "hdmi_apb_clk_root",
	                                           root_range(22), m24_ref_clk,
	                                           system_pll2_div8, system_pll1_clk,
	                                           system_pll3_clk, system_pll1_div20,
	                                           audio_pll2_clk, ext_clk_1,
	                                           system_pll1_div6 };
	Root_clock hdmi_axi_clk_root             { clocks, "hdmi_axi_clk_root",
	                                           root_range(23), m24_ref_clk,
	                                           system_pll2_clk, system_pll1_clk,
	                                           system_pll3_clk, system_pll1_div20,
	                                           audio_pll2_clk, ext_clk_1,
	                                           system_pll2_div2 };
	Root_clock gpu_axi_clk_root              { clocks, "gpu_axi_clk_root",
	                                           root_range(24), m24_ref_clk,
	                                           system_pll1_clk, gpu_pll_clk,
	                                           system_pll3_clk, system_pll2_clk,
	                                           audio_pll1_clk, video_pll_clk,
	                                           audio_pll2_clk };
	Root_clock gpu_ahb_clk_root              { clocks, "gpu_ahb_clk_root",
	                                           root_range(25), m24_ref_clk,
	                                           system_pll1_clk, gpu_pll_clk,
	                                           system_pll3_clk, system_pll2_clk,
	                                           audio_pll1_clk, video_pll_clk,
	                                           audio_pll2_clk };
	Root_clock noc_clk_root                  { clocks, "noc_clk_root",
	                                           root_range(26), m24_ref_clk,
	                                           system_pll1_clk, system_pll3_clk,
	                                           system_pll2_clk, system_pll2_div2,
	                                           audio_pll1_clk, video_pll_clk,
	                                           audio_pll2_clk, true };
	Root_clock noc_io_clk_root               { clocks, "noc_io_clk_root",
	                                           root_range(27), m24_ref_clk,
	                                           system_pll1_clk, system_pll3_clk,
	                                           system_pll2_clk, system_pll2_div2,
	                                           audio_pll1_clk, video_pll_clk,
	                                           audio_pll2_clk };
	Root_clock ml_axi_clk_root               { clocks, "ml_axi_clk_root",
	                                           root_range(28), m24_ref_clk,
	                                           system_pll1_clk, gpu_pll_clk,
	                                           system_pll3_clk, system_pll2_clk,
	                                           audio_pll1_clk, video_pll_clk,
	                                           audio_pll2_clk };
	Root_clock ml_ahb_clk_root               { clocks, "ml_ahb_clk_root",
	                                           root_range(29), m24_ref_clk,
	                                           system_pll1_clk, gpu_pll_clk,
	                                           system_pll3_clk, system_pll2_clk,
	                                           audio_pll1_clk, video_pll_clk,
	                                           audio_pll2_clk };
	Root_clock ahb_clk_root                  { clocks, "ahb_clk_root",
	                                           root_range(32), m24_ref_clk,
	                                           system_pll1_div6, system_pll1_clk,
	                                           system_pll1_div2, system_pll2_div8,
	                                           system_pll3_clk, audio_pll1_clk,
	                                           video_pll_clk, true};
	Root_clock audio_ahb_clk_root            { clocks, "audio_ahb_clk_root",
	                                           root_range(34), m24_ref_clk,
	                                           system_pll2_div2, system_pll1_clk,
	                                           system_pll2_clk, system_pll2_div6,
	                                           system_pll3_clk, audio_pll1_clk,
	                                           video_pll_clk };
	Root_clock media_disp2_clk_root          { clocks, "media_disp2_clk_root",
	                                           root_range(38), m24_ref_clk,
	                                           video_pll_clk, audio_pll2_clk,
	                                           audio_pll1_clk, system_pll1_clk,
	                                           system_pll2_clk, system_pll3_clk,
	                                           ext_clk_4 };
	Root_clock dram_alt_clk_root             { clocks, "dram_alt_clk_root",
	                                           root_range(64), m24_ref_clk,
	                                           system_pll1_clk, system_pll1_div8,
	                                           system_pll2_div2, system_pll2_clk,
	                                           system_pll3_clk, audio_pll1_clk,
	                                           system_pll1_div3, true };
	Root_clock dram_apb_clk_root             { clocks, "dram_apb_clk_root",
	                                           root_range(65), m24_ref_clk,
	                                           system_pll2_div5, system_pll1_div20,
	                                           system_pll1_div5, system_pll1_clk,
	                                           system_pll3_clk, system_pll2_div4,
	                                           audio_pll2_clk, true };
	Root_clock vpu_g1_clk_root               { clocks, "vpu_g1_clk_root",
	                                           root_range(66), m24_ref_clk,
	                                           vpu_pll_clk, system_pll1_clk,
	                                           system_pll2_clk, system_pll1_div8,
	                                           system_pll2_div8, system_pll3_clk,
	                                           audio_pll1_clk };
	Root_clock vpu_g2_clk_root               { clocks, "vpu_g2_clk_root",
	                                           root_range(67), m24_ref_clk,
	                                           vpu_pll_clk, system_pll1_clk,
	                                           system_pll2_clk, system_pll1_div8,
	                                           system_pll2_div8, system_pll3_clk,
	                                           audio_pll1_clk };
	Root_clock can1_clk_root                 { clocks, "can1_clk_root",
	                                           root_range(68), m24_ref_clk,
	                                           system_pll2_div5, system_pll1_div20,
	                                           system_pll1_div5, system_pll1_clk,
	                                           system_pll3_clk, system_pll2_div4,
	                                           audio_pll2_clk };
	Root_clock can2_clk_root                 { clocks, "can2_clk_root",
	                                           root_range(69), m24_ref_clk,
	                                           system_pll2_div5, system_pll1_div20,
	                                           system_pll1_div5, system_pll1_clk,
	                                           system_pll3_clk, system_pll2_div4,
	                                           audio_pll2_clk };
	Root_clock memrepair_clk_root            { clocks, "memrepair_clk_root",
	                                           root_range(70), m24_ref_clk,
	                                           system_pll1_div5, system_pll2_div20,
	                                           system_pll3_clk, audio_pll1_clk,
	                                           video_pll_clk, audio_pll2_clk,
	                                           system_pll1_div6 };
	Root_clock pcie_phy_clk_root             { clocks, "pcie_phy_clk_root",
	                                           root_range(71), m24_ref_clk,
	                                           system_pll2_div10, system_pll2_div2,
	                                           ext_clk_1, ext_clk_2,
	                                           ext_clk_3, ext_clk_4,
	                                           system_pll1_div2 };
	Root_clock pcie_aux_clk_root             { clocks, "pcie_aux_clk_root",
	                                           root_range(72), m24_ref_clk,
	                                           system_pll2_div5, system_pll2_div20,
	                                           system_pll3_clk, system_pll2_div10,
	                                           system_pll1_div10, system_pll1_div5,
	                                           system_pll1_div4 };
	Root_clock i2c5_clk_root                 { clocks, "i2c5_clk_root",
	                                           root_range(73), m24_ref_clk,
	                                           system_pll1_div5, system_pll2_div20,
	                                           system_pll3_clk, audio_pll1_clk,
	                                           video_pll_clk, audio_pll2_clk,
	                                           system_pll1_div6 };
	Root_clock i2c6_clk_root                 { clocks, "i2c6_clk_root",
	                                           root_range(74), m24_ref_clk,
	                                           system_pll1_div5, system_pll2_div20,
	                                           system_pll3_clk, audio_pll1_clk,
	                                           video_pll_clk, audio_pll2_clk,
	                                           system_pll1_div6 };
	Root_clock sai1_clk_root                 { clocks, "sai1_clk_root",
	                                           root_range(75), m24_ref_clk,
	                                           audio_pll1_clk, audio_pll2_clk,
	                                           video_pll_clk, system_pll1_div6,
	                                           no_clk, ext_clk_1,
	                                           ext_clk_2 };
	Root_clock sai2_clk_root                 { clocks, "sai2_clk_root",
	                                           root_range(76), m24_ref_clk,
	                                           audio_pll1_clk, audio_pll2_clk,
	                                           video_pll_clk, system_pll1_div6,
	                                           no_clk, ext_clk_2,
	                                           ext_clk_3 };
	Root_clock sai3_clk_root                 { clocks, "sai3_clk_root",
	                                           root_range(77), m24_ref_clk,
	                                           audio_pll1_clk, audio_pll2_clk,
	                                           video_pll_clk, system_pll1_div6,
	                                           no_clk, ext_clk_3,
	                                           ext_clk_4 };
	Root_clock sai5_clk_root                 { clocks, "sai5_clk_root",
	                                           root_range(79), m24_ref_clk,
	                                           audio_pll1_clk, audio_pll2_clk,
	                                           video_pll_clk, system_pll1_div6,
	                                           no_clk, ext_clk_2,
	                                           ext_clk_3 };
	Root_clock sai6_clk_root                 { clocks, "sai6_clk_root",
	                                           root_range(80), m24_ref_clk,
	                                           audio_pll1_clk, audio_pll2_clk,
	                                           video_pll_clk, system_pll1_div6,
	                                           no_clk, ext_clk_3,
	                                           ext_clk_4 };
	Root_clock enet_qos_clk_root             { clocks, "enet_qos_clk_root",
	                                           root_range(81), m24_ref_clk,
	                                           system_pll2_div8, system_pll2_div20,
	                                           system_pll2_div10, system_pll1_div5,
	                                           audio_pll1_clk, video_pll_clk,
	                                           ext_clk_4 };
	Root_clock enet_qos_timer_clk_root       { clocks, "enet_qos_timer_clk_root",
	                                           root_range(82), m24_ref_clk,
	                                           system_pll2_div10, audio_pll1_clk,
	                                           ext_clk_1, ext_clk_2,
	                                           ext_clk_3, ext_clk_4,
	                                           video_pll_clk };
	Root_clock enet_ref_clk_root             { clocks, "enet_ref_clk_root",
	                                           root_range(83), m24_ref_clk,
	                                           system_pll2_div8, system_pll2_div20,
	                                           system_pll2_div10, system_pll1_div5,
	                                           audio_pll1_clk, video_pll_clk,
	                                           ext_clk_4 };
	Root_clock enet_timer_clk_root           { clocks, "enet_timer_clk_root",
	                                           root_range(84), m24_ref_clk,
	                                           system_pll2_div10, audio_pll1_clk,
	                                           ext_clk_1, ext_clk_2,
	                                           ext_clk_3, ext_clk_4,
	                                           video_pll_clk };
	Root_clock enet_phy_ref_clk_root         { clocks, "enet_phy_ref_clk_root",
	                                           root_range(85), m24_ref_clk,
	                                           system_pll2_div20, system_pll2_div8,
	                                           system_pll2_div5, system_pll2_div2,
	                                           audio_pll1_clk, video_pll_clk,
	                                           audio_pll2_clk };
	Root_clock nand_clk_root                 { clocks, "nand_clk_root",
	                                           root_range(86), m24_ref_clk,
	                                           system_pll2_div2, audio_pll1_clk,
	                                           system_pll1_div2, audio_pll2_clk,
	                                           system_pll3_clk, system_pll2_div4,
	                                           video_pll_clk };
	Root_clock qspi_clk_root                 { clocks, "qspi_clk_root",
	                                           root_range(87), m24_ref_clk,
	                                           system_pll1_div2, system_pll2_div3,
	                                           system_pll2_div2, audio_pll2_clk,
	                                           system_pll1_div3, system_pll3_clk,
	                                           system_pll1_div8 };
	Root_clock usdhc1_clk_root               { clocks, "usdhc1_clk_root",
	                                           root_range(88), m24_ref_clk,
	                                           system_pll1_div2, system_pll1_clk,
	                                           system_pll2_div2, system_pll3_clk,
	                                           system_pll1_div3, audio_pll2_clk,
	                                           system_pll1_div8 };
	Root_clock usdhc2_clk_root               { clocks, "usdhc2_clk_root",
	                                           root_range(89), m24_ref_clk,
	                                           system_pll1_div2, system_pll1_clk,
	                                           system_pll2_div2, system_pll3_clk,
	                                           system_pll1_div3, audio_pll2_clk,
	                                           system_pll1_div8 };
	Root_clock i2c1_clk_root                 { clocks, "i2c1_clk_root",
	                                           root_range(90), m24_ref_clk,
	                                           system_pll1_div5, system_pll2_div20,
	                                           system_pll3_clk, audio_pll1_clk,
	                                           video_pll_clk, audio_pll2_clk,
	                                           system_pll1_div6 };
	Root_clock i2c2_clk_root                 { clocks, "i2c2_clk_root",
	                                           root_range(91), m24_ref_clk,
	                                           system_pll1_div5, system_pll2_div20,
	                                           system_pll3_clk, audio_pll1_clk,
	                                           video_pll_clk, audio_pll2_clk,
	                                           system_pll1_div6 };
	Root_clock i2c3_clk_root                 { clocks, "i2c3_clk_root",
	                                           root_range(92), m24_ref_clk,
	                                           system_pll1_div5, system_pll2_div20,
	                                           system_pll3_clk, audio_pll1_clk,
	                                           video_pll_clk, audio_pll2_clk,
	                                           system_pll1_div6 };
	Root_clock i2c4_clk_root                 { clocks, "i2c4_clk_root",
	                                           root_range(93), m24_ref_clk,
	                                           system_pll1_div5, system_pll2_div20,
	                                           system_pll3_clk, audio_pll1_clk,
	                                           video_pll_clk, audio_pll2_clk,
	                                           system_pll1_div6 };
	Root_clock uart1_clk_root                { clocks, "uart1_clk_root",
	                                           root_range(94), m24_ref_clk,
	                                           system_pll1_div10, system_pll2_div5,
	                                           system_pll2_div10, system_pll3_clk,
	                                           ext_clk_2, ext_clk_4,
	                                           audio_pll2_clk };
	Root_clock uart2_clk_root                { clocks, "uart2_clk_root",
	                                           root_range(95), m24_ref_clk,
	                                           system_pll1_div10, system_pll2_div5,
	                                           system_pll2_div10, system_pll3_clk,
	                                           ext_clk_2, ext_clk_3,
	                                           audio_pll2_clk, true };
	Root_clock uart3_clk_root                { clocks, "uart3_clk_root",
	                                           root_range(96), m24_ref_clk,
	                                           system_pll1_div10, system_pll2_div5,
	                                           system_pll2_div10, system_pll3_clk,
	                                           ext_clk_2, ext_clk_4,
	                                           audio_pll2_clk };
	Root_clock uart4_clk_root                { clocks, "uart4_clk_root",
	                                           root_range(97), m24_ref_clk,
	                                           system_pll1_div10, system_pll2_div5,
	                                           system_pll2_div10, system_pll3_clk,
	                                           ext_clk_2, ext_clk_3,
	                                           audio_pll2_clk };
	Root_clock gic_clk_root                  { clocks, "gic_clk_root",
	                                           root_range(100), m24_ref_clk,
	                                           system_pll2_div5, system_pll1_div20,
	                                           system_pll2_div10, system_pll1_clk,
	                                           system_pll2_div2, ext_clk_4,
	                                           audio_pll2_clk, true };
	Root_clock ecspi1_clk_root               { clocks, "ecspi1_clk_root",
	                                           root_range(101), m24_ref_clk,
	                                           system_pll2_div5, system_pll1_div20,
	                                           system_pll1_div5, system_pll1_clk,
	                                           system_pll3_clk, system_pll2_div4,
	                                           audio_pll2_clk };
	Root_clock ecspi2_clk_root               { clocks, "ecspi2_clk_root",
	                                           root_range(102), m24_ref_clk,
	                                           system_pll2_div5, system_pll1_div20,
	                                           system_pll1_div5, system_pll1_clk,
	                                           system_pll3_clk, system_pll2_div4,
	                                           audio_pll2_clk };
	Root_clock pwm1_clk_root                 { clocks, "pwm1_clk_root",
	                                           root_range(103), m24_ref_clk,
	                                           system_pll2_div10, system_pll1_div5,
	                                           system_pll1_div20, system_pll3_clk,
	                                           ext_clk_1, system_pll1_div10,
	                                           video_pll_clk };
	Root_clock pwm2_clk_root                 { clocks, "pwm2_clk_root",
	                                           root_range(104), m24_ref_clk,
	                                           system_pll2_div10, system_pll1_div5,
	                                           system_pll1_div20, system_pll3_clk,
	                                           ext_clk_1, system_pll1_div10,
	                                           video_pll_clk };
	Root_clock pwm3_clk_root                 { clocks, "pwm3_clk_root",
	                                           root_range(105), m24_ref_clk,
	                                           system_pll2_div10, system_pll1_div5,
	                                           system_pll1_div20, system_pll3_clk,
	                                           ext_clk_2, system_pll1_div10,
	                                           video_pll_clk };
	Root_clock pwm4_clk_root                 { clocks, "pwm4_clk_root",
	                                           root_range(106), m24_ref_clk,
	                                           system_pll2_div10, system_pll1_div5,
	                                           system_pll1_div20, system_pll3_clk,
	                                           ext_clk_2, system_pll1_div10,
	                                           video_pll_clk };
	Root_clock gpt1_clk_root                 { clocks, "gpt1_clk_root",
	                                           root_range(107), m24_ref_clk,
	                                           system_pll2_div10, system_pll1_div2,
	                                           system_pll1_div20, video_pll_clk,
	                                           system_pll1_div10, audio_pll1_clk,
	                                           ext_clk_1 };
	Root_clock gpt2_clk_root                 { clocks, "gpt2_clk_root",
	                                           root_range(108), m24_ref_clk,
	                                           system_pll2_div10, system_pll1_div2,
	                                           system_pll1_div20, video_pll_clk,
	                                           system_pll1_div10, audio_pll1_clk,
	                                           ext_clk_2 };
	Root_clock gpt3_clk_root                 { clocks, "gpt3_clk_root",
	                                           root_range(109), m24_ref_clk,
	                                           system_pll2_div10, system_pll1_div2,
	                                           system_pll1_div20, video_pll_clk,
	                                           system_pll1_div10, audio_pll1_clk,
	                                           ext_clk_3 };
	Root_clock gpt4_clk_root                 { clocks, "gpt4_clk_root",
	                                           root_range(110), m24_ref_clk,
	                                           system_pll2_div10, system_pll1_div2,
	                                           system_pll1_div20, video_pll_clk,
	                                           system_pll1_div10, audio_pll1_clk,
	                                           ext_clk_1 };
	Root_clock gpt5_clk_root                 { clocks, "gpt5_clk_root",
	                                           root_range(111), m24_ref_clk,
	                                           system_pll2_div10, system_pll1_div2,
	                                           system_pll1_div20, video_pll_clk,
	                                           system_pll1_div10, audio_pll1_clk,
	                                           ext_clk_2 };
	Root_clock gpt6_clk_root                 { clocks, "gpt6_clk_root",
	                                           root_range(112), m24_ref_clk,
	                                           system_pll2_div10, system_pll1_div2,
	                                           system_pll1_div20, video_pll_clk,
	                                           system_pll1_div10, audio_pll1_clk,
	                                           ext_clk_3 };
	Root_clock trace_clk_root                { clocks, "trace_clk_root",
	                                           root_range(113), m24_ref_clk,
	                                           system_pll1_div6, system_pll1_div5,
	                                           vpu_pll_clk, system_pll2_div8,
	                                           system_pll3_clk, ext_clk_1,
	                                           ext_clk_3, true };
	Root_clock wdog_clk_root                 { clocks, "wdog_clk_root",
	                                           root_range(114), m24_ref_clk,
	                                           system_pll1_div6, system_pll1_div5,
	                                           vpu_pll_clk, system_pll2_div8,
	                                           system_pll3_clk, system_pll1_div10,
	                                           system_pll2_div6, true };
	Root_clock wrclk_clk_root                { clocks, "wrclk_clk_root",
	                                           root_range(115), m24_ref_clk,
	                                           system_pll1_div20, vpu_pll_clk,
	                                           system_pll3_clk, system_pll2_div5,
	                                           system_pll1_div3, system_pll2_div2,
	                                           system_pll1_div8 };
	Root_clock ipp_do_clko1                  { clocks, "ipp_do_clko1",
	                                           root_range(116), m24_ref_clk,
	                                           system_pll1_clk, system_pll1_div6,
	                                           system_pll1_div4, audio_pll2_clk,
	                                           system_pll2_div2, vpu_pll_clk,
	                                           system_pll1_div10 };
	Root_clock ipp_do_clko2                  { clocks, "ipp_do_clko2",
	                                           root_range(117), m24_ref_clk,
	                                           system_pll2_div5, system_pll1_div2,
	                                           system_pll2_div6, system_pll3_clk,
	                                           audio_pll1_clk, video_pll_clk,
	                                           k32_ref_clk };
	Root_clock hdmi_fdcc_tst_clk_root        { clocks, "hdmi_fdcc_tst_clk_root",
	                                           root_range(118), m24_ref_clk,
	                                           system_pll1_div3, system_pll2_div4,
	                                           system_pll1_clk, system_pll2_clk,
	                                           system_pll3_clk, audio_pll2_clk,
	                                           video_pll_clk };
	Root_clock hdmi_ref_266m_clk_root        { clocks, "hdmi_ref_266m_clk_root",
	                                           root_range(120), m24_ref_clk,
	                                           system_pll1_div2, system_pll3_clk,
	                                           system_pll2_div3, system_pll1_div3,
	                                           system_pll2_div5, audio_pll1_clk,
	                                           video_pll_clk };
	Root_clock usdhc3_clk_root               { clocks, "usdhc3_clk_root",
	                                           root_range(121), m24_ref_clk,
	                                           system_pll1_div2, system_pll1_clk,
	                                           system_pll2_div2, system_pll3_clk,
	                                           system_pll1_div3, audio_pll2_clk,
	                                           system_pll1_div8 };
	Root_clock media_cam1_pix_clk_root       { clocks, "media_cam1_pix_clk_root",
	                                           root_range(122), m24_ref_clk,
	                                           system_pll1_div3, system_pll2_div4,
	                                           system_pll1_clk, system_pll2_clk,
	                                           system_pll3_clk, audio_pll2_clk,
	                                           video_pll_clk };
	Root_clock media_mipi_phy1_ref_clk_root  { clocks, "media_mipi_phy1_ref_clk_root",
	                                           root_range(123), m24_ref_clk,
	                                           system_pll2_div3, system_pll2_div10,
	                                           system_pll1_clk, system_pll2_clk,
	                                           ext_clk_2, audio_pll2_clk,
	                                           video_pll_clk };
	Root_clock media_disp1_pix_clk_root      { clocks, "media_disp1_pix_clk_root",
	                                           root_range(124), m24_ref_clk,
	                                           video_pll_clk, audio_pll2_clk,
	                                           audio_pll1_clk, system_pll1_clk,
	                                           system_pll2_clk, system_pll3_clk,
	                                           ext_clk_4 };
	Root_clock media_cam2_pix_clk_root       { clocks, "media_cam2_pix_clk_root",
	                                           root_range(125), m24_ref_clk,
	                                           system_pll1_div3, system_pll2_div4,
	                                           system_pll1_clk, system_pll2_clk,
	                                           system_pll3_clk, audio_pll2_clk,
	                                           video_pll_clk };
	Root_clock media_ldb_clk_root            { clocks, "media_ldb_clk_root",
	                                           root_range(126), m24_ref_clk,
	                                           system_pll2_div3, system_pll2_div10,
	                                           system_pll1_clk, system_pll2_clk,
	                                           ext_clk_2, audio_pll2_clk,
	                                           video_pll_clk };
	Root_clock media_mipi_test_byte_clk      { clocks, "media_mipi_test_byte_clk",
	                                           root_range(130), m24_ref_clk,
	                                           system_pll2_div5, system_pll2_div20,
	                                           system_pll3_clk, system_pll2_div10,
	                                           system_pll1_div10, system_pll1_div5,
	                                           system_pll1_div4 };
	Root_clock ecspi3_clk_root               { clocks, "ecspi3_clk_root",
	                                           root_range(131), m24_ref_clk,
	                                           system_pll2_div5, system_pll1_div20,
	                                           system_pll1_div5, system_pll1_clk,
	                                           system_pll3_clk, system_pll2_div4,
	                                           audio_pll2_clk };
	Root_clock pdm_clk_root                  { clocks, "pdm_clk_root",
	                                           root_range(132), m24_ref_clk,
	                                           system_pll2_div10, audio_pll1_clk,
	                                           system_pll1_clk, system_pll2_clk,
	                                           system_pll3_clk, ext_clk_3,
	                                           audio_pll2_clk };
	Root_clock vpu_vc8000e_clk_root          { clocks, "vpu_vc8000e_clk_root",
	                                           root_range(133), m24_ref_clk,
	                                           vpu_pll_clk, system_pll1_clk,
	                                           system_pll2_clk, audio_pll2_clk,
	                                           system_pll2_div8, system_pll3_clk,
	                                           audio_pll1_clk };
	Root_clock sai7_clk_root                 { clocks, "sai7_clk_root",
	                                           root_range(134), m24_ref_clk,
	                                           audio_pll1_clk, audio_pll2_clk,
	                                           video_pll_clk, system_pll1_div6,
	                                           no_clk, ext_clk_3, ext_clk_4 };
	Root_clock usb_core_clk_root             { clocks, "usb_core_clk_root",
	                                           ccm_regs.range_at(0xb100), m24_ref_clk,
	                                           system_pll1_div8, system_pll1_div20,
	                                           system_pll2_div10, system_pll2_div5,
	                                           ext_clk_2, ext_clk_3, audio_pll2_clk };
	Root_clock usb_phy_clk_root              { clocks, "usb_phy_clk_root",
	                                           ccm_regs.range_at(0xb180), m24_ref_clk,
	                                           system_pll1_div8, system_pll1_div20,
	                                           system_pll2_div10, system_pll2_div5,
	                                           ext_clk_2, ext_clk_3, audio_pll2_clk };

	Root_clock_divider ipg_clk_root          { clocks, "ipg_clk_root",
	                                           root_range(33), ahb_clk_root };

	Gate debug_gate       { clocks, "debug_gate",
	                        gate_range(4),   ahb_clk_root, true };
	Gate dram1_gate       { clocks, "dram1_gate",
	                        gate_range(5),   dram_alt_clk_root, true };
	Gate ecspi1_gate      { clocks, "ecspi1_gate",
	                        gate_range(7),   ecspi1_clk_root };
	Gate ecspi2_gate      { clocks, "ecspi2_gate",
	                        gate_range(8),   ecspi2_clk_root };
	Gate ecspi3_gate      { clocks, "ecspi3_gate",
	                        gate_range(9),   ecspi3_clk_root };
	Gate enet1_gate       { clocks, "enet1_gate",
	                        gate_range(10),  enet_ref_clk_root };
	Gate gpio1_gate       { clocks, "gpio1_gate",
	                        gate_range(11),  ipg_clk_root };
	Gate gpio2_gate       { clocks, "gpio2_gate",
	                        gate_range(12),  ipg_clk_root };
	Gate gpio3_gate       { clocks, "gpio3_gate",
	                        gate_range(13),  ipg_clk_root };
	Gate gpio4_gate       { clocks, "gpio4_gate",
	                        gate_range(14),  ipg_clk_root };
	Gate gpio5_gate       { clocks, "gpio5_gate",
	                        gate_range(15),  ipg_clk_root };
	Gate gpt1_gate        { clocks, "gpt1_gate",
	                        gate_range(16),  gpt1_clk_root };
	Gate gpt2_gate        { clocks, "gpt2_gate",
	                        gate_range(17),  gpt2_clk_root };
	Gate gpt3_gate        { clocks, "gpt3_gate",
	                        gate_range(18),  gpt3_clk_root };
	Gate gpt4_gate        { clocks, "gpt4_gate",
	                        gate_range(19),  gpt4_clk_root };
	Gate gpt5_gate        { clocks, "gpt5_gate",
	                        gate_range(20),  gpt5_clk_root };
	Gate gpt6_gate        { clocks, "gpt6_gate",
	                        gate_range(21),  gpt6_clk_root };
	Gate i2c1_gate        { clocks, "i2c1_gate",
	                        gate_range(23),  i2c1_clk_root };
	Gate i2c2_gate        { clocks, "i2c2_gate",
	                        gate_range(24),  i2c2_clk_root };
	Gate i2c3_gate        { clocks, "i2c3_gate",
	                        gate_range(25),  i2c3_clk_root };
	Gate i2c4_gate        { clocks, "i2c4_gate",
	                        gate_range(26),  i2c4_clk_root };
	Gate iomux_gate       { clocks, "iomux_gate",
	                        gate_range(27),  ipg_clk_root, true };
	Gate ipmux1_gate      { clocks, "ipmux1_gate",
	                        gate_range(28),  ahb_clk_root, true };
	Gate ipmux2_gate      { clocks, "ipmux2_gate",
	                        gate_range(29),  ahb_clk_root, true };
	Gate ipmux3_gate      { clocks, "ipmux3_gate",
	                        gate_range(30),  ahb_clk_root, true };
	Gate mu_gate          { clocks, "mu_gate",
	                        gate_range(33),  ipg_clk_root };
	Gate ocotp_gate       { clocks, "ocotp_gate",
	                        gate_range(34),  ipg_clk_root };
	Gate ocram_gate       { clocks, "ocram_gate",
	                        gate_range(35),  main_axi_clk_root, true };
	Gate ocram_s_gate     { clocks, "ocram_s_gate",
	                        gate_range(36),  ahb_clk_root, true };
	Gate pcie_gate        { clocks, "pcie_gate",
	                        gate_range(37),  pcie_aux_clk_root };
	Gate pwm1_gate        { clocks, "pwm1_gate",
	                        gate_range(40),  pwm1_clk_root };
	Gate pwm2_gate        { clocks, "pwm2_gate",
	                        gate_range(41),  pwm2_clk_root };
	Gate pwm3_gate        { clocks, "pwm3_gate",
	                        gate_range(42),  pwm3_clk_root };
	Gate pwm4_gate        { clocks, "pwm4_gate",
	                        gate_range(43),  pwm4_clk_root };
	Gate qos_enet_gate    { clocks, "qos_enet_gate",
	                        gate_range(46),  enet_qos_clk_root };
	Gate flexspi_gate     { clocks, "flexspi_gate",
	                        gate_range(47),  ahb_clk_root };
	Gate rawnand_gate     { clocks, "rawnand_gate",
	                        gate_range(48),  nand_clk_root };
	Gate rdc_gate         { clocks, "rdc_gate",
	                        gate_range(49),  ipg_clk_root, true };
	Gate i2c5_gate        { clocks, "i2c5_gate",
	                        gate_range(51),  i2c5_clk_root };
	Gate i2c6_gate        { clocks, "i2c6_gate",
	                        gate_range(52),  i2c6_clk_root };
	Gate can1_gate        { clocks, "can1_gate",
	                        gate_range(53),  can1_clk_root };
	Gate can2_gate        { clocks, "can2_gate",
	                        gate_range(54),  can2_clk_root };
	Gate sctr_gate        { clocks, "sctr_gate",
	                        gate_range(57),  ipg_clk_root, true };
	Gate sdma1_gate       { clocks, "sdma1_gate",
	                        gate_range(58),  ipg_clk_root };
	Gate enet_qos_gate    { clocks, "enet_qos_gate",
	                        gate_range(59),  enet_axi_clk_root };
	Gate sema1_gate       { clocks, "sema1_gate",
	                        gate_range(61),  ipg_clk_root };
	Gate sema2_gate       { clocks, "sema2_gate",
	                        gate_range(62),  ipg_clk_root };
	Gate irq_steer_gate   { clocks, "irq_steer_gate",
	                        gate_range(63),  ipg_clk_root };
	Gate sim_enet_gate    { clocks, "sim_enet_gate",
	                        gate_range(64),  enet_ref_clk_root };
	Gate gpu2d_gate       { clocks, "gpu2d_gate",
	                        gate_range(69),  gpu2d_clk_root };
	Gate gpu3d_gate       { clocks, "gpu3d_gate",
	                        gate_range(70),  gpu_axi_clk_root };
	Gate snvs_gate        { clocks, "snvs_gate",
	                        gate_range(71),  ipg_clk_root };
	Gate trace_gate       { clocks, "trace_gate",
	                        gate_range(72),  trace_clk_root, true };
	Gate uart1_gate       { clocks, "uart1_gate",
	                        gate_range(73),  uart1_clk_root };
	Gate uart2_gate       { clocks, "uart2_gate",
	                        gate_range(74),  uart2_clk_root, true };
	Gate uart3_gate       { clocks, "uart3_gate",
	                        gate_range(75),  uart3_clk_root };
	Gate uart4_gate       { clocks, "uart4_gate",
	                        gate_range(76),  uart4_clk_root };
	Gate usb_gate         { clocks, "usb_gate",
	                        gate_range(77),  hsio_axi_clk_root };
	Gate usb_phy_gate     { clocks, "usb_phy_gate",
	                        gate_range(79),  usb_phy_clk_root };
	Gate usdhc1_gate      { clocks, "usdhc1_gate",
	                        gate_range(81),  usdhc1_clk_root };
	Gate usdhc2_gate      { clocks, "usdhc2_gate",
	                        gate_range(82),  usdhc2_clk_root };
	Gate wdog1_gate       { clocks, "wdog1_gate",
	                        gate_range(83),  wdog_clk_root, true };
	Gate wdog2_gate       { clocks, "wdog2_gate",
	                        gate_range(84),  wdog_clk_root, true };
	Gate wdog3_gate       { clocks, "wdog3_gate",
	                        gate_range(85),  wdog_clk_root };
	Gate vpu_g1_gate      { clocks, "vpu_g1_gate",
	                        gate_range(86),  vpu_g1_clk_root };
	Gate gpu_gate         { clocks, "gpu_gate",
	                        gate_range(87),  gpu_ahb_clk_root };
	Gate vpu_vc8ke_gate   { clocks, "vpu_vc8ke_gate",
	                        gate_range(89),  vpu_vc8000e_clk_root};
	Gate vpu_g2_gate      { clocks, "vpu_g2_gate",
	                        gate_range(90),  vpu_g2_clk_root };
	Gate npu_gate         { clocks, "npu_gate",
	                        gate_range(91),  ml_ahb_clk_root };
	Gate hsio_gate        { clocks, "hsio_gate",
	                        gate_range(92),  hsio_axi_clk_root };
	Gate media_gate       { clocks, "media_gate",
	                        gate_range(93),  media_mipi_phy1_ref_clk_root};
	Gate usdhc3_gate      { clocks, "usdhc3_gate",
	                        gate_range(94),  usdhc3_clk_root };
	Gate hdmi_gate        { clocks, "hdmi_gate",
	                        gate_range(95),  hdmi_apb_clk_root };
	Gate vpu_gate         { clocks, "vpu_gate",
	                        gate_range(99),  vpu_bus_clk_root};
	Gate mrpr_gate        { clocks, "mrpr_gate",
	                        gate_range(100), ipg_clk_root, true };
	Gate audio_gate       { clocks, "audio_gate",
	                        gate_range(101), audio_ahb_clk_root };
};
