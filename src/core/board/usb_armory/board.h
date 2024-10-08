/*
 * \brief  Board driver
 * \author Stefan Kalkowski
 * \author Martin Stein
 * \date   2012-10-24
 */

/*
 * Copyright (C) 2012-2017 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _CORE__SPEC__USB_ARMORY__BOARD_H_
#define _CORE__SPEC__USB_ARMORY__BOARD_H_

/* base-hw internal includes */
#include <hw/spec/arm/imx_tzic.h>
#include <hw/spec/arm/usb_armory_board.h>

/* base-hw core includes */
#include <spec/arm/imx_epit.h>
#include <spec/arm/trustzone_board.h>
#include <spec/arm_v7/cpu_support.h>
#include <spec/arm/cortex_a8_page_table.h>

namespace Core { using Cpu = Arm_v7_cpu; }

namespace Board { using namespace Hw::Usb_armory_board; }

#endif /* _CORE__SPEC__USB_ARMORY__BOARD_H_ */
