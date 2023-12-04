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
                                const char * name) { }


#include <asm/uaccess.h>

unsigned long arm_copy_from_user(void *to, const void *from, unsigned long n)
{
	memcpy(to, from, n);
	return 0;
}


#include <asm/uaccess.h>

unsigned long arm_copy_to_user(void *to, const void *from, unsigned long n)
{
	memcpy(to, from, n);
	return 0;
}



#include <linux/gfp.h>
#include <linux/mm.h>

struct page * __alloc_pages_nodemask(gfp_t gfp_mask, unsigned int order,
                                     int preferred_nid, nodemask_t * nodemask)
{
	unsigned const num_pages = (1 << order);
	void *   const ptr = lx_emul_mem_alloc_aligned(PAGE_SIZE*num_pages, PAGE_SIZE);
	return lx_emul_virt_to_pages(ptr, num_pages);
}


struct page *alloc_pages_current(gfp_t gfp, unsigned order)
{
	return __alloc_pages(gfp, order, 0, NULL);
}


#include <asm-generic/logic_io.h>
#include <lx_emul/io_mem.h>

void __iomem * ioremap(resource_size_t phys_addr, size_t size)
{
	return lx_emul_io_mem_map(phys_addr, size);
}


extern void arm_heavy_mb(void);
void arm_heavy_mb(void)
{
	static unsigned long dummy = 0;
	// FIXME: we shoud do an L2-cache flush only here.
	lx_emul_mem_cache_clean_invalidate(&dummy, sizeof(dummy));
}


