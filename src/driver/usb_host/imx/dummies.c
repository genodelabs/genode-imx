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

#include <asm-generic/sections.h>

char __start_rodata[] = {};
char __end_rodata[]   = {};


#include <linux/srcu.h>

void synchronize_srcu(struct srcu_struct * ssp)
{
	lx_emul_trace(__func__);
}


#include <asm/irq_regs.h>

struct pt_regs * __irq_regs = NULL;


#include <linux/of_reserved_mem.h>
#include <linux/mod_devicetable.h>

const struct of_device_id __reservedmem_of_table[] = {};


#include <linux/kernel_stat.h>

void account_process_tick(struct task_struct * p,int user_tick)
{
	lx_emul_trace(__func__);
}


extern void arch_trigger_cpumask_backtrace(const cpumask_t * mask, int exclude_cpu);
void arch_trigger_cpumask_backtrace(const cpumask_t * mask, int exclude_cpu)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/context_tracking_irq.h>

noinstr void ct_irq_enter(void)
{
	lx_emul_trace(__func__);
}


#include <linux/context_tracking_irq.h>

noinstr void ct_irq_exit(void)
{
	lx_emul_trace(__func__);
}


#include <linux/tracepoint-defs.h>

const struct trace_print_flags vmaflag_names[]  = { {0,NULL}};


#include <linux/tracepoint-defs.h>

const struct trace_print_flags gfpflag_names[]  = { {0,NULL}};


#include <linux/cpuhotplug.h>

int __cpuhp_setup_state(enum cpuhp_state state,const char * name,bool invoke,int (* startup)(unsigned int cpu),int (* teardown)(unsigned int cpu),bool multi_instance)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/timekeeper_internal.h>

void update_vsyscall(struct timekeeper * tk)
{
	lx_emul_trace(__func__);
}


#include <net/net_namespace.h>

void __init net_ns_init(void)
{
	lx_emul_trace(__func__);
}


#include <linux/sched/signal.h>

void ignore_signals(struct task_struct * t)
{
	lx_emul_trace(__func__);
}


#include <linux/sysfs.h>

int sysfs_create_dir_ns(struct kobject * kobj,const void * ns)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/sysfs.h>

int sysfs_create_groups(struct kobject * kobj,const struct attribute_group ** groups)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/kernfs.h>

void kernfs_get(struct kernfs_node * kn)
{
	lx_emul_trace(__func__);
}


#include <linux/kobject.h>

int kobject_uevent(struct kobject * kobj,enum kobject_action action)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/kernfs.h>

void kernfs_notify(struct kernfs_node * kn)
{
	lx_emul_trace(__func__);
}


#include <linux/sysfs.h>

int sysfs_create_bin_file(struct kobject * kobj,const struct bin_attribute * attr)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/proc_fs.h>

struct proc_dir_entry * proc_symlink(const char * name,struct proc_dir_entry * parent,const char * dest)
{
	lx_emul_trace(__func__);
	return NULL;
}


extern void software_node_notify(struct device * dev);
void software_node_notify(struct device * dev)
{
	lx_emul_trace(__func__);
}


#include <linux/sysfs.h>

int sysfs_create_file_ns(struct kobject * kobj,const struct attribute * attr,const void * ns)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/sysfs.h>

int sysfs_create_link(struct kobject * kobj,struct kobject * target,const char * name)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/logic_pio.h>

struct logic_pio_hwaddr * find_io_range_by_fwnode(struct fwnode_handle * fwnode)
{
	lx_emul_trace(__func__);
	return NULL;
}


#include <linux/kernel.h>

bool parse_option_str(const char * str,const char * option)
{
	lx_emul_trace(__func__);
	return false;
}


#include <linux/fs.h>

int __register_chrdev(unsigned int major,unsigned int baseminor,unsigned int count,const char * name,const struct file_operations * fops)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/fs.h>

int register_chrdev_region(dev_t from,unsigned count,const char * name)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/cdev.h>

int cdev_add(struct cdev * p,dev_t dev,unsigned count)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/pinctrl/devinfo.h>

int pinctrl_bind_pins(struct device * dev)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/dma-map-ops.h>

void arch_setup_dma_ops(struct device * dev,u64 dma_base,u64 size,const struct iommu_ops * iommu,bool coherent)
{
	lx_emul_trace(__func__);
}


#include <linux/clk/clk-conf.h>

int of_clk_set_defaults(struct device_node * node,bool clk_supplier)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/gpio/consumer.h>

struct gpio_desc * __must_check devm_gpiod_get_optional(struct device * dev,const char * con_id,enum gpiod_flags flags)
{
	lx_emul_trace(__func__);
	return NULL;
}


#include <linux/regulator/consumer.h>

struct regulator * devm_regulator_get(struct device * dev,const char * id)
{
	lx_emul_trace(__func__);
	return NULL;
}


#include <linux/regulator/consumer.h>

struct regulator * devm_regulator_get_exclusive(struct device * dev,const char * id)
{
	lx_emul_trace(__func__);
	return NULL;
}


#include <linux/pinctrl/devinfo.h>

int pinctrl_init_done(struct device * dev)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/sysfs.h>

void sysfs_remove_file_ns(struct kobject * kobj,const struct attribute * attr,const void * ns)
{
	lx_emul_trace(__func__);
}


#include <linux/syscore_ops.h>

void register_syscore_ops(struct syscore_ops * ops)
{
	lx_emul_trace(__func__);
}


#include <linux/proc_fs.h>

struct proc_dir_entry { int dummy; };
struct proc_dir_entry * proc_create_seq_private(const char * name,umode_t mode,struct proc_dir_entry * parent,const struct seq_operations * ops,unsigned int state_size,void * data)
{
	static struct proc_dir_entry ret;
	lx_emul_trace(__func__);
	return &ret;
}


#include <linux/sysfs.h>

int sysfs_add_file_to_group(struct kobject * kobj,const struct attribute * attr,const char * group)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/sysctl.h>

void __init __register_sysctl_init(const char * path, struct ctl_table * table,
                                   const char * table_name, size_t table_size)
{
	lx_emul_trace(__func__);
}


#include <linux/sysfs.h>

void sysfs_remove_link(struct kobject * kobj,const char * name)
{
	lx_emul_trace(__func__);
}


#include <linux/sysfs.h>

void sysfs_delete_link(struct kobject * kobj,struct kobject * targ,const char * name)
{
	lx_emul_trace(__func__);
}


#include <linux/sysfs.h>

void sysfs_remove_groups(struct kobject * kobj,const struct attribute_group ** groups)
{
	lx_emul_trace(__func__);
}


extern void software_node_notify_remove(struct device * dev);
void software_node_notify_remove(struct device * dev)
{
	lx_emul_trace(__func__);
}


#include <linux/sysfs.h>

void sysfs_remove_dir(struct kobject * kobj)
{
	lx_emul_trace(__func__);
}


#include <linux/kernfs.h>

void kernfs_put(struct kernfs_node * kn)
{
	lx_emul_trace(__func__);
}


#include <linux/dma-map-ops.h>

void arch_teardown_dma_ops(struct device * dev)
{
	lx_emul_trace(__func__);
}


#include <linux/regulator/consumer.h>

struct regulator * devm_regulator_get_optional(struct device * dev,const char * id)
{
	lx_emul_trace(__func__);
	return NULL;
}


#include <linux/pinctrl/consumer.h>

struct pinctrl * devm_pinctrl_get(struct device * dev)
{
	lx_emul_trace(__func__);
	return NULL;
}


#include <linux/pinctrl/consumer.h>

struct pinctrl_state * pinctrl_lookup_state(struct pinctrl * p,const char * name)
{
	lx_emul_trace(__func__);
	return NULL;
}


#include <linux/ioport.h>

int insert_resource(struct resource * parent,struct resource * new)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/rcupdate.h>

void rcu_sched_clock_irq(int user)
{
	lx_emul_trace(__func__);
}


#include <linux/clk.h>

struct clk * of_clk_get(struct device_node * np,int index)
{
	lx_emul_trace(__func__);
	return NULL;
}


#include <linux/posix-timers.h>

void run_posix_cpu_timers(void)
{
	lx_emul_trace(__func__);
}


#include <linux/random.h>

void add_device_randomness(const void * buf,size_t len)
{
	lx_emul_trace(__func__);
}


extern int devtmpfs_create_node(struct device * dev);
int devtmpfs_create_node(struct device * dev)
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


extern void register_irq_proc(unsigned int irq,struct irq_desc * desc);
void register_irq_proc(unsigned int irq,struct irq_desc * desc)
{
	lx_emul_trace(__func__);
}


extern void register_handler_proc(unsigned int irq,struct irqaction * action);
void register_handler_proc(unsigned int irq,struct irqaction * action)
{
	lx_emul_trace(__func__);
}


#include <linux/mfd/syscon.h>

struct regmap * syscon_node_to_regmap(struct device_node * np)
{
	lx_emul_trace_and_stop(__func__);
}


struct regmap * syscon_regmap_lookup_by_phandle(struct device_node * np,const char * property)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/random.h>

void add_interrupt_randomness(int irq)
{
	lx_emul_trace(__func__);
}


#include <linux/mm.h>

bool is_vmalloc_addr(const void * x)
{
	lx_emul_trace(__func__);
	return false;
}


#include <linux/fs.h>

struct timespec64 current_time(struct inode * inode)
{
	struct timespec64 ret = { 0 };
	lx_emul_trace(__func__);
	return ret;
}


#include <linux/pid.h>

void put_pid(struct pid * pid)
{
	lx_emul_trace(__func__);
}


#include <linux/cred.h>

void __put_cred(struct cred * cred)
{
	lx_emul_trace(__func__);
}


#include <linux/sysfs.h>

void sysfs_remove_bin_file(struct kobject * kobj,const struct bin_attribute * attr)
{
	lx_emul_trace(__func__);
}


extern int devtmpfs_delete_node(struct device * dev);
int devtmpfs_delete_node(struct device * dev)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/skbuff.h>

void skb_init()
{
	lx_emul_trace(__func__);
}


#include <linux/sysfs.h>

void sysfs_notify(struct kobject * kobj,const char * dir,const char * attr)
{
	lx_emul_trace(__func__);
}


#include <linux/kobject.h>

int kobject_uevent_env(struct kobject * kobj,enum kobject_action action,char * envp_ext[])
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/cdev.h>

void cdev_init(struct cdev * cdev, const struct file_operations * fops)
{
	lx_emul_trace(__func__);
}
