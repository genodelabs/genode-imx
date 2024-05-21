/*
 * \brief  Definitions of Linux Kernel functions
 * \author Stefan Kalkowski
 * \date   2022-10-17
 */

/*
 * Copyright (C) 2022 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#include <lx_emul.h>
#include <lx_emul/irq.h>

#include <linux/sched.h>

// int __sched _cond_resched(void)
// {
// 	if (should_resched(0)) {
// 		schedule();
// 		return 1;
// 	}
// 	return 0;
// }


#include <linux/irqchip.h>

IRQCHIP_DECLARE(dde_gic_a7,     "arm,cortex-a7-gic", lx_emul_irq_init);
IRQCHIP_DECLARE(dde_tzic_imx53, "fsl,imx53-tzic",    lx_emul_irq_init);
