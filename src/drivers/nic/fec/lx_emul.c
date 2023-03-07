/*
 * \brief  Common definitions of Linux Kernel functions
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

#include <linux/fs.h>

int alloc_chrdev_region(dev_t * dev,unsigned baseminor,unsigned count,const char * name)
{
	static dev_t counter = 0;
	*dev = counter++;
	return 0;
}


#include <linux/dma-mapping.h>

void * dmam_alloc_attrs(struct device * dev,size_t size,dma_addr_t * dma_handle,gfp_t gfp,unsigned long attrs)
{
//	struct dma_devres *dr;
	void *vaddr;

//	dr = devres_alloc(dmam_release, sizeof(*dr), gfp);
//	if (!dr)
//		return NULL;

	vaddr = dma_alloc_attrs(dev, size, dma_handle, gfp, attrs);
	if (!vaddr) {
//		devres_free(dr);
		return NULL;
	}

//	dr->vaddr = vaddr;
//	dr->dma_handle = *dma_handle;
//	dr->size = size;
//	dr->attrs = attrs;
//
//	devres_add(dev, dr);

	return vaddr;
}


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


void dma_sync_single_for_cpu(struct device *dev, dma_addr_t addr,
                             size_t size, enum dma_data_direction dir)
{
	unsigned long const virt_addr = lx_emul_mem_virt_addr((void*)addr);

	if (!virt_addr)
		return;

	lx_emul_mem_cache_invalidate((void *)virt_addr, size);
}


void dma_sync_single_for_device(struct device * dev,dma_addr_t addr,size_t size,enum dma_data_direction dir)
{
	unsigned long const virt_addr = lx_emul_mem_virt_addr((void*)addr);

	if (!virt_addr)
		return;

	lx_emul_mem_cache_clean_invalidate((void *)virt_addr, size);
}


int dma_supported(struct device * dev,u64 mask)
{
	lx_emul_trace(__func__);
	return 1;
}


#include <linux/slab.h>

#ifdef CONFIG_TRACING
void * kmalloc_order_trace(size_t size,gfp_t flags,unsigned int order)
{
	return kmalloc(size, flags);
}
#endif


#include <linux/gfp.h>
#include <linux/slab.h>

unsigned long get_zeroed_page(gfp_t gfp_mask)
{
	void * const ptr = lx_emul_mem_alloc_aligned(PAGE_SIZE, PAGE_SIZE);
	return (unsigned long)lx_emul_virt_to_pages(ptr, 1)->virtual;
}


#include <linux/slab.h>

struct kmem_cache * kmem_cache_create_usercopy(const char * name,
                                               unsigned int size,
                                               unsigned int align,
                                               slab_flags_t flags,
                                               unsigned int useroffset,
                                               unsigned int usersize,
                                               void (* ctor)(void *))
{
	return kmem_cache_create(name, size, align, flags, ctor);
}


void kmem_cache_free_bulk(struct kmem_cache *s, size_t size, void **p)
{
	size_t i;

	for (i = 0; i < size; i++) {
		kmem_cache_free(s, p[i]);
	}
}


#include <linux/gfp.h>

void * page_frag_alloc(struct page_frag_cache * nc,unsigned int fragsz,gfp_t gfp_mask)
{
	return lx_emul_mem_alloc_aligned(fragsz, ARCH_KMALLOC_MINALIGN);
}


void page_frag_free(void * addr)
{
	lx_emul_mem_free(addr);
}


#include <linux/mm.h>

bool is_vmalloc_addr(const void * x)
{
	return false;
}


#include <linux/rtnetlink.h>

static DEFINE_MUTEX(rtnl_mutex);

int rtnl_is_locked(void)
{
	return mutex_is_locked(&rtnl_mutex);
}


void rtnl_lock(void)
{
	mutex_lock(&rtnl_mutex);
}


int rtnl_lock_killable(void)
{
	return mutex_lock_killable(&rtnl_mutex);
}


void rtnl_unlock(void)
{
	mutex_unlock(&rtnl_mutex);
}
