/**
 * \brief  Dummy definitions of Linux Kernel functions
 * \author Stefan Kalkowski
 * \date   2024-05-27
 */

/*
 * Copyright (C) 2024 Genode Labs GmbH
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


#ifdef __cplusplus
extern "C" {
#endif

void lx_emul_get_mac_address(void *buf);

#ifdef __cplusplus
}
#endif
