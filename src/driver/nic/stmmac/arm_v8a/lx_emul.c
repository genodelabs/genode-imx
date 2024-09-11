/*
 * \brief  Linux emulation environment specific to this driver
 * \author Stefan Kalkowski
 * \date   2024-05-27
 */

/*
 * Copyright (C) 2021 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#include <lx_emul.h>
#include <linux/slab.h>


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


#include <asm-generic/softirq_stack.h>
#include <linux/interrupt.h>

void do_softirq_own_stack(void)
{
	__do_softirq();
}


#include <linux/proc_ns.h>

int proc_alloc_inum(unsigned int * inum)
{
	*inum = 1; /* according to linux/proc_ns.h without CONFIG_PROC_FS */
	return 0;
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


#include <linux/mfd/syscon.h>
#include <linux/regmap.h>

struct regmap * syscon_regmap_lookup_by_phandle(struct device_node * np,const char * property)
{
	static u32 dummy_regs[32];
	static struct regmap_config config = {
		.reg_bits = 32,
		.val_bits = 32,
		.reg_stride = 4,
		.val_format_endian = REGMAP_ENDIAN_NATIVE,
	};
	struct regmap *regmap = regmap_init_mmio(NULL, &dummy_regs, &config);
	lx_emul_trace(__func__);
	return regmap;
}


#include <linux/netdevice.h>

u8 netdev_rss_key[NETDEV_RSS_KEY_LEN] __read_mostly;

void netdev_rss_key_fill(void *buffer, size_t len)
{
	BUG_ON(len > sizeof(netdev_rss_key));
	net_get_random_once(netdev_rss_key, sizeof(netdev_rss_key));
	memcpy(buffer, netdev_rss_key, len);
}
EXPORT_SYMBOL(netdev_rss_key_fill);


#include <linux/gfp.h>

void page_frag_free(void * addr)
{
	lx_emul_mem_free(addr);
}


#include <linux/gfp.h>
#include <linux/slab.h>

unsigned long get_zeroed_page(gfp_t gfp_mask)
{
	return (unsigned long)__alloc_pages(GFP_KERNEL, 0, 0, NULL)->virtual;
}


#include <linux/mm.h>

bool is_vmalloc_addr(const void * x)
{
	return false;
}

