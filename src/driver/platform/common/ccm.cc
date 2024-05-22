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

#include <common/ccm.h>

/********************************
 ** Root_clock immplementation **
 ********************************/

void Ccm::Root_clock::rate(Rate rate)
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


void Ccm::Root_clock::parent(Name name)
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


Driver::Clock::Rate Ccm::Root_clock::rate() const
{
	unsigned long parent_rate =
		_ref_clks[read<Target_reg::Ref_sel>()].ref.rate().value;
	unsigned pre  = read<Target_reg::Pre_div>()+1;
	unsigned post = read<Target_reg::Post_div>()+1;
	return {parent_rate / pre / post};
}


void Ccm::Root_clock::_enable()
{
	/* enable the parent clock */
	_ref_clks[read<Target_reg::Ref_sel>()].ref.enable();
	write<Target_reg::Enable>(1);
}


void Ccm::Root_clock::_disable()
{
	if (_never_disable)
		return;

	write<Target_reg::Enable>(0);

	/* disable the parent clock */
	_ref_clks[read<Target_reg::Ref_sel>()].ref.disable();
}


/***************************************
 ** Root_clock_divider implementation **
 ***************************************/

void Ccm::Root_clock_divider::rate(Rate rate)
{
	uint32_t div = (uint32_t) ((_parent.rate().value / rate.value) - 1);
	if (div > 64) {
		Genode::error("Cannot set divider ", name, " to ", div);
		return;
	}
	write<Target_reg::Post_div>(div);
}


Driver::Clock::Rate Ccm::Root_clock_divider::rate() const
{
	return {_parent.rate().value / (read<Target_reg::Post_div>()+1)};
};


/**************************
 ** Gate immplementation **
 **************************/

void Ccm::Gate::_enable()
{
	/* enable the parent clock implictly */
	_parent.enable();
	write<Ccgr>(0x3);
}


void Ccm::Gate::_disable()
{
	if (_never_disable)
		return;

	/* disable the parent clock implictly */
	_parent.disable();

	write<Ccgr>(0x0);
}
