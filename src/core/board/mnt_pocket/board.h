/*
 * \brief  Board driver for core
 * \author Stefan Kalkowski
 * \date   2024-08-21
 */

/*
 * Copyright (C) 2024 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _CORE__BOARD__MNT_POCKET__BOARD_H_
#define _CORE__BOARD__MNT_POCKET__BOARD_H_

#include <hw/spec/arm_64/mnt_pocket_board.h>
#include <spec/arm/generic_timer.h>
#include <spec/arm/virtualization/gicv3.h>
#include <spec/arm_v8/cpu.h>

/* base-hw includes */
#include <spec/arm_64/cpu/vcpu_state_virtualization.h>

/* base-hw Core includes */
#include <spec/arm/virtualization/board.h>

namespace Board {
	using namespace Hw::Mnt_pocket_board;

	enum {
		TIMER_IRQ           = 14 + 16,
		VT_TIMER_IRQ        = 11 + 16,
		VT_MAINTAINANCE_IRQ = 9  + 16,
		VCPU_MAX            = 16
	};
};

#endif /* _CORE__BOARD__MNT_POCKET__BOARD_H_ */
