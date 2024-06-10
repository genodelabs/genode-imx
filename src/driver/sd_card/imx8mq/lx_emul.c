/*
 * \brief  Driver-specific emulation of Linux Kernel functions
 * \author Stefan Kalkowski
 * \date   2021-10-01
 */

/*
 * Copyright (C) 2021 Genode Labs GmbH
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


extern int cache_line_size(void);
int cache_line_size(void)
{
	return 128;
}


#include <linux/blkdev.h>
#include <linux/sched.h>

long __sched io_schedule_timeout(long timeout)
{
	long ret;
	int  old_iowait = current->in_iowait;

	current->in_iowait = 1;
	blk_flush_plug(current->plug, true);
	ret = schedule_timeout(timeout);
	current->in_iowait = old_iowait;

	return ret;
}


#include <../mm/slab.h>

void * kmem_cache_alloc_lru(struct kmem_cache * cachep,struct list_lru * lru,gfp_t flags)
{
	return kmem_cache_alloc(cachep, flags);
}


#include <linux/blkdev.h>

int bd_prepare_to_claim(struct block_device * bdev,void * holder)
{
	struct block_device *whole = bdev_whole(bdev);
	whole->bd_claiming = holder;
	return 0;
}


void bd_abort_claiming(struct block_device * bdev,void * holder)
{
	struct block_device *whole = bdev_whole(bdev);
	whole->bd_claiming = NULL;
}


#include <linux/ioprio.h>

int __get_task_ioprio(struct task_struct * p)
{
	return IOPRIO_DEFAULT;
}


#include <linux/mm.h>

bool is_vmalloc_addr(const void * x)
{
	return false;
}
