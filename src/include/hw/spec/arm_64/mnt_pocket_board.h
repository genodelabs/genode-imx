/*
 * \brief  Board definitions for MNT Pocket
 * \author Stefan Kalkowski
 * \date   2024-08-21
 */

/*
 * Copyright (C) 2024 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _SRC__INCLUDE__HW__SPEC__ARM_64__MNT_POCKET__BOARD_H_
#define _SRC__INCLUDE__HW__SPEC__ARM_64__MNT_POCKET__BOARD_H_

#include <hw/spec/arm/boot_info.h>
#include <hw/spec/arm/imx_uart.h>

namespace Hw::Mnt_pocket_board {
	using Serial = Hw::Imx_uart;

	enum {
		RAM_0_BASE   =  0x40000000,
		RAM_0_SIZE   =  0x16000000,
		RAM_1_BASE   =  0x58000000,
		RAM_1_SIZE   = 0x1e8000000,

		UART_BASE  = 0x30890000, /* UART2 */
		UART_SIZE  = 0x1000,
		UART_CLOCK = 250000000,
	};

	static constexpr Genode::size_t NR_OF_CPUS = 4;

	namespace Cpu_mmio {
		enum {
			IRQ_CONTROLLER_DISTR_BASE  = 0x38800000,
			IRQ_CONTROLLER_DISTR_SIZE  = 0x10000,
			IRQ_CONTROLLER_VT_CPU_BASE = 0x31020000,
			IRQ_CONTROLLER_VT_CPU_SIZE = 0x2000,
			IRQ_CONTROLLER_REDIST_BASE = 0x38880000,
			IRQ_CONTROLLER_REDIST_SIZE = 0xc0000,
		};
	};
};

#endif /* _SRC__INCLUDE__HW__SPEC__ARM_64__MNT_POCKET__BOARD_H_ */
