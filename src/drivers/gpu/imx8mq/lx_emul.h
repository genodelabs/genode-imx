/**
 * \brief  Dummy definitions of Linux Kernel functions
 * \author Stefan Kalkowski
 * \date   2021-03-16
 */

/*
 * Copyright (C) 2021 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

/* Needed to trace and stop */
#include <lx_emul/debug.h>

/* fix for wait_for_completion_timeout where the __sched include is missing */
#include <linux/sched/debug.h>

/* fix for missing include in linux/dynamic_debug.h */
#include <linux/compiler_attributes.h>

/* fix for missing include in linux/irqdesc.h */
#include <linux/irq.h>

/* fix for warning in drm/bridge/cdns-mhdp-common.h */
#include <linux/platform_device.h>

#ifdef __cplusplus
extern "C" {
#endif

void lx_emul_time_udelay(unsigned long usec);

void lx_user_wait_and_dispatch(void);

#ifdef __cplusplus
}
#endif

