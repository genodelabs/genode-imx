/**
 * \brief  Backend implementation for Linux
 * \author Josef Soentgen
 * \date   2021-08-09
 */

/*
 * Copyright (C) 2021 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#ifndef _LX_DRM_H_
#define _LX_DRM_H_

#ifdef __cplusplus
extern "C" {
#endif

void *lx_drm_open(void);
void  lx_drm_close(void *);

int       lx_drm_ioctl_etnaviv_gem_param(void *, unsigned char, unsigned long long*);
int       lx_drm_ioctl_etnaviv_gem_submit(void *, unsigned long, unsigned int*);
unsigned  lx_drm_gem_submit_bo_count(void const*);
unsigned *lx_drm_gem_submit_bo_handle(void*, unsigned);
int       lx_drm_ioctl_etnaviv_gem_new(void *, unsigned long, unsigned int *);
int       lx_drm_ioctl_etnaviv_gem_info(void *, unsigned int, unsigned long long *);
int       lx_drm_ioctl_etnaviv_cpu_prep(void *, unsigned int, int);
int       lx_drm_ioctl_etnaviv_cpu_fini(void *, unsigned int);
int       lx_drm_ioctl_gem_close(void *, unsigned int);
int       lx_drm_ioctl_etnaviv_wait_fence(void *, unsigned int);


#ifdef __cplusplus
}
#endif

#endif /* _LX_DRM_H_ */
