/*
 * \brief  Board driver for bootstrap
 * \author Alice Domage
 * \date   2024-02-27
 */

/*
 * Copyright (C) 2024 Genode Labs GmbH
 * Copyright (C) 2024 gapfruit ag
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _BOOTSTRAP__SPEC__IMX8MP_IOT_GATE__BOARD_H_
#define _BOOTSTRAP__SPEC__IMX8MP_IOT_GATE__BOARD_H_

#include <hw/spec/arm_64/imx8mp_iot_gate_board.h>
#include <hw/spec/arm_64/cpu.h>
#include <hw/spec/arm/gicv3.h>
#include <hw/spec/arm/lpae.h>

namespace Board {
	using namespace Hw::Imx8mp_iot_gate_board;

	struct Cpu : Hw::Arm_64_cpu
	{
		static void wake_up_all_cpus(void*);
	};

	using Hw::Pic;
};

#endif /* _BOOTSTRAP__SPEC__IMX8MP_IOT_GATE__BOARD_H_ */
