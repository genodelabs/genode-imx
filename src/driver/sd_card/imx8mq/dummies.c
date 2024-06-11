/*
 * \brief  Dummy definitions of Linux Kernel functions - handled manually
 * \author Stefan Kalkowski
 * \date   2021-03-31
 */

/*
 * Copyright (C) 2021 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#include <lx_emul.h>
#include <lx_emul/alloc.h>

unsigned long __must_check __arch_copy_from_user(void *to, const void __user *from, unsigned long n);
unsigned long __must_check __arch_copy_from_user(void *to, const void __user *from, unsigned long n)
{
	lx_emul_trace_and_stop(__func__);
}


unsigned long __must_check __arch_copy_to_user(void __user *to, const void *from, unsigned long n);
unsigned long __must_check __arch_copy_to_user(void __user *to, const void *from, unsigned long n)
{
	lx_emul_trace_and_stop(__func__);
}


#include <asm-generic/sections.h>

char __start_rodata[] = {};
char __end_rodata[]   = {};


#include <linux/of_reserved_mem.h>
#include <linux/mod_devicetable.h>

const struct of_device_id __reservedmem_of_table[] = {};


#include <linux/kernel_stat.h>

void account_process_tick(struct task_struct * p,int user_tick)
{
	lx_emul_trace(__func__);
}


#include <linux/tracepoint-defs.h>

const struct trace_print_flags vmaflag_names[]  = { {0,NULL}};


#include <linux/tracepoint-defs.h>

const struct trace_print_flags pageflag_names[]  = { {0,NULL}};


#include <linux/tracepoint-defs.h>

const struct trace_print_flags gfpflag_names[]  = { {0,NULL}};


#include <linux/ratelimit_types.h>

int ___ratelimit(struct ratelimit_state * rs,const char * func)
{
	lx_emul_trace(__func__);
	return 0;
}


struct bio;
extern void __bio_crypt_advance(struct bio *bio, unsigned int bytes);
void __bio_crypt_advance(struct bio *bio, unsigned int bytes)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/cpuhotplug.h>

int __cpuhp_state_add_instance(enum cpuhp_state state,struct hlist_node * node,bool invoke)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/cpuhotplug.h>

int __cpuhp_state_remove_instance(enum cpuhp_state state,struct hlist_node * node,bool invoke)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/threads.h>

unsigned long __per_cpu_offset[NR_CPUS] = { 0UL };


#include <linux/pm_runtime.h>

void __pm_runtime_disable(struct device * dev,bool check_resume)
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


#include <linux/pm_runtime.h>

void __pm_runtime_use_autosuspend(struct device * dev,bool use)
{
	lx_emul_trace(__func__);
}


#include <linux/random.h>

void add_interrupt_randomness(int irq)
{
	lx_emul_trace(__func__);
}


#include <linux/dma-map-ops.h>

void arch_setup_dma_ops(struct device * dev,u64 dma_base,u64 size,const struct iommu_ops * iommu,bool coherent)
{
	lx_emul_trace(__func__);
}


bool arm64_use_ng_mappings = false;
EXPORT_SYMBOL(arm64_use_ng_mappings);


#include <linux/backing-dev.h>

struct backing_dev_info * bdi_alloc(int node_id)
{
	struct backing_dev_info * ret = kzalloc(sizeof(struct backing_dev_info), GFP_KERNEL);
	return ret;
}


#include <linux/backing-dev.h>

int bdi_register(struct backing_dev_info * bdi,const char * fmt,...)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/backing-dev.h>

void bdi_set_owner(struct backing_dev_info * bdi,struct device * owner)
{
	lx_emul_trace(__func__);
}


#include <linux/backing-dev.h>

void bdi_unregister(struct backing_dev_info * bdi)
{
	lx_emul_trace(__func__);
}


#include <../block/blk-stat.h>
struct blk_queue_stats { int dummy; };

struct blk_queue_stats * blk_alloc_queue_stats(void)
{
	static struct blk_queue_stats ret;
	lx_emul_trace(__func__);
	return &ret;
}


#include <linux/blk-cgroup.h>

void blk_cgroup_bio_start(struct bio * bio)
{
	lx_emul_trace(__func__);
}


struct request_queue;
extern void blk_mq_sysfs_init(struct request_queue * q);
void blk_mq_sysfs_init(struct request_queue * q)
{
	lx_emul_trace(__func__);
}


#include <../block/blk.h>
struct kobj_type blk_queue_ktype;


extern struct blk_stat_callback * blk_stat_alloc_callback(void (* timer_fn)(struct blk_stat_callback *),int (* bucket_fn)(const struct request *),unsigned int buckets,void * data);
struct blk_stat_callback * blk_stat_alloc_callback(void (* timer_fn)(struct blk_stat_callback *),int (* bucket_fn)(const struct request *),unsigned int buckets,void * data)
{
	static struct blk_stat_callback ret;
	lx_emul_trace(__func__);
	return &ret;
}


#include <linux/cdev.h>

int cdev_device_add(struct cdev * cdev,struct device * dev)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/cdev.h>

void cdev_init(struct cdev * cdev,const struct file_operations * fops)
{
	lx_emul_trace(__func__);
}


#include <linux/gpio/consumer.h>

struct gpio_desc * __must_check devm_gpiod_get_index(struct device * dev,const char * con_id,unsigned int idx,enum gpiod_flags flags)
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


extern void dpm_sysfs_remove(struct device * dev);
void dpm_sysfs_remove(struct device * dev)
{
	lx_emul_trace(__func__);
}


#include <linux/gpio/consumer.h>

struct gpio_desc * __must_check gpiod_get_optional(struct device * dev,const char * con_id,enum gpiod_flags flags)
{
	lx_emul_trace(__func__);
	return NULL;
}


#include <linux/gpio/consumer.h>

int gpiod_set_debounce(struct gpio_desc * desc,unsigned int debounce)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/kernfs.h>

void kernfs_put(struct kernfs_node * kn)
{
	lx_emul_trace(__func__);
}


#include <linux/kobject.h>

int kobject_uevent_env(struct kobject * kobj,enum kobject_action action,char * envp_ext[])
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/leds.h>

int led_classdev_register_ext(struct device * parent,struct led_classdev * led_cdev,struct led_init_data * init_data)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/leds.h>

void led_trigger_event(struct led_trigger * trig,enum led_brightness brightness)
{
	lx_emul_trace(__func__);
}


#include <linux/leds.h>

void led_trigger_register_simple(const char * name,struct led_trigger ** tp)
{
	lx_emul_trace(__func__);
}


#include <linux/clk/clk-conf.h>

int of_clk_set_defaults(struct device_node * node,bool clk_supplier)
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


#include <linux/pinctrl/devinfo.h>

int pinctrl_init_done(struct device * dev)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/pinctrl/consumer.h>

struct pinctrl_state * pinctrl_lookup_state(struct pinctrl * p,const char * name)
{
	lx_emul_trace(__func__);
	return NULL;
}


#include <linux/pinctrl/consumer.h>

int pinctrl_select_default_state(struct device * dev)
{
	lx_emul_trace(__func__);
	return 0;
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


#include <linux/pm_runtime.h>

void pm_runtime_set_memalloc_noio(struct device * dev,bool enable)
{
	lx_emul_trace(__func__);
}


#include <linux/prandom.h>

u32 prandom_u32(void)
{
	lx_emul_trace(__func__);
	return (u32) 0xdeadbeef;
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


extern void synchronize_rcu_expedited(void);
void synchronize_rcu_expedited(void)
{
	lx_emul_trace_and_stop(__func__);
}


void synchronize_srcu(struct srcu_struct * ssp)
{
	lx_emul_trace(__func__);
}


#include <linux/sysfs.h>

int sysfs_create_files(struct kobject * kobj,const struct attribute * const * ptr)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/sysfs.h>

int sysfs_create_link_nowarn(struct kobject * kobj,struct kobject * target,const char * name)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/sysfs.h>

void sysfs_delete_link(struct kobject * kobj,struct kobject * targ,const char * name)
{
	lx_emul_trace(__func__);
}


#include <linux/sysfs.h>

void sysfs_remove_dir(struct kobject * kobj)
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

void sysfs_remove_files(struct kobject * kobj,const struct attribute * const * ptr)
{
	lx_emul_trace(__func__);
}


#include <linux/sysfs.h>

void sysfs_remove_link(struct kobject * kobj,const char * name)
{
	lx_emul_trace(__func__);
}



#include <linux/skbuff.h>

void skb_init()
{
	lx_emul_trace(__func__);
}


struct blk_mq_hw_ctx;
extern void blk_mq_hctx_kobj_init(struct blk_mq_hw_ctx * hctx);
void blk_mq_hctx_kobj_init(struct blk_mq_hw_ctx * hctx)
{
	lx_emul_trace(__func__);
}


u64 vabits_actual;
EXPORT_SYMBOL(vabits_actual);


#include <linux/pci.h>

unsigned long pci_address_to_pio(phys_addr_t addr)
{
    lx_emul_trace(__func__);
	return 0;
}


#include <linux/blkdev.h>

void blkdev_put(struct block_device * bdev,fmode_t mode)
{
	lx_emul_trace(__func__);
}


#include <linux/cpuhotplug.h>

int __cpuhp_setup_state(enum cpuhp_state state,const char * name,bool invoke,int (* startup)(unsigned int cpu),int (* teardown)(unsigned int cpu),bool multi_instance)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/posix-timers.h>

void __init posix_cputimers_init_work(void)
{
	lx_emul_trace(__func__);
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

struct kernfs_node * kernfs_find_and_get_ns(struct kernfs_node * parent,const char * name,const void * ns)
{
	lx_emul_trace(__func__);
	return NULL;
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


extern void pm_runtime_init(struct device * dev);
void pm_runtime_init(struct device * dev)
{
	lx_emul_trace(__func__);
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


extern int dpm_sysfs_add(struct device * dev);
int dpm_sysfs_add(struct device * dev)
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


#include <linux/pm_runtime.h>

int __pm_runtime_resume(struct device * dev,int rpmflags)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/pm_runtime.h>

int __pm_runtime_idle(struct device * dev,int rpmflags)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/kernel.h>

bool parse_option_str(const char * str,const char * option)
{
	lx_emul_trace(__func__);
	return false;
}


#include <linux/pm_runtime.h>

void pm_runtime_get_suppliers(struct device * dev)
{
	lx_emul_trace(__func__);
}


#include <linux/pm_runtime.h>

int pm_runtime_barrier(struct device * dev)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/pm_domain.h>

int dev_pm_domain_attach(struct device * dev,bool power_on)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/pm_runtime.h>

void pm_runtime_put_suppliers(struct device * dev)
{
	lx_emul_trace(__func__);
}


#include <linux/logic_pio.h>

struct logic_pio_hwaddr * find_io_range_by_fwnode(struct fwnode_handle * fwnode)
{
	lx_emul_trace(__func__);
	return NULL;
}


#include <linux/sysctl.h>

struct ctl_table_header * register_sysctl(const char * path,struct ctl_table * table)
{
	lx_emul_trace(__func__);
	return NULL;
}


#include <linux/syscore_ops.h>

void register_syscore_ops(struct syscore_ops * ops)
{
	lx_emul_trace(__func__);
}


#include <linux/proc_fs.h>

struct proc_dir_entry * proc_create_seq_private(const char * name,umode_t mode,struct proc_dir_entry * parent,const struct seq_operations * ops,unsigned int state_size,void * data)
{
	lx_emul_trace(__func__);
	return NULL;
}


#include <linux/sysctl.h>

void __init __register_sysctl_init(const char * path,struct ctl_table * table,const char * table_name)
{
	lx_emul_trace(__func__);
}


#include <linux/sysfs.h>

int sysfs_add_file_to_group(struct kobject * kobj,const struct attribute * attr,const char * group)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/pm_runtime.h>

void pm_runtime_drop_link(struct device_link * link)
{
	lx_emul_trace(__func__);
}


extern void pm_runtime_remove(struct device * dev);
void pm_runtime_remove(struct device * dev)
{
	lx_emul_trace(__func__);
}


extern void software_node_notify_remove(struct device * dev);
void software_node_notify_remove(struct device * dev)
{
	lx_emul_trace(__func__);
}


#include <linux/pm_runtime.h>

void pm_runtime_release_supplier(struct device_link * link)
{
	lx_emul_trace(__func__);
}


#include <linux/rcupdate.h>

void rcu_sched_clock_irq(int user)
{
	lx_emul_trace(__func__);
}


#include <linux/posix-timers.h>

void run_posix_cpu_timers(void)
{
	lx_emul_trace(__func__);
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


#include <linux/random.h>

void add_device_randomness(const void * buf,size_t len)
{
	lx_emul_trace(__func__);
}


#include <linux/blkdev.h>

void __cold rand_initialize_disk(struct gendisk * disk)
{
	lx_emul_trace(__func__);
}


extern void pm_runtime_reinit(struct device * dev);
void pm_runtime_reinit(struct device * dev)
{
	lx_emul_trace(__func__);
}


#include <linux/pinctrl/consumer.h>

int pinctrl_select_state(struct pinctrl * p,struct pinctrl_state * state)
{
	lx_emul_trace(__func__);
	return 0;
}

