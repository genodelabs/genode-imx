/*
 * \brief  Dummy definitions of Linux Kernel functions - handled manually
 * \author Sebastian Sumpf
 * \date   2004-09-03
 */

/*
 * Copyright (C) 2024 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#include <lx_emul.h>

#include <linux/percpu.h>

/* kernel/sched/sched.h */
bool sched_smp_initialized = true;

DEFINE_PER_CPU(unsigned long, cpu_scale);


#include <linux/tracepoint-defs.h>

const struct trace_print_flags pageflag_names[] = { {0,NULL}};


/* mm/debug.c */
const struct trace_print_flags pagetype_names[] = {
	{0, NULL}
};


struct dl_bw;
void init_dl_bw(struct dl_bw *dl_b)
{
	lx_emul_trace_and_stop(__func__);
}


struct irq_work;
extern void rto_push_irq_work_func(struct irq_work *work);
void rto_push_irq_work_func(struct irq_work *work)
{
	lx_emul_trace_and_stop(__func__);
}


/* kernel/sched/cpudeadline.h */
struct cpudl;
int  cpudl_init(struct cpudl *cp)
{
	lx_emul_trace_and_stop(__func__);
	return -1;
}


void cpudl_cleanup(struct cpudl *cp)
{
	lx_emul_trace_and_stop(__func__);
}


/* include/linux/sched/topology.h */
int arch_asym_cpu_priority(int cpu)
{
	lx_emul_trace_and_stop(__func__);
	return 0;
}


#include <linux/random.h>

int __cold execute_with_initialized_rng(struct notifier_block * nb)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/sysctl.h>

struct ctl_table_header * register_sysctl_sz(const char * path,struct ctl_table * table,size_t table_size)
{
	lx_emul_trace(__func__);
	return NULL;
}


#include <linux/swiotlb.h>

#ifdef CONFIG_SWIOTLB
void swiotlb_dev_init(struct device * dev)
{
	lx_emul_trace(__func__);
}


bool is_swiotlb_allocated(void)
{
	lx_emul_trace(__func__);
	return false;
}
#endif
