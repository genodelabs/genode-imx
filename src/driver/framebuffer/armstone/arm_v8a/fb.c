/*
 * \brief  Linux kernel framebuffer device support
 * \author Stefan Kalkowski
 * \date   2021-05-03
 */

/*
 * Copyright (C) 2021 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/fb.h>
#include <linux/of.h>
#include <drm/drm_fb_helper.h>
#include <lx_emul/fb.h>

struct fb_info * framebuffer_alloc(size_t size,struct device * dev)
{
#define BYTES_PER_LONG (BITS_PER_LONG/8)
#define PADDING (BYTES_PER_LONG - (sizeof(struct fb_info) % BYTES_PER_LONG))
	int fb_info_size = sizeof(struct fb_info);
	struct fb_info *info;
	char *p;

	if (size) {
		fb_info_size += PADDING;
	}

	p = kzalloc(fb_info_size + size, GFP_KERNEL);

	if (!p)
		return NULL;

	info = (struct fb_info *) p;

	if (size)
		info->par = p + fb_info_size;

	info->device = dev;
	info->fbcon_rotate_hint = -1;

#if IS_ENABLED(CONFIG_FB_BACKLIGHT)
	mutex_init(&info->bl_curve_mutex);
#endif

	return info;
#undef PADDING
#undef BYTES_PER_LONG
}

#define FBPIXMAPSIZE (1024 * 8)

struct class *fb_class;

int
fb_pan_display(struct fb_info *info, struct fb_var_screeninfo *var)
{
	struct fb_fix_screeninfo *fix = &info->fix;
	unsigned int yres = info->var.yres;
	int err = 0;

	if (var->yoffset > 0) {
		if (var->vmode & FB_VMODE_YWRAP) {
			if (!fix->ywrapstep || (var->yoffset % fix->ywrapstep))
				err = -EINVAL;
			else
				yres = 0;
		} else if (!fix->ypanstep || (var->yoffset % fix->ypanstep))
			err = -EINVAL;
	}

	if (var->xoffset > 0 && (!fix->xpanstep ||
				 (var->xoffset % fix->xpanstep)))
		err = -EINVAL;

	if (err || !info->fbops->fb_pan_display ||
	    var->yoffset > info->var.yres_virtual - yres ||
	    var->xoffset > info->var.xres_virtual - info->var.xres)
		return -EINVAL;

	if ((err = info->fbops->fb_pan_display(var, info)))
		return err;
	info->var.xoffset = var->xoffset;
	info->var.yoffset = var->yoffset;
	if (var->vmode & FB_VMODE_YWRAP)
		info->var.vmode |= FB_VMODE_YWRAP;
	else
		info->var.vmode &= ~FB_VMODE_YWRAP;
	return 0;
}
EXPORT_SYMBOL(fb_pan_display);

int
fb_set_var(struct fb_info *info, struct fb_var_screeninfo *var)
{
	int ret = 0;
	u32 activate;
	struct fb_var_screeninfo old_var;
	struct fb_videomode mode;
	struct fb_event event;
	u32 unused;

	if (!(var->activate & FB_ACTIVATE_FORCE) &&
	    !memcmp(&info->var, var, sizeof(struct fb_var_screeninfo)))
		return 0;

	activate = var->activate;

	/* When using FOURCC mode, make sure the red, green, blue and
	 * transp fields are set to 0.
	 */
	if ((info->fix.capabilities & FB_CAP_FOURCC) &&
	    var->grayscale > 1) {
		if (var->red.offset     || var->green.offset    ||
		    var->blue.offset    || var->transp.offset   ||
		    var->red.length     || var->green.length    ||
		    var->blue.length    || var->transp.length   ||
		    var->red.msb_right  || var->green.msb_right ||
		    var->blue.msb_right || var->transp.msb_right)
			return -EINVAL;
	}

	if (!info->fbops->fb_check_var) {
		*var = info->var;
		return 0;
	}

	/* bitfill_aligned() assumes that it's at least 8x8 */
	if (var->xres < 8 || var->yres < 8)
		return -EINVAL;

	/* Too huge resolution causes multiplication overflow. */
	if (check_mul_overflow(var->xres, var->yres, &unused) ||
	    check_mul_overflow(var->xres_virtual, var->yres_virtual, &unused))
		return -EINVAL;

	ret = info->fbops->fb_check_var(var, info);

	if (ret)
		return ret;

	/* verify that virtual resolution >= physical resolution */
	if (var->xres_virtual < var->xres ||
	    var->yres_virtual < var->yres) {
		pr_warn("WARNING: fbcon: Driver '%s' missed to adjust virtual screen size (%ux%u vs. %ux%u)\n",
			info->fix.id,
			var->xres_virtual, var->yres_virtual,
			var->xres, var->yres);
		return -EINVAL;
	}

	old_var = info->var;
	info->var = *var;

	if (info->fbops->fb_set_par) {
		ret = info->fbops->fb_set_par(info);

		if (ret) {
			info->var = old_var;
			printk(KERN_WARNING "detected "
				"fb_set_par error, "
				"error code: %d\n", ret);
			return ret;
		}
	}

	fb_pan_display(info, &info->var);
	fb_set_cmap(&info->cmap, info);
	fb_var_to_videomode(&mode, &info->var);

	if (info->modelist.prev && info->modelist.next &&
	    !list_empty(&info->modelist))
		ret = fb_add_videomode(&mode, &info->modelist);

	if (ret)
		return ret;

	event.info = info;
	event.data = &mode;
	fb_notifier_call_chain(FB_EVENT_MODE_CHANGE, &event);

	return 0;
}
EXPORT_SYMBOL(fb_set_var);

int register_framebuffer(struct fb_info * fb_info)
{
	struct fb_videomode mode;

	fb_info->node = 0;
	refcount_set(&fb_info->count, 1);
	mutex_init(&fb_info->lock);
	mutex_init(&fb_info->mm_lock);

	fb_info->dev = device_create(fb_class, fb_info->device,
								 MKDEV(FB_MAJOR, 0), NULL, "fb%d", 0);

		if (IS_ERR(fb_info->dev)) {
		/* Not fatal */
		printk(KERN_WARNING "Unable to create device for framebuffer %d; errno = %ld\n", 0, PTR_ERR(fb_info->dev));
		fb_info->dev = NULL;
	}

	if (fb_info->pixmap.addr == NULL) {
		fb_info->pixmap.addr = kmalloc(FBPIXMAPSIZE, GFP_KERNEL);
		if (fb_info->pixmap.addr) {
			fb_info->pixmap.size = FBPIXMAPSIZE;
			fb_info->pixmap.buf_align = 1;
			fb_info->pixmap.scan_align = 1;
			fb_info->pixmap.access_align = 32;
			fb_info->pixmap.flags = FB_PIXMAP_DEFAULT;
		}
	}
	fb_info->pixmap.offset = 0;

	if (!fb_info->pixmap.blit_x)
		fb_info->pixmap.blit_x = ~(u32)0;

	if (!fb_info->pixmap.blit_y)
		fb_info->pixmap.blit_y = ~(u32)0;

	if (!fb_info->modelist.prev || !fb_info->modelist.next)
		INIT_LIST_HEAD(&fb_info->modelist);

	fb_var_to_videomode(&mode, &fb_info->var);
	fb_add_videomode(&mode, &fb_info->modelist);

	{
		struct fb_var_screeninfo var = fb_info->var;
		struct list_head *pos, *n;
		struct fb_modelist *modelist;
		struct fb_videomode *m, mode;
		int err;

		list_for_each_safe(pos, n, &fb_info->modelist) {
			modelist = list_entry(pos, struct fb_modelist, list);
			m = &modelist->mode;
			fb_videomode_to_var(&var, m);
			var.activate = FB_ACTIVATE_TEST;
			err = fb_set_var(fb_info, &var);
			fb_var_to_videomode(&mode, &var);
			if (err || !fb_mode_is_equal(m, &mode)) {
				list_del(pos);
				kfree(pos);
			}
		}
	}

	fb_pan_display(fb_info, &fb_info->var);

	lx_emul_framebuffer_ready(fb_info->screen_base, fb_info->screen_size,
	                          fb_info->var.xres, fb_info->var.yres);
	return 0;
}


bool lx_emul_machine_is_compatible(char const *compat)
{
	return of_machine_is_compatible(compat);
}
