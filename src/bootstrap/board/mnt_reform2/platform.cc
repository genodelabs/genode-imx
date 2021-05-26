/*
 * \brief   Platform implementations specific for base-hw and i.MX8Q EVK
 * \author  Stefan Kalkowski
 * \date    2019-06-12
 */

/*
 * Copyright (C) 2019 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#include <platform.h>


/**
 * Leave out the first page (being 0x0) from bootstraps RAM allocator,
 * some code does not feel happy with addresses being zero
 */
Bootstrap::Platform::Board::Board()
:
	early_ram_regions(Memory_region { ::Board::RAM_BASE, ::Board::RAM_SIZE }),
	late_ram_regions(Memory_region { }),
	core_mmio(Memory_region { ::Board::UART_BASE, ::Board::UART_SIZE },
	          Memory_region { ::Board::Cpu_mmio::IRQ_CONTROLLER_DISTR_BASE,
	                          ::Board::Cpu_mmio::IRQ_CONTROLLER_DISTR_SIZE },
	          Memory_region { ::Board::Cpu_mmio::IRQ_CONTROLLER_REDIST_BASE,
	                          ::Board::Cpu_mmio::IRQ_CONTROLLER_REDIST_SIZE })
{
	::Board::Pic pic {};


	/*******************************
	 ** Set default IOMUXC values **
	 *******************************/

	static Genode::addr_t iomuxc_values[][2] = {
		{ 0x3033005c, 0x0 },
		{ 0x303301b0, 0x0 },
		{ 0x303301b4, 0x0 },
		{ 0x303301b8, 0x0 },
		{ 0x303301bc, 0x0 },
		{ 0x303301c0, 0x0 },
		{ 0x303301c4, 0x0 },
		{ 0x303301c8, 0x0 },
		{ 0x303301e4, 0x1 },
		{ 0x303301e8, 0x1 },
		{ 0x303301ec, 0x1 },
		{ 0x303301fc, 0x1 },
		{ 0x30330200, 0x1 },
		{ 0x30330224, 0x10 },
		{ 0x30330228, 0x10 },
		{ 0x3033022c, 0x10 },
		{ 0x30330230, 0x10 },
		{ 0x3033023c, 0x0 },
		{ 0x30330240, 0x0 },
		{ 0x30330244, 0x0 },
		{ 0x30330248, 0x0 },
		{ 0x303302b4, 0x19 },
		{ 0x303302bc, 0x59 },
		{ 0x303302c8, 0x56 },
		{ 0x30330308, 0x9f },
		{ 0x3033030c, 0xdf },
		{ 0x30330310, 0xdf },
		{ 0x30330314, 0xdf },
		{ 0x30330318, 0xdf },
		{ 0x3033031c, 0xdf },
		{ 0x30330320, 0xdf },
		{ 0x30330324, 0xdf },
		{ 0x30330328, 0xdf },
		{ 0x3033032c, 0xdf },
		{ 0x303303ac, 0x19 },
		{ 0x303303b8, 0x16 },
		{ 0x30330418, 0xd6 },
		{ 0x3033041c, 0xd6 },
		{ 0x30330420, 0xd6 },
		{ 0x30330424, 0xd6 },
		{ 0x30330428, 0xd6 },
		{ 0x3033042c, 0xd6 },
		{ 0x30330430, 0xd6 },
		{ 0x30330464, 0x45 },
		{ 0x30330468, 0x45 },
		{ 0x3033047c, 0x7f },
		{ 0x30330480, 0x7f },
		{ 0x3033048c, 0x7f },
		{ 0x30330490, 0x7f },
		{ 0x30330494, 0x7f },
		{ 0x30330498, 0x7f },
		{ 0x3033049c, 0x45 },
		{ 0x303304a0, 0x45 },
		{ 0x303304a4, 0x45 },
		{ 0x303304a8, 0x45 },
		{ 0x303304ac, 0x45 },
		{ 0x303304b0, 0x45 },
		{ 0x30330500, 0x1 },
		{ 0x30330504, 0x2 },
		{ 0x30340034, 0x4 },
		{ 0x30340040, 0x49409200 },
		{ 0x30340060, 0x180000 },
		{ 0x30340064, 0x6400a20 },
		{ 0x30340068, 0xa }
	};

	unsigned num_values = sizeof(iomuxc_values) / (2*sizeof(Genode::addr_t));
	for (unsigned i = 0; i < num_values; i++) {
		*((volatile Genode::uint32_t*)iomuxc_values[i][0]) =
			(Genode::uint32_t)iomuxc_values[i][1];
	}


	/*************************
	 ** Raise CPU frequency **
	 *************************/

	enum Mmio_base_addresses {
		CCM_ANALOG_MMIO_BASE = 0x30360000,
		CCM_MMIO_BASE        = 0x30380000,
	};

	struct Ccm : Genode::Mmio
	{
		Ccm() : Genode::Mmio(CCM_MMIO_BASE) { }

		struct Target_root_0 : Register<0x8000, 32>
		{
			struct Mux : Bitfield<24, 3>
			{
				enum { ARM_PLL = 1, SYS_PLL1 = 4 };
			};

			struct Enable : Bitfield<28, 1> {};
		};
	} ccm;

	struct Ccm_analog : Genode::Mmio
	{
		Ccm_analog() : Genode::Mmio(CCM_ANALOG_MMIO_BASE) { }

		struct Pll_arm_0 : Register<0x28, 32>
		{
			struct Output_div_value : Bitfield<0, 5> {};
			struct Newdiv_ack       : Bitfield<11,1> {};
			struct Newdiv_val       : Bitfield<12,1> {};
		};
		struct Pll_arm_1 : Register<0x2c, 32>
		{
			struct Int_div_ctl      : Bitfield<0,  7> {};
			struct Frac_div_ctl     : Bitfield<7, 24> {};
		};
	} pll;

	/* set Cortex A53 reference clock to System PLL1 800 MHz */
	ccm.write<Ccm::Target_root_0::Mux>(Ccm::Target_root_0::Mux::SYS_PLL1);

	/* set new divider value for Pll_arm */
	pll.write<Ccm_analog::Pll_arm_1>(Ccm_analog::Pll_arm_1::Int_div_ctl::bits(0x4a));
	pll.write<Ccm_analog::Pll_arm_0::Output_div_value>(0);
	pll.write<Ccm_analog::Pll_arm_0::Newdiv_val>(1);
	while (!pll.read<Ccm_analog::Pll_arm_0::Newdiv_ack>()) { ; }
	pll.write<Ccm_analog::Pll_arm_0::Newdiv_val>(0);

	/* set Cortex A53 reference clock to ARM_PLL 1500 MHz */
	ccm.write<Ccm::Target_root_0::Mux>(Ccm::Target_root_0::Mux::ARM_PLL);
}


void Board::Cpu::wake_up_all_cpus(void * ip)
{
	enum Function_id { CPU_ON = 0xC4000003 };

	unsigned long result = 0;
	for (unsigned i = 1; i < NR_OF_CPUS; i++) {
		asm volatile("mov x0, %1  \n"
		             "mov x1, %2  \n"
		             "mov x2, %3  \n"
		             "mov x3, %2  \n"
		             "smc #0      \n"
		             "mov %0, x0  \n"
		             : "=r" (result) : "r" (CPU_ON), "r" (i), "r" (ip)
		                      : "x0", "x1", "x2", "x3", "x4", "x5", "x6", "x7",
		                        "x8", "x9", "x10", "x11", "x12", "x13", "x14");
	}
}
