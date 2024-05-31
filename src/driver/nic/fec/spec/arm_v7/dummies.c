/*
 * \brief  Dummy definitions of Linux Kernel functions - handled manually
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


extern void __bad_cmpxchg(volatile void *ptr, int size);
void __bad_cmpxchg(volatile void *ptr, int size)
{
	lx_emul_trace_and_stop(__func__);
}


extern void __bad_xchg(volatile void * ptr, int size);
void __bad_xchg(volatile void * ptr, int size)
{
	lx_emul_trace_and_stop(__func__);
}


asmlinkage void __div0(void);
asmlinkage void __div0(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <asm/uaccess.h>

unsigned long arm_copy_from_user(void *to, const void *from, unsigned long n)
{
	lx_emul_trace_and_stop(__func__);
}


#include <asm/uaccess.h>

unsigned long arm_copy_to_user(void *to, const void *from, unsigned long n)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/rcupdate.h>

noinstr int notrace debug_lockdep_rcu_enabled(void)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/rcutree.h>

int rcu_scheduler_active __read_mostly;


extern void arm_heavy_mb(void);
void arm_heavy_mb(void)
{
	lx_emul_trace(__func__);
}


#include <asm-generic/bug.h>

void warn_slowpath_fmt(const char * file,int line,unsigned taint,const char * fmt,...)
{
	lx_emul_trace(__func__);
}


#include <linux/pm_runtime.h>

void __pm_runtime_disable(struct device * dev,bool check_resume)
{
	lx_emul_trace(__func__);
}


#include <linux/mfd/syscon.h>

struct regmap * syscon_node_to_regmap(struct device_node * np)
{
	lx_emul_trace(__func__);
	return NULL;
}


#include <linux/ptp_clock_kernel.h>

struct ptp_clock * ptp_clock_register(struct ptp_clock_info * info,struct device * parent)
{
	lx_emul_trace(__func__);
	return NULL;
}


#include <soc/imx/cpuidle.h>

void imx6q_cpuidle_fec_irqs_used(void)
{
	lx_emul_trace(__func__);
}

