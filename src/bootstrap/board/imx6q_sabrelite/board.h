/*
 * \brief   i.MX6Quad Sabrelite specific board definitions
 * \author  Stefan Kalkowski
 * \date    2019-01-05
 */

/*
 * Copyright (C) 2019 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _SRC__BOOTSTRAP__SPEC__IMX6Q_SABRELITE__BOARD_H_
#define _SRC__BOOTSTRAP__SPEC__IMX6Q_SABRELITE__BOARD_H_

#include <hw/spec/arm/imx6q_sabrelite_board.h>
#include <spec/arm/cortex_a9_actlr.h>
#include <spec/arm/cortex_a9_page_table.h>
#include <spec/arm/cpu.h>
#include <hw/spec/arm/gicv2.h>

namespace Board {

	using namespace Hw::Imx6q_sabrelite_board;
	using Hw::Global_interrupt_controller;
	using Hw::Local_interrupt_controller;
	struct L2_cache;

	static constexpr bool NON_SECURE = false;

	static volatile unsigned long initial_values[][2] {
		// (IOMUX Controller)
		{ 0x20e0004, 0x48603005 },
		{ 0x20e0218, 0x2 },
		{ 0x20e0220, 0x0 },
		{ 0x20e0224, 0x3 },
		{ 0x20e02b8, 0x0 },
		{ 0x20e02f4, 0x0 },
		{ 0x20e036c, 0x10030 },
		{ 0x20e0370, 0x10030 },
		{ 0x20e0374, 0x10030 },
		{ 0x20e0378, 0x10030 },
		{ 0x20e037c, 0x10030 },
		{ 0x20e0388, 0x10030 },
		{ 0x20e03b0, 0xb1 },
		{ 0x20e03bc, 0xb0 },
		{ 0x20e03c0, 0xb0 },
		{ 0x20e04e4, 0x100b0 },
		{ 0x20e04e8, 0x100b0 },
		{ 0x20e0508, 0x100b0 },
		{ 0x20e05f0, 0x30b0 },
		{ 0x20e05f4, 0x17059 },
		{ 0x20e061c, 0x30b0 },
		{ 0x20e069c, 0x1f0b0 },
		{ 0x20e06a4, 0x10059 },
		{ 0x20e06e0, 0x10059 },
		{ 0x20e0944, 0x1 },
		// (Power Management Unit)
		{ 0x20c8120, 0x10f75 },
		// (Clock Controller Module)
		{ 0x20c4004, 0x10000 },
		{ 0x20c4018, 0x10204 },
		{ 0x20c402c, 0x7348c1 },
		{ 0x20c4030, 0x33e71f92 },
		{ 0x20c4034, 0x12090 },
		{ 0x20c4038, 0x12090 },
		{ 0x20c4054, 0x78 },
		{ 0x20c4060, 0xe0101 },
		{ 0x20c8010, 0x80003040 },
		{ 0x20c8020, 0x80003040 },
		{ 0x20c8070, 0x1006 },
		{ 0x20c80a0, 0x100c },
		{ 0x20c80e0, 0x101001 },
		{ 0x20c80f0, 0xd3d1d0cc },
		{ 0x20c8100, 0x501890db },
	};
}


struct Board::L2_cache : Hw::Pl310
{
	L2_cache(Genode::addr_t mmio) : Hw::Pl310(mmio)
	{
		Aux::access_t aux = 0;
		Aux::Full_line_of_zero::set(aux, true);
		Aux::Associativity::set(aux, Aux::Associativity::WAY_16);
		Aux::Way_size::set(aux, Aux::Way_size::KB_64);
		Aux::Share_override::set(aux, true);
		Aux::Replacement_policy::set(aux, Aux::Replacement_policy::PRAND);
		Aux::Ns_lockdown::set(aux, true);
		Aux::Data_prefetch::set(aux, true);
		Aux::Inst_prefetch::set(aux, true);
		Aux::Early_bresp::set(aux, true);
		write<Aux>(aux);

		Tag_ram::access_t tag_ram = 0;
		Tag_ram::Setup_latency::set(tag_ram, 2);
		Tag_ram::Read_latency::set(tag_ram, 3);
		Tag_ram::Write_latency::set(tag_ram, 1);
		write<Tag_ram>(tag_ram);

		Data_ram::access_t data_ram = 0;
		Data_ram::Setup_latency::set(data_ram, 2);
		Data_ram::Read_latency::set(data_ram, 3);
		Data_ram::Write_latency::set(data_ram, 1);
		write<Data_ram>(data_ram);

		Prefetch_ctrl::access_t prefetch = 0;
		Prefetch_ctrl::Data_prefetch::set(prefetch, 1);
		Prefetch_ctrl::Inst_prefetch::set(prefetch, 1);
		write<Prefetch_ctrl>(prefetch | 0xF);
	}

	using Hw::Pl310::invalidate;

	void enable()
	{
		Pl310::mask_interrupts();
		write<Control::Enable>(1);
	}

	void disable() {
		write<Control::Enable>(0);
	}
};

#endif /* _SRC__BOOTSTRAP__SPEC__IMX6Q_SABRELITE__BOARD_H_ */
