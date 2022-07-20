/*
 * \brief  Dummy definitions of Linux Kernel functions - handled manually
 * \author Josef Soentgen
 * \date   2021-10-29
 */

/*
 * Copyright (C) 2021 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#include <lx_emul.h>

unsigned long __must_check __arch_clear_user(void __user *to, unsigned long n);
unsigned long __must_check __arch_clear_user(void __user *to, unsigned long n)
{
	lx_emul_trace_and_stop(__func__);
}

bool arm64_use_ng_mappings = false;
EXPORT_SYMBOL(arm64_use_ng_mappings);


#include <linux/gfp.h>

struct page * alloc_pages_current(gfp_t gfp,unsigned order)
{
	lx_emul_trace_and_stop(__func__);
}


#include <asm/pgtable.h>

pgprot_t pgprot_noncached(pgprot_t prot)
{
	lx_emul_trace_and_stop(__func__);
}


pgprot_t pgprot_writecombine(pgprot_t prot)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pinctrl/devinfo.h>

int pinctrl_bind_pins(struct device * dev)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/pinctrl/devinfo.h>

int pinctrl_init_done(struct device * dev)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/of_iommu.h>

const struct iommu_ops * of_iommu_configure(struct device * dev,struct device_node * master_np,const u32 * id)
{
	static struct iommu_ops ops;
	lx_emul_trace(__func__);
	return &ops;
}


#include <linux/dma-map-ops.h>

void arch_setup_dma_ops(struct device * dev,u64 dma_base,u64 size,const struct iommu_ops * iommu,bool coherent)
{
	lx_emul_trace(__func__);
}


#include <linux/dma-map-ops.h>

void arch_teardown_dma_ops(struct device * dev)
{
	lx_emul_trace(__func__);
}


#include <linux/clk/clk-conf.h>

int of_clk_set_defaults(struct device_node * node,bool clk_supplier)
{
	lx_emul_trace(__func__);
	return 0;
}


extern void irq_pm_install_action(struct irq_desc * desc,struct irqaction * action);
void irq_pm_install_action(struct irq_desc * desc,struct irqaction * action)
{
	lx_emul_trace(__func__);
}


extern void irq_pm_remove_action(struct irq_desc * desc,struct irqaction * action);
void irq_pm_remove_action(struct irq_desc * desc,struct irqaction * action)
{
	lx_emul_trace(__func__);
}


extern void register_handler_proc(unsigned int irq,struct irqaction * action);
void register_handler_proc(unsigned int irq,struct irqaction * action)
{
	lx_emul_trace(__func__);
}


extern void register_irq_proc(unsigned int irq,struct irq_desc * desc);
void register_irq_proc(unsigned int irq,struct irq_desc * desc)
{
	lx_emul_trace(__func__);
}


#include <linux/pm_runtime.h>

void __pm_runtime_disable(struct device * dev,bool check_resume)
{
	lx_emul_trace(__func__);
}


#include <linux/pm_runtime.h>

int __pm_runtime_suspend(struct device * dev,int rpmflags)
{
	lx_emul_trace(__func__);
	return  0;
}


#include <linux/pm_runtime.h>

void __pm_runtime_use_autosuspend(struct device * dev,bool use)
{
	lx_emul_trace(__func__);
}


#include <linux/pm_runtime.h>

void pm_runtime_enable(struct device * dev)
{
	lx_emul_trace(__func__);
}


#include <linux/pm_runtime.h>

void pm_runtime_set_autosuspend_delay(struct device * dev,int delay)
{
	lx_emul_trace(__func__);
}


#include <linux/sysfs.h>

void sysfs_remove_file_ns(struct kobject * kobj,const struct attribute * attr,const void * ns)
{
	lx_emul_trace(__func__);
}


#include <linux/thermal.h>

struct thermal_cooling_device * thermal_of_cooling_device_register(struct device_node * np,const char * type,void * devdata,const struct thermal_cooling_device_ops * ops)
{
	lx_emul_trace(__func__);
	return NULL;
}


#include <linux/sched.h>

void sched_set_fifo(struct task_struct * p)
{
	lx_emul_trace(__func__);
}


void sched_set_fifo_low(struct task_struct * p)
{
	lx_emul_trace(__func__);
}


extern int devtmpfs_create_node(struct device * dev);
int devtmpfs_create_node(struct device * dev)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/thread_info.h>

void __check_object_size(const void * ptr,unsigned long n,bool to_user)
{
	lx_emul_trace(__func__);
}


void __lockfunc _raw_read_unlock(rwlock_t * lock)
{
	lx_emul_trace(__func__);
}


#include <linux/dma-mapping.h>

size_t dma_max_mapping_size(struct device * dev)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/mm.h>

bool is_vmalloc_addr(const void * x)
{
	lx_emul_trace(__func__);
	return false;
}


int set_page_dirty(struct page * page)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/random.h>

void add_interrupt_randomness(int irq,int irq_flags)
{
	lx_emul_trace(__func__);
}


#include <linux/vmalloc.h>

void vunmap(const void * addr)
{
	lx_emul_trace(__func__);
}


#include <linux/swap.h>

void check_move_unevictable_pages(struct pagevec * pvec)
{
	lx_emul_trace(__func__);
}


#include <linux/ratelimit_types.h>

int ___ratelimit(struct ratelimit_state * rs,const char * func)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/vmalloc.h>

void * __vmalloc(unsigned long size,gfp_t gfp_mask)
{
	lx_emul_trace(__func__);
	return NULL;
}


#include <linux/capability.h>

bool capable(int cap)
{
	lx_emul_trace(__func__);
	return true;
}


#include <linux/irq_work.h>

bool irq_work_needs_cpu(void)
{
	return false;
}


#include <linux/sched/nohz.h>

void calc_load_nohz_start(void)
{
	lx_emul_trace(__func__);
}


#include <linux/sched/nohz.h>

void calc_load_nohz_stop(void)
{
	lx_emul_trace(__func__);
}


#include <linux/vmstat.h>

void quiet_vmstat(void)
{
	lx_emul_trace(__func__);
}


#include <linux/sched/nohz.h>

void nohz_balance_enter_idle(int cpu)
{
	lx_emul_trace(__func__);
}


#include <linux/nmi.h>

notrace void touch_softlockup_watchdog_sched(void)
{
	lx_emul_trace(__func__);
}


#include <linux/kernel_stat.h>

void account_idle_ticks(unsigned long ticks)
{
	lx_emul_trace(__func__);
}


#include <linux/sched/nohz.h>

void wake_up_nohz_cpu(int cpu)
{
	lx_emul_trace(__func__);
}


#include <linux/wait_bit.h>

void __init wait_bit_init(void)
{
	lx_emul_trace(__func__);
}
