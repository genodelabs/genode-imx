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
	return dma_alloc_attrs(dev, size, dma_handle, gfp, attrs);
}


#include <linux/gfp.h>
#include <linux/slab.h>

unsigned long get_zeroed_page(gfp_t gfp_mask)
{
	return (unsigned long)__alloc_pages(GFP_KERNEL, 0, 0, NULL)->virtual;
}


void * page_frag_alloc_align(struct page_frag_cache *nc,
                             unsigned int fragsz, gfp_t gfp_mask,
                             unsigned int align_mask)
{
	struct page *page;

	if (fragsz > PAGE_SIZE) {
		printk("no support for fragments larger than PAGE_SIZE\n");
		lx_emul_backtrace();
		return NULL;
	}

	page = __alloc_pages(gfp_mask, 0, 0, NULL);

	if (!page)
		return NULL;

	return page->virtual;
}


void page_frag_free(void * addr)
{
	struct page *page = virt_to_page(addr);
	if (!page) {
		printk("BUG %s: page for addr: %p not found\n", __func__, addr);
		lx_emul_backtrace();
	}

	__free_pages(page, 0ul);
}


#include <../mm/slab.h>

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


int kmem_cache_alloc_bulk(struct kmem_cache * s,gfp_t flags, size_t nr,void ** p)
{
	size_t i;
	for (i = 0; i < nr; i++)
		p[i] = kmem_cache_alloc(s, flags);

	return nr;
}


void * kmem_cache_alloc_lru(struct kmem_cache * cachep,struct list_lru * lru,gfp_t flags)
{
	return kmem_cache_alloc(cachep, flags);
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


#include <lx_emul/random.h>

u8 get_random_u8(void)
{
    return (u8)lx_emul_random_gen_u32();
}


#include <asm-generic/softirq_stack.h>

void do_softirq_own_stack(void)
{
	__do_softirq();
}
