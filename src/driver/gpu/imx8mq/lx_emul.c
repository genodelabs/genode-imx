/*
 * \brief  Linux emulation C helper functions
 * \author Josef Soentgen
 * \date   2021-03-22
 */

/*
 * Copyright (C) 2021 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#include <lx_emul/task.h>
#include <lx_user/init.h>
#include <lx_user/io.h>

#include <linux/sched/task.h>

#include "emul.h"
#include "lx_emul.h"
#include "lx_drm.h"


#include <drm/drm_device.h>

extern struct drm_device *lx_drm_dev;

struct drm_device *_lx_drm_device;


#include <drm/drm_file.h>

struct lx_drm_private
{
	struct file  *file;
	struct inode *inode;
};


#include <linux/fs.h>

static struct file_operations const *_drm_fops;

int __register_chrdev(unsigned int major, unsigned int baseminor,
                      unsigned int count, char const * name,
                      struct file_operations const * fops)
{
	_drm_fops = fops;
	return 0;
}


#include <drm/drm_ioctl.h>
#include <linux/kdev_t.h>

void *lx_drm_open(void)
{
	int err;
	struct lx_drm_private *lx_drm_prv;

	if (!_drm_fops || !_drm_fops->open)
		return NULL;

	lx_drm_prv = (struct lx_drm_private*)kzalloc(sizeof (struct lx_drm_private), 0);
	if (!lx_drm_prv)
		return NULL;

	lx_drm_prv->inode = alloc_anon_inode(NULL);
	if (!lx_drm_prv->inode)
		goto free_session;

	lx_drm_prv->inode->i_rdev = MKDEV(DRM_MAJOR, DRM_MINOR_PRIMARY);

	lx_drm_prv->file = (struct file*)kzalloc(sizeof (struct file), 0);
	if (!lx_drm_prv->file)
		goto free_inode;

	err = _drm_fops->open(lx_drm_prv->inode, lx_drm_prv->file);
	if (err)
		goto free_file;

	return lx_drm_prv;

free_file:
	kfree(lx_drm_prv->file);
free_inode:
	kfree(lx_drm_prv->inode);
free_session:
	kfree(lx_drm_prv);
	return NULL;
}


#include <drm/drm_drv.h>
#include <../drivers/gpu/drm/drm_internal.h>

void lx_drm_close(void *p)
{
	struct lx_drm_private *lx_drm_prv;

	if (!p || !_drm_fops || !_drm_fops->release) {
		return;
	}

	lx_drm_prv = (struct lx_drm_private*)p;

	(void)_drm_fops->release(lx_drm_prv->inode, lx_drm_prv->file);

	kfree(lx_drm_prv->inode);
	kfree(lx_drm_prv->file);
	kfree(lx_drm_prv);
}


#include <drm/drm_ioctl.h>
#include <uapi/drm/drm.h>
#include <uapi/drm/etnaviv_drm.h>

unsigned lx_drm_gem_submit_bo_count(void const *p)
{
	struct drm_etnaviv_gem_submit const * const submit =
		(struct drm_etnaviv_gem_submit const*)p;
	return submit->nr_bos;
}


unsigned *lx_drm_gem_submit_bo_handle(void *p, unsigned index)
{
	struct drm_etnaviv_gem_submit * const submit =
		(struct drm_etnaviv_gem_submit*)p;

	struct drm_etnaviv_gem_submit_bo *bos =
		(struct drm_etnaviv_gem_submit_bo*)(submit->bos + (unsigned long)submit);

	struct drm_etnaviv_gem_submit_bo * const bo = &bos[index];
	return &bo->handle;
}


static void lx_drm_gem_submit_in(struct drm_etnaviv_gem_submit *submit)
{
	submit->bos    += (unsigned long)submit;
	submit->relocs += (unsigned long)submit;
	submit->pmrs   += (unsigned long)submit;
	submit->stream += (unsigned long)submit;
}


static void lx_drm_version_in(struct drm_version *version)
{
	/* set proper pointer value from offset */
	version->name += (unsigned long)version;
	version->date += (unsigned long)version;
	version->desc += (unsigned long)version;
}


static void lx_drm_version_out(struct drm_version *version)
{
	/* set proper offset value from pointer */
	version->name -= (unsigned long)version;
	version->date -= (unsigned long)version;
	version->desc -= (unsigned long)version;
}


static int lx_drm_in(unsigned int cmd, unsigned long arg)
{
	unsigned int const nr = DRM_IOCTL_NR(cmd);
	bool const is_driver_ioctl =
		nr >= DRM_COMMAND_BASE && nr < DRM_COMMAND_END;

	if (is_driver_ioctl) {
		unsigned const int dnr = nr - DRM_COMMAND_BASE;

		switch (dnr) {
		case DRM_ETNAVIV_GEM_SUBMIT:
			lx_drm_gem_submit_in((struct drm_etnaviv_gem_submit*)arg);
			break;
		default:
			break;
		}
	} else {
		switch (nr) {
		case DRM_IOCTL_NR(DRM_IOCTL_VERSION):
			lx_drm_version_in((struct drm_version*)arg);
			break;
		default:
			break;
		}
	}
	return 0;
}


static int lx_drm_out(unsigned int cmd, unsigned long arg)
{
	unsigned int const nr = DRM_IOCTL_NR(cmd);
	bool const is_driver_ioctl =
		nr >= DRM_COMMAND_BASE && nr < DRM_COMMAND_END;

	if (is_driver_ioctl) {
		unsigned const int dnr = nr - DRM_COMMAND_BASE;

		switch (dnr) {
		default:
			break;
		}
	} else {
		switch (nr) {
		case DRM_IOCTL_NR(DRM_IOCTL_VERSION):
			lx_drm_version_out((struct drm_version*)arg);
			break;
		default:
			break;
		}
	}
	return 0;
}

int lx_drm_ioctl(void *p, unsigned int cmd, unsigned long arg)
{
	struct lx_drm_private *lx_drm_prv;
	int res;

	lx_drm_prv = (struct lx_drm_private*)p;

	if (!lx_drm_prv) {
		return -1;
	}

	if (cmd & IOC_IN) {
		lx_drm_in(cmd, arg);
	}
	res = drm_ioctl(lx_drm_prv->file, cmd, arg);
	if (cmd & IOC_OUT) {
		lx_drm_out(cmd, arg);
	}
	return res;
}


int lx_drm_check_gem_new(unsigned int cmd)
{
	unsigned int const nr = DRM_IOCTL_NR(cmd);

	bool const is_driver_ioctl =
		nr >= DRM_COMMAND_BASE && nr < DRM_COMMAND_END;

	if (!is_driver_ioctl) {
		return 0;
	}

	return (nr - DRM_COMMAND_BASE) == DRM_ETNAVIV_GEM_NEW ? 1 : 0;
}


unsigned int lx_drm_get_gem_new_handle(unsigned long arg)
{
	struct drm_etnaviv_gem_new const *p =
		(struct drm_etnaviv_gem_new const *)arg;

	return p->handle;
}


int lx_drm_check_gem_close(unsigned int cmd)
{
	unsigned int const nr = DRM_IOCTL_NR(cmd);

	bool const is_driver_ioctl =
		nr >= DRM_COMMAND_BASE && nr < DRM_COMMAND_END;

	if (is_driver_ioctl) {
		return 0;
	}

	return nr == DRM_IOCTL_NR(DRM_IOCTL_GEM_CLOSE) ? 1 : 0;
}


unsigned int lx_drm_get_gem_close_handle(unsigned long arg)
{
	struct drm_gem_close const *p =
		(struct drm_gem_close const *)arg;

	return p->handle;
}


int lx_drm_close_handle(void *p, unsigned int handle)
{
	struct lx_drm_private *lx_drm_prv;

	struct drm_gem_close arg = {
		.handle = handle
	};

	lx_drm_prv = (struct lx_drm_private*)p;

	return drm_ioctl(lx_drm_prv->file, DRM_IOCTL_GEM_CLOSE, (unsigned long)&arg);
}


/*
 * The next functions are used by the Gpu lx_drm_prv to perform I/O controls.
 */

int lx_drm_ioctl_etnaviv_gem_param(void *lx_drm_prv, unsigned char param,
                                   unsigned long long *value)
{
	int err;
	struct drm_etnaviv_param req = {
		.pipe = 0,
		.param = param,
		.value = 0,
	};

	err = lx_drm_ioctl(lx_drm_prv, DRM_IOCTL_ETNAVIV_GET_PARAM, (unsigned long)&req);
	if (err) {
		return -1;
	}

	*value = req.value;
	return 0;
}


int lx_drm_ioctl_etnaviv_gem_submit(void *lx_drm_prv, unsigned long arg,
                                    unsigned int *fence)
{
	int err;
	struct drm_etnaviv_gem_submit *submit;

	err = lx_drm_ioctl(lx_drm_prv, DRM_IOCTL_ETNAVIV_GEM_SUBMIT, arg);
	if (err) {
		return err;
	}

	submit = (struct drm_etnaviv_gem_submit*)arg;

	*fence = submit->fence;
	return 0;
}


int lx_drm_ioctl_etnaviv_wait_fence(void *lx_drm_prv, unsigned int fence)
{
	int err;

	struct drm_etnaviv_wait_fence req = {
		.pipe = 0,
		.fence = fence,
		// .flags = ETNA_WAIT_NONBLOCK,
		.flags = 0,
	};

	err = lx_drm_ioctl(lx_drm_prv, DRM_IOCTL_ETNAVIV_WAIT_FENCE,
	                   (unsigned long) &req);

	return err;
}


int lx_drm_ioctl_etnaviv_gem_new(void *lx_drm_prv, unsigned long size,
                                 unsigned int *handle)
{
	int err;
	struct drm_etnaviv_gem_new req = {
		.size = size,
		.flags = ETNA_BO_WC,
		.handle = 0,
	};

	err = lx_drm_ioctl(lx_drm_prv, DRM_IOCTL_ETNAVIV_GEM_NEW, (unsigned long)&req);
	if (err) {
		return -1;
	}

	*handle = req.handle;
	return 0;
}


int lx_drm_ioctl_etnaviv_gem_info(void *lx_drm_prv, unsigned int handle,
                                  unsigned long long *offset)
{
	int err;
	struct drm_etnaviv_gem_info req = {
		.handle = handle,
	};

	err = lx_drm_ioctl(lx_drm_prv, DRM_IOCTL_ETNAVIV_GEM_INFO, (unsigned long)&req);
	if (err) {
		return -1;
	}

	*offset = req.offset;
	return 0;
}


int lx_drm_ioctl_etnaviv_cpu_prep(void *lx_drm_prv, unsigned int handle, int op)
{
	int err;

	struct drm_etnaviv_gem_cpu_prep req;
	struct timespec64 to;
	ktime_get_ts64(&to);
	// see mesa:
	//     get_abs_timeout(&req.timeout, 5000000000);
	to.tv_sec += 5;

	req.handle = handle,
	req.op     = op,
	req.timeout = (struct drm_etnaviv_timespec){ to.tv_sec, to.tv_nsec },

	err = lx_drm_ioctl(lx_drm_prv, DRM_IOCTL_ETNAVIV_GEM_CPU_PREP, (unsigned long)&req);
	if (err) {
		return -1;
	}

	return 0;
}


int lx_drm_ioctl_etnaviv_cpu_fini(void *lx_drm_prv, unsigned int handle)
{
	int err;
	struct drm_etnaviv_gem_cpu_fini req = {
		.handle = handle,
	};

	err = lx_drm_ioctl(lx_drm_prv, DRM_IOCTL_ETNAVIV_GEM_CPU_FINI, (unsigned long)&req);
	if (err) {
		return -1;
	}

	return 0;
}


int lx_drm_ioctl_gem_close(void *lx_drm_prv, unsigned int handle)
{
	int err;
	struct drm_gem_close req = {
		.handle = handle,
	};

	err = lx_drm_ioctl(lx_drm_prv, DRM_IOCTL_GEM_CLOSE, (unsigned long)&req);
	if (err) {
		return -1;
	}

	return 0;
}


#include <drm/drm_gem.h>
#include <drm/drm_vma_manager.h>
#include <lx_emul/shmem_file.h>

void *genode_lookup_mapping_from_offset(void *p,
                                        unsigned long offset,
                                        unsigned long size)
{
	struct lx_drm_private *lx_drm_prv;
	struct file *file;
	struct drm_file *drm_file;
	struct drm_device *dev;
	struct drm_vma_offset_manager *mgr;
	struct drm_vma_offset_node *node;

	lx_drm_prv = (struct lx_drm_private*)p;
	if (!lx_drm_prv)
		return NULL;

	file = lx_drm_prv->file;
	if (!file)
		return NULL;

	drm_file = file->private_data;
	if (!drm_file)
		return NULL;

	dev = drm_file->minor->dev;
	if (!dev)
		return NULL;

	mgr = dev->vma_offset_manager;

	drm_vma_offset_lock_lookup(mgr);
	node = drm_vma_offset_lookup_locked(mgr, offset / PAGE_SIZE,
	                                    size / PAGE_SIZE);
	drm_vma_offset_unlock_lookup(mgr);

	if (node) {
		struct drm_gem_object *obj =
			container_of(node, struct drm_gem_object, vma_node);
		if (obj) {
			struct file *f = obj->filp;
			if (f) {
				struct address_space *mapping = f->f_mapping;
				if (mapping) {
					struct shmem_file_buffer *private_data =
						mapping->private_data;
					if (private_data) {
						return private_data->addr;
					}
				}
			}
		}
	}
	return NULL;
}


#include <linux/fs.h>
#include <linux/mount.h>

int simple_pin_fs(struct file_system_type * type,struct vfsmount ** mount,int * count)
{
	*mount = kzalloc(sizeof(struct vfsmount), GFP_KERNEL);
	return 0;
}


static unsigned long _get_next_ino(void)
{
	static unsigned long count = 0;
	return ++count;
}


struct inode *alloc_anon_inode(struct super_block *s)
{
	struct inode *inode;

	inode = kzalloc(sizeof (struct inode), 0);
	if (!inode) {
		return (struct inode*)ERR_PTR(-ENOMEM);
	}

	inode->i_ino = _get_next_ino();

	return inode;
}


#include <linux/dma-mapping.h>

u64 dma_get_required_mask(struct device * dev)
{
	/* XXX query HW for DMA_MASK?  */
	enum { DMA_MASK = 0xbfffffffUL, };
	return DMA_MASK;
}


#include <lx_emul/alloc.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>

void *vzalloc(unsigned long size)
{
	return lx_emul_mem_alloc_aligned(size, ARCH_KMALLOC_MINALIGN);
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


#include <linux/dma-mapping.h>

int dma_map_sgtable(struct device *dev, struct sg_table *sgt,
                    enum dma_data_direction dir, unsigned long attrs)
{
	int nents = dma_map_sg_attrs(dev, sgt->sgl, sgt->orig_nents, dir, attrs);
	if (nents < 0)
		return nents;
	sgt->nents = nents;
	return 0;
}
