/*
 * \brief  Central clock module for i.MX
 * \author Stefan Kalkowski
 * \date   2020-06-12
 */

/*
 * Copyright (C) 2020 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#pragma once

#include <os/attached_mmio.h>
#include <clock.h>

namespace Ccm {
	using namespace Genode;

	class Root_clock;
	class Root_clock_divider;
	class Gate;
};


class Ccm::Root_clock : public Driver::Clock, Mmio<0x4>
{
	private:

		struct Target_reg : Register<0x0, 32>
		{
			struct Post_div : Bitfield<0,6>  {};
			struct Pre_div  : Bitfield<16,3> {};
			struct Ref_sel  : Bitfield<24,3> {};
			struct Enable   : Bitfield<28,1> {};
		};

		struct Clock_ref {
			Driver::Clock &ref;
			Clock_ref(Driver::Clock & c) : ref(c) {}
		};

		enum { REF_CLK_MAX = 8 };

		Driver::Clocks &_clocks;
		Clock_ref       _ref_clks[REF_CLK_MAX];
		bool const      _never_disable;

		Driver::Clock &_parent() const;

	public:

		Root_clock(Driver::Clocks       &clocks,
		           Name                  name,
		           Byte_range_ptr const &range,
		           Driver::Clock        &ref_clk0,
		           Driver::Clock        &ref_clk1,
		           Driver::Clock        &ref_clk2,
		           Driver::Clock        &ref_clk3,
		           Driver::Clock        &ref_clk4,
		           Driver::Clock        &ref_clk5,
		           Driver::Clock        &ref_clk6,
		           Driver::Clock        &ref_clk7,
		           bool const            never_disable = false)
		:
			Driver::Clock(clocks, name),
			Mmio(range),
			_clocks(clocks),
			_ref_clks { ref_clk0, ref_clk1, ref_clk2, ref_clk3,
			            ref_clk4, ref_clk5, ref_clk6, ref_clk7 },
			_never_disable(never_disable)
		{
			if (_never_disable) enable();
			else                _disable();
		}

		void parent(Name name) override;
		void rate(Rate rate)   override;
		Rate rate()      const override;
		void _enable()         override;
		void _disable()        override;
};


class Ccm::Root_clock_divider : public Driver::Clock, Mmio<0x4>
{
	private:

		struct Target_reg : Register<0x0, 32>
		{
			struct Post_div : Bitfield<0,6>  {};
		};

		Driver::Clock &_parent;

	public:

		Root_clock_divider(Driver::Clocks       &clocks,
		                   Name                  name,
		                   Byte_range_ptr const &range,
		                   Driver::Clock        &parent)
		:
			Driver::Clock(clocks, name),
			Mmio(range),
			_parent(parent) {}

		void rate(Rate rate) override;
		Rate rate()    const override;
};


class Ccm::Gate : public Driver::Clock, Mmio<0x4>
{
	private:

		struct Ccgr : Register<0x0, 32> { };

		Driver::Clock &_parent;
		bool const     _never_disable;

	public:

		Gate(Driver::Clocks       &clocks,
		     Name                  name,
		     Byte_range_ptr const &range,
		     Driver::Clock        &parent,
		     bool const            never_disable = false)
		:
			Driver::Clock(clocks, name),
			Mmio(range),
			_parent(parent),
			_never_disable(never_disable)
		{
			if (_never_disable) enable();
			else                _disable();
		}

		Rate rate() const override {
			return _parent.rate(); }

		void rate(Rate rate) override {
			_parent.rate(rate); }

		void _enable()  override;
		void _disable() override;
};
