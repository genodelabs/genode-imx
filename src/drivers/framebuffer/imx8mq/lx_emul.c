/*
 * \brief  Common definitions of Linux Kernel functions
 * \author Stefan Kalkowski
 * \date   2022-02-08
 */

/*
 * Copyright (C) 2021 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#include <lx_emul.h>


#include <asm-generic/delay.h>
#include <linux/delay.h>

void __const_udelay(unsigned long xloops)
{
	unsigned long usecs = xloops / 0x10C7UL;
	if (usecs < 100)
		lx_emul_time_udelay(usecs);
	else
		usleep_range(usecs, usecs * 10);
}


#include <linux/gfp.h>

struct page * __alloc_pages_nodemask(gfp_t gfp_mask, unsigned int order,
                                     int preferred_nid, nodemask_t * nodemask)
{
	unsigned const num_pages = (1 << order);
	void *   const ptr = lx_emul_mem_alloc_aligned(PAGE_SIZE*num_pages, PAGE_SIZE);
	return lx_emul_virt_to_pages(ptr, num_pages);
}


#include <linux/kallsyms.h>

int sprint_symbol_no_offset(char * buffer, unsigned long address)
{
	return sprintf(buffer, "0x%lx", address);
}
