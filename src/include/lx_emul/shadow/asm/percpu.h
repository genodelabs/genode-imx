/**
 * \brief  Shadows Linux kernel asm/percpu.h
 * \author Stefan Kalkowski
 * \date   2021-04-14
 */

/*
 * Copyright (C) 2021 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#pragma once

#include_next <asm/percpu.h>

static inline unsigned long __dummy_cpu_offset(void)
{
	return 0;
}

#undef  __my_cpu_offset
#define __my_cpu_offset __dummy_cpu_offset()
