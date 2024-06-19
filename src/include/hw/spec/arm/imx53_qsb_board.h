/*
 * \brief   i.MX53 Quickstart board definitions
 * \author  Stefan Kalkowski
 * \date    2019-05-15
 */

/*
 * Copyright (C) 2019 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _SRC__INCLUDE__HW__SPEC__IMX53_QSB_BOARD_H_
#define _SRC__INCLUDE__HW__SPEC__IMX53_QSB_BOARD_H_

#include <hw/spec/arm/boot_info.h>
#include <hw/spec/arm/imx53.h>
#include <hw/spec/arm/imx_uart.h>

namespace Hw::Imx53_qsb_board {

	using namespace Imx53;

	enum {
		RAM0_BASE = RAM_BANK_0_BASE,
		RAM0_SIZE = 0x20000000,
		RAM1_BASE = RAM_BANK_1_BASE,
		RAM1_SIZE = 0x20000000,
	};

	using Serial = Hw::Imx_uart;

	enum {
		UART_BASE  = UART_1_MMIO_BASE,
		UART_CLOCK = 0, /* ignored value */
	};

	static constexpr Genode::size_t NR_OF_CPUS = 1;
}

#endif /* _SRC__INCLUDE__HW__SPEC__IMX53_QSB_BOARD_H_ */
