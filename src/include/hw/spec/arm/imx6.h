/*
 * \brief  MMIO and IRQ definitions common to i.MX6 SoC
 * \author Nikolay Golikov <nik@ksyslabs.org>
 * \author Josef Soentgen
 * \author Martin Stein
 * \date   2017-06-20
 */

/*
 * Copyright (C) 2017 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _INCLUDE__DRIVERS__DEFS__IMX6_H_
#define _INCLUDE__DRIVERS__DEFS__IMX6_H_

namespace Imx6 {
	enum {
		UART_1_IRQ       = 58,
		UART_1_MMIO_BASE = 0x02020000,
		UART_1_MMIO_SIZE = 0x00004000,

		UART_2_IRQ       = 59,
		UART_2_MMIO_BASE = 0x021e8000,
		UART_2_MMIO_SIZE = 0x00004000,

		/* timer */
		EPIT_2_IRQ       = 89,
		EPIT_2_MMIO_BASE = 0x020d4000,
		EPIT_2_MMIO_SIZE = 0x00004000,

		/* ARM IP Bus control */
		AIPS_1_MMIO_BASE = 0x0207c000,
		AIPS_1_MMIO_SIZE = 0x00004000,
		AIPS_2_MMIO_BASE = 0x0217c000,
		AIPS_2_MMIO_SIZE = 0x00004000,

		/* CPU */
		CORTEX_A9_PRIVATE_MEM_BASE  = 0x00a00000,
		CORTEX_A9_PRIVATE_MEM_SIZE  = 0x00002000,

		/* L2 cache controller */
		PL310_MMIO_BASE = 0x00a02000,
		PL310_MMIO_SIZE = 0x00001000,

		/* System reset controller */
		SRC_MMIO_BASE = 0x20d8000,
	};
};

#endif /* _INCLUDE__DRIVERS__DEFS__IMX6_H_ */
