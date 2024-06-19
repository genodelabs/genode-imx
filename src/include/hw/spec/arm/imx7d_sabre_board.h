/*
 * \brief   Imx7 Sabrelite specific board definitions
 * \author  Stefan Kalkowski
 * \date    2018-11-07
 */

/*
 * Copyright (C) 2018 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _SRC__INCLUDE__HW__SPEC__ARM__IMX7_SABRELITE_BOARD_H_
#define _SRC__INCLUDE__HW__SPEC__ARM__IMX7_SABRELITE_BOARD_H_

#include <drivers/uart/imx.h>
#include <hw/spec/arm/boot_info.h>
#include <hw/spec/arm/cortex_a15.h>

namespace Hw::Imx7d_sabre_board {

	enum {
		RAM_0_BASE          = 0x80000000UL,
		RAM_0_SIZE          = 0x40000000UL,

		IRQ_CONTROLLER_BASE = 0x31000000UL,
		IRQ_CONTROLLER_SIZE = 0x8000,

		SRC_MMIO_BASE       = 0x30390000UL,

		AIPS_1_MMIO_BASE    = 0x301f0000UL,
		AIPS_2_MMIO_BASE    = 0x305f0000UL,
		AIPS_3_MMIO_BASE    = 0x309f0000UL,

		UART_1_MMIO_BASE    = 0x30860000UL,
		UART_1_MMIO_SIZE    = 0x10000UL,

		TIMER_CLOCK         = 1000000000UL,


		/******************************
		 ** Virtualization extension **
		 ******************************/

		VT_MAINTAINANCE_IRQ = 25,
		VT_TIMER_IRQ        = 27,
	};

	using Cpu_mmio = Hw::Cortex_a15_mmio<IRQ_CONTROLLER_BASE>;
	using Serial = Genode::Imx_uart;

	enum {
		UART_BASE  = UART_1_MMIO_BASE,
		UART_CLOCK = 0, /* unsued value */
	};

	static constexpr Genode::size_t NR_OF_CPUS = 2;
}

#endif /* _SRC__INCLUDE__HW__SPEC__ARM__IMX7_SABRELITE_BOARD_H_ */
