/*
 * \brief  Dummy definitions of Linux Kernel functions - handled manually
 * \author Stefan Kalkowski
 * \date   2021-08-31
 */

/*
 * Copyright (C) 2021 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#include <lx_emul.h>


#include <linux/threads.h>
unsigned long __per_cpu_offset[NR_CPUS] = { 0UL };


#include <linux/fs.h>

int __register_chrdev(unsigned int major,unsigned int baseminor,unsigned int count,const char * name,const struct file_operations * fops)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/pci.h>

int __pci_register_driver(struct pci_driver * drv,struct module * owner,const char * mod_name)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/pm_runtime.h>

void __pm_runtime_disable(struct device * dev,bool check_resume)
{
	lx_emul_trace(__func__);
}


#include <linux/pm_runtime.h>


void __pm_runtime_use_autosuspend(struct device * dev,bool use)
{
	lx_emul_trace(__func__);
}


#include <linux/pm_runtime.h>

int __pm_runtime_set_status(struct device * dev,unsigned int status)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/pm_runtime.h>

int __pm_runtime_suspend(struct device * dev,int rpmflags)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <asm-generic/delay.h>

void __udelay(unsigned long usecs)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/rwlock_api_smp.h>

unsigned long __lockfunc _raw_read_lock_irqsave(rwlock_t * lock)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/rwlock_api_smp.h>

void __lockfunc _raw_read_unlock_irqrestore(rwlock_t * lock,unsigned long flags)
{
	lx_emul_trace(__func__);
}


#include <linux/random.h>

void add_device_randomness(const void * buf,unsigned int size)
{
	lx_emul_trace(__func__);
}


#include <linux/random.h>

void add_interrupt_randomness(int irq,int irq_flags)
{
	lx_emul_trace(__func__);
}


#include <linux/gfp.h>

struct page *alloc_pages_current(gfp_t gfp, unsigned order)
{
	lx_emul_trace_and_stop(__func__);
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


#include <linux/cdev.h>

int cdev_add(struct cdev * p,dev_t dev,unsigned count)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/cdev.h>

void cdev_init(struct cdev * cdev,const struct file_operations * fops)
{
	lx_emul_trace(__func__);
}


#include <linux/clk.h>

void clk_bulk_disable(int num_clks,const struct clk_bulk_data * clks)
{
	lx_emul_trace(__func__);
}


#include <linux/clk.h>

int __must_check clk_bulk_get_all(struct device * dev,struct clk_bulk_data ** clks)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/clk.h>

int __must_check clk_bulk_enable(int num_clks,const struct clk_bulk_data * clks)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/clk.h>

int __must_check clk_bulk_prepare(int num_clks,const struct clk_bulk_data * clks)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/clk.h>

void clk_bulk_unprepare(int num_clks,const struct clk_bulk_data * clks)
{
	lx_emul_trace(__func__);
}


#include <linux/debugfs.h>

void debugfs_create_regset32(const char * name,umode_t mode,struct dentry * parent,struct debugfs_regset32 * regset)
{
	lx_emul_trace(__func__);
}


#include <linux/debugfs.h>

void debugfs_remove(struct dentry * dentry)
{
	lx_emul_trace(__func__);
}


#include <linux/pm_qos.h>

int dev_pm_qos_expose_flags(struct device * dev,s32 val)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/pm_qos.h>

int dev_pm_qos_add_request(struct device * dev,struct dev_pm_qos_request * req,enum dev_pm_qos_req_type type,s32 value)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/pm_qos.h>

int dev_pm_qos_remove_request(struct dev_pm_qos_request * req)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/pm_wakeup.h>

int device_init_wakeup(struct device * dev,bool enable)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/pm_wakeup.h>

void device_set_wakeup_capable(struct device * dev,bool capable)
{
	lx_emul_trace(__func__);
}


#include <linux/pm_wakeup.h>

int device_set_wakeup_enable(struct device * dev,bool enable)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/regulator/consumer.h>

struct regulator * devm_regulator_get(struct device * dev,const char * id)
{
	lx_emul_trace(__func__);
	return NULL;
}


#include <linux/reset.h>

struct reset_control * devm_reset_control_array_get(struct device * dev,bool shared,bool optional)
{
	lx_emul_trace(__func__);
	return NULL;
}


extern int devtmpfs_create_node(struct device * dev);
int devtmpfs_create_node(struct device * dev)
{
	lx_emul_trace(__func__);
	return 0;
}


extern int devtmpfs_delete_node(struct device * dev);
int devtmpfs_delete_node(struct device * dev)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/dmi.h>

const char * dmi_get_system_info(int field)
{
	lx_emul_trace(__func__);
	return NULL;
}


extern void dpm_sysfs_remove(struct device * dev);
void dpm_sysfs_remove(struct device * dev)
{
	lx_emul_trace(__func__);
}


struct dwc3;

extern void dwc3_debugfs_exit(struct dwc3 * dwc);
void dwc3_debugfs_exit(struct dwc3 * dwc)
{
	lx_emul_trace(__func__);
}


extern void dwc3_debugfs_init(struct dwc3 * dwc);
void dwc3_debugfs_init(struct dwc3 * dwc)
{
	lx_emul_trace(__func__);
}


extern int idle_cpu(int cpu);
int idle_cpu(int cpu)
{
	return 1;
}


#include <linux/mm.h>

DEFINE_STATIC_KEY_FALSE(init_on_alloc);
DEFINE_STATIC_KEY_FALSE(init_on_free);


#include <linux/ioport.h>

int insert_resource(struct resource * parent,struct resource * new)
{
	lx_emul_trace(__func__);
	return 0;
}


extern void irq_pm_install_action(struct irq_desc * desc,struct irqaction * action);
void irq_pm_install_action(struct irq_desc * desc,struct irqaction * action)
{
	lx_emul_trace(__func__);
}


#include <linux/mm.h>

bool is_vmalloc_addr(const void * x)
{
	lx_emul_trace(__func__);
	return false;
}


#include <linux/kernfs.h>

void kernfs_put(struct kernfs_node * kn)
{
	lx_emul_trace(__func__);
}


#include <linux/clk/clk-conf.h>

int of_clk_set_defaults(struct device_node * node,bool clk_supplier)
{
	static unsigned cnt = 0;
	if (cnt++ < 1) return -EPROBE_DEFER;

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


#include <linux/pm_runtime.h>

void pm_runtime_allow(struct device * dev)
{
	lx_emul_trace(__func__);
}


#include <linux/pm_runtime.h>

void pm_runtime_enable(struct device * dev)
{
	lx_emul_trace(__func__);
}


#include <linux/pm_runtime.h>

void pm_runtime_forbid(struct device * dev)
{
	lx_emul_trace(__func__);
}


#include <linux/pm_runtime.h>

void pm_runtime_no_callbacks(struct device * dev)
{
	lx_emul_trace(__func__);
}


#include <linux/pm_runtime.h>

void pm_runtime_set_autosuspend_delay(struct device * dev,int delay)
{
	lx_emul_trace(__func__);
}


extern void rcu_irq_enter(void);
void rcu_irq_enter(void)
{
	lx_emul_trace(__func__);
}


extern void rcu_irq_exit(void);
void rcu_irq_exit(void)
{
	lx_emul_trace(__func__);
}


extern void rcu_softirq_qs(void);
void rcu_softirq_qs(void)
{
	lx_emul_trace(__func__);
}


#include <linux/fs.h>

int register_chrdev_region(dev_t from,unsigned count,const char * name)
{
	lx_emul_trace(__func__);
	return 0;
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


#include <linux/regulator/consumer.h>

int regulator_enable(struct regulator * regulator)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/regulator/consumer.h>

struct regulator * regulator_get_optional(struct device * dev,const char * id)
{
	lx_emul_trace(__func__);
	return NULL;
}


#include <linux/reset.h>

int reset_control_assert(struct reset_control * rstc)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/reset.h>

int reset_control_deassert(struct reset_control * rstc)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/sysfs.h>

int sysfs_add_file_to_group(struct kobject * kobj,const struct attribute * attr,const char * group)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/sysfs.h>

int sysfs_create_group(struct kobject * kobj,const struct attribute_group * grp)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/sysfs.h>

int sysfs_merge_group(struct kobject * kobj,const struct attribute_group * grp)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/sysfs.h>

void sysfs_remove_bin_file(struct kobject * kobj,const struct bin_attribute * attr)
{
	lx_emul_trace(__func__);
}


#include <linux/sysfs.h>

void sysfs_remove_dir(struct kobject * kobj)
{
	lx_emul_trace(__func__);
}


#include <linux/sysfs.h>

void sysfs_remove_file_from_group(struct kobject * kobj,const struct attribute * attr,const char * group)
{
	lx_emul_trace(__func__);
}


#include <linux/sysfs.h>

void sysfs_remove_file_ns(struct kobject * kobj,const struct attribute * attr,const void * ns)
{
	lx_emul_trace(__func__);
}


#include <linux/sysfs.h>

void sysfs_remove_groups(struct kobject * kobj,const struct attribute_group ** groups)
{
	lx_emul_trace(__func__);
}


#include <linux/sysfs.h>

void sysfs_remove_link(struct kobject * kobj,const char * name)
{
	lx_emul_trace(__func__);
}


#include <linux/sysfs.h>

void sysfs_unmerge_group(struct kobject * kobj,const struct attribute_group * grp)
{
	lx_emul_trace(__func__);
}


#include <linux/sched/wake_q.h>

void wake_q_add(struct wake_q_head * head,struct task_struct * task)
{
	lx_emul_trace(__func__);
	wake_up_process(task);
}


#include <linux/sched/wake_q.h>

void wake_up_q(struct wake_q_head * head)
{
	lx_emul_trace(__func__);
}
