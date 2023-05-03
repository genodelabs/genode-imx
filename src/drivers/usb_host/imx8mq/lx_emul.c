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


#include <linux/dma-mapping.h>

dma_addr_t dma_map_page_attrs(struct device * dev,
                              struct page * page,
                              size_t offset,
                              size_t size,
                              enum dma_data_direction dir,
                              unsigned long attrs)
{
	dma_addr_t    const dma_addr  = page_to_phys(page);
	unsigned long const virt_addr = (unsigned long)page_to_virt(page);

	lx_emul_mem_cache_clean_invalidate((void *)(virt_addr + offset), size);
	return dma_addr + offset;
}


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


#include <linux/dma-mapping.h>

int dma_supported(struct device * dev,u64 mask)
{
	lx_emul_trace(__func__);
	return 1;
}


#include <linux/dma-mapping.h>

void dma_unmap_page_attrs(struct device * dev,
                          dma_addr_t addr,
                          size_t size,
                          enum dma_data_direction dir,
                          unsigned long attrs)
{
	unsigned long const virt_addr = lx_emul_mem_virt_addr((void*)addr);

	if (!virt_addr)
		return;

	if (dir == DMA_FROM_DEVICE)
		lx_emul_mem_cache_invalidate((void *)virt_addr, size);
}


#include <linux/pci.h>

void lx_emul_register_pci_fixup(void (*fn)(struct pci_dev*),
                                const char * name)
{
	/* remove when enabling proper PCI support in the driver */
}


bool arm64_use_ng_mappings;


#include <linux/cdev.h>
#include <lx_emul/usb.h>

void cdev_init(struct cdev * cdev, const struct file_operations * fops)
{
	lx_emul_usb_register_devio(fops);
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

struct page * __alloc_pages_nodemask(gfp_t gfp_mask, unsigned int order,
                                     int preferred_nid, nodemask_t * nodemask)
{
	unsigned const num_pages = (1 << order);
	void *   const ptr = lx_emul_mem_alloc_aligned(PAGE_SIZE*num_pages, PAGE_SIZE);
	return lx_emul_virt_to_pages(ptr, num_pages);
}


void free_pages(unsigned long addr,unsigned int order)
{
	if (addr != 0ul)
		__free_pages(virt_to_page((void *)addr), order);
}


unsigned long __get_free_pages(gfp_t gfp_mask, unsigned int order)
{
	struct page *page = __alloc_pages(gfp_mask, order, 0);

	if (!page)
		return 0;

	return (unsigned long)page_address(page);
}


struct page *alloc_pages_current(gfp_t gfp, unsigned order)
{
	return __alloc_pages(gfp, order, 0);
}
