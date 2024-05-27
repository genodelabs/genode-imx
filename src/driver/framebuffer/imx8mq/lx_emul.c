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

#include <asm-generic/softirq_stack.h>

void __do_softirq(void);
void do_softirq_own_stack(void)
{
	__do_softirq();
}


#include <asm/io.h>
#include <lx_emul/io_mem.h>

void __iomem * ioremap_prot(phys_addr_t phys_addr,size_t size,unsigned long prot)
{
	return lx_emul_io_mem_map(phys_addr, size);
}


#include <linux/mount.h>
#include <linux/fs.h>
#include <linux/slab.h>

struct vfsmount * kern_mount(struct file_system_type * type)
{
	struct vfsmount *m;

	m = kzalloc(sizeof (struct vfsmount), 0);
	if (!m) {
		return (struct vfsmount*)ERR_PTR(-ENOMEM);
	}

	return m;
}
