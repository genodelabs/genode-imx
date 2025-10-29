/*
 * \brief   i.MX53 Quickstart board definitions
 * \author  Stefan Kalkowski
 * \date    2017-03-22
 */

/*
 * Copyright (C) 2017 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _SRC__BOOTSTRAP__SPEC__USB_ARMORY__BOARD_H_
#define _SRC__BOOTSTRAP__SPEC__USB_ARMORY__BOARD_H_

#include <hw/spec/arm/usb_armory_board.h>
#include <hw/spec/arm/imx_tzic.h>

#include <spec/arm/cortex_a8_page_table.h>
#include <spec/arm/cpu.h>

namespace Board {

	using namespace Hw::Usb_armory_board;

	using Hw::Global_interrupt_controller;
	using Hw::Local_interrupt_controller;

	bool secure_irq(unsigned irq);
}

#endif /* _SRC__BOOTSTRAP__SPEC__USB_ARMORY__BOARD_H_ */
