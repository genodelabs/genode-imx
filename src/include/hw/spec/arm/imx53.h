/*
 * \brief  MMIO and IRQ definitions common to i.MX53 SoC
 * \author Stefan Kalkowski
 * \date   2012-10-24
 */

/*
 * Copyright (C) 2012-2017 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _INCLUDE__DRIVERS__DEFS__IMX53_H_
#define _INCLUDE__DRIVERS__DEFS__IMX53_H_

namespace Imx53 {
	enum {
		MMIO_BASE          = 0x0,
		MMIO_SIZE          = 0x70000000,

		RAM_BANK_0_BASE    = 0x70000000,
		RAM_BANK_0_SIZE    = 0x40000000,
		RAM_BANK_1_BASE    = 0xb0000000,
		RAM_BANK_1_SIZE    = 0x40000000,

		SDHC_IRQ           = 1,
		GPIO1_IRQL         = 50,
		GPIO1_IRQH         = 51,
		GPIO2_IRQL         = 52,
		GPIO2_IRQH         = 53,
		GPIO3_IRQL         = 54,
		GPIO3_IRQH         = 55,
		GPIO4_IRQL         = 56,
		GPIO4_IRQH         = 57,
		GPIO5_IRQL         = 103,
		GPIO5_IRQH         = 104,
		GPIO6_IRQL         = 105,
		GPIO6_IRQH         = 106,
		GPIO7_IRQL         = 107,
		GPIO7_IRQH         = 108,
		I2C_2_IRQ          = 63,
		I2C_3_IRQ          = 64,


		UART_1_IRQ         = 31,
		UART_1_MMIO_BASE   = 0x53fbc000,
		UART_1_MMIO_SIZE   = 0x00004000,

		EPIT_1_IRQ         = 40,
		EPIT_1_MMIO_BASE   = 0x53fac000,
		EPIT_1_MMIO_SIZE   = 0x00004000,

		EPIT_2_IRQ         = 41,
		EPIT_2_MMIO_BASE   = 0x53fb0000,
		EPIT_2_MMIO_SIZE   = 0x00004000,

		IRQ_CONTROLLER_BASE = 0x0fffc000,
		IRQ_CONTROLLER_SIZE = 0x00004000,

		AIPS_1_MMIO_BASE   = 0x53f00000,
		AIPS_2_MMIO_BASE   = 0x63f00000,

		CSU_BASE           = 0x63f9c000,
		CSU_SIZE           = 0x00001000,

		/**
		 * Currently, we limit secure RAM to 256 MB only,
		 * because the memory protection feature of the M4IF
		 * on this platform allows to protect a max. region of
		 * 256MB per RAM bank only.
		 */
		SECURE_RAM_BASE    = RAM_BANK_0_BASE,
		SECURE_RAM_SIZE    = 256 * 1024 * 1024,
	};
};

#endif /* _INCLUDE__DRIVERS__DEFS__IMX53_H_ */
