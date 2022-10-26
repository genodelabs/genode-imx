/*
 * \brief  Dummy definitions of Linux Kernel functions - handled manually
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

#include <linux/of_iommu.h>

const struct iommu_ops * of_iommu_configure(struct device * dev,struct device_node * master_np,const u32 * id)
{
	static struct iommu_ops ops;
	lx_emul_trace(__func__);
	return &ops;
}


#include <linux/nmi.h>

notrace void touch_softlockup_watchdog_sched(void)
{
	lx_emul_trace(__func__);
}

