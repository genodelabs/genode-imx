/*
 * \brief  Linux emulation environment specific to this driver
 * \author Stefan Kalkowski
 * \date   2021-08-31
 */

/*
 * Copyright (C) 2021 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#include <lx_emul.h>
#include <linux/slab.h>


#include <linux/dmapool.h>

struct dma_pool { size_t size; };

void * dma_pool_alloc(struct dma_pool * pool, gfp_t mem_flags, dma_addr_t * handle)
{
	void * ret =
		lx_emul_mem_alloc_aligned_uncached(pool->size, PAGE_SIZE);
	*handle = lx_emul_mem_dma_addr(ret);
	return ret;
}


struct dma_pool * dma_pool_create(const char * name,
                                  struct device * dev,
                                  size_t size,
                                  size_t align,
                                  size_t boundary)
{
	struct dma_pool * pool = kmalloc(sizeof(struct dma_pool), GFP_KERNEL);
	pool->size = size;
	return pool;
}


void dma_pool_free(struct dma_pool * pool,void * vaddr,dma_addr_t dma)
{
	lx_emul_mem_free(vaddr);
}


#include <linux/pci.h>

void lx_emul_register_pci_fixup(void (*fn)(struct pci_dev*),
                                const char * name)
{
	/* remove when enabling proper PCI support in the driver */
}


unsigned long __must_check __arch_copy_from_user(void *to, const void __user *from, unsigned long n);
unsigned long __must_check __arch_copy_from_user(void *to, const void __user *from, unsigned long n)
{
	memcpy(to, from, n);
	return 0;
}


unsigned long __must_check __arch_copy_to_user(void __user *to, const void *from, unsigned long n);
unsigned long __must_check __arch_copy_to_user(void __user *to, const void *from, unsigned long n)
{
	memcpy(to, from, n);
	return 0;
}


#include <linux/gfp.h>
#include <linux/mm.h>

struct page *alloc_pages_current(gfp_t gfp, unsigned order)
{
	return __alloc_pages(gfp, order, 0, NULL);
}


#include <asm-generic/softirq_stack.h>

void do_softirq_own_stack(void)
{
	__do_softirq();
}


#include <linux/kernfs.h>

struct kernfs_node * kernfs_find_and_get_ns(struct kernfs_node * parent,const char * name,const void * ns)
{
	static struct kernfs_node dummy;

	/* usb_hub_create_port_device requires existing "state" dirent */
	if (strncmp("state", name, 5) == 0)
		return &dummy;

	return NULL;
}


#include <linux/sched.h>

void kick_process(struct task_struct *p)
{
	lx_emul_task_unblock(p);
}
