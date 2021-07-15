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


unsigned long __must_check __arch_clear_user(void __user *to, unsigned long n);
unsigned long __must_check __arch_clear_user(void __user *to, unsigned long n)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/serial_core.h>

const struct earlycon_id __earlycon_table[] = { };


#include <linux/serial_core.h>

const struct earlycon_id __earlycon_table_end[] = { };


#include <linux/i2c.h>

LIST_HEAD(__i2c_board_list);
EXPORT_SYMBOL_GPL(__i2c_board_list);


#include <linux/i2c.h>

DECLARE_RWSEM(__i2c_board_lock);
EXPORT_SYMBOL_GPL(__i2c_board_lock);


#include <linux/i2c.h>

int __i2c_first_dynamic_bus_num;
EXPORT_SYMBOL_GPL(__i2c_first_dynamic_bus_num);


#include <asm-generic/percpu.h>

unsigned long __per_cpu_offset[NR_CPUS] = {};


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


#include <linux/fs.h>

int __register_chrdev(unsigned int major, unsigned int baseminor,unsigned int count,const char * name,const struct file_operations * fops)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/random.h>

void add_interrupt_randomness(int irq,int irq_flags)
{
	lx_emul_trace(__func__);
}


#include <linux/fs.h>

struct inode * alloc_anon_inode(struct super_block * s)
{
	return kmalloc(sizeof(struct inode), GFP_KERNEL);
}


#include <linux/dma-mapping.h>

void arch_setup_dma_ops(struct device * dev,u64 dma_base,u64 size,const struct iommu_ops * iommu,bool coherent)
{
	lx_emul_trace(__func__);
}


#include <linux/dma-mapping.h>

void arch_teardown_dma_ops(struct device * dev)
{
	lx_emul_trace(__func__);
}


bool arm64_use_ng_mappings = false;
EXPORT_SYMBOL(arm64_use_ng_mappings);


#include <linux/init.h>

char __initdata boot_command_line[] = { 0 };


#include <linux/rcupdate.h>

void call_rcu(struct rcu_head * head,rcu_callback_t func)
{
	lx_emul_trace(__func__);
}


#include <linux/capability.h>

bool capable(int cap)
{
	lx_emul_trace(__func__);
	return true;
}


#include <linux/printk.h>

int console_printk[] = { 0 };


#include <linux/pm_wakeirq.h>

void dev_pm_clear_wake_irq(struct device * dev)
{
	lx_emul_trace(__func__);
}


#include <linux/pm_wakeup.h>

int device_init_wakeup(struct device * dev,bool enable)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/gpio/consumer.h>
#include <uapi/linux/synclink.h>

struct gpio_desc * __must_check devm_gpiod_get(struct device * dev,const char * con_id,enum gpiod_flags flags)
{
	static struct gpio_desc gpiod;
	return &gpiod;
}


#include <linux/gpio/consumer.h>

struct gpio_desc * __must_check devm_gpiod_get_optional(struct device * dev,const char * con_id,enum gpiod_flags flags)
{
	lx_emul_trace(__func__);
	return NULL;
}


#include <linux/mux/consumer.h>
#include <linux/mux/driver.h>

struct mux_control * devm_mux_control_get(struct device * dev,const char * mux_name)
{
	static struct mux_control ret;
	lx_emul_trace(__func__);
	return &ret;
}


#include <linux/backlight.h>

struct backlight_device *devm_of_find_backlight(struct device *dev)
{
	lx_emul_trace(__func__);
	return NULL;
}


#include <linux/regulator/consumer.h>

int devm_regulator_bulk_get(struct device * dev,int num_consumers,struct regulator_bulk_data * consumers)
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


extern int devtmpfs_create_node(struct device * dev);
int devtmpfs_create_node(struct device * dev)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/atomic.h>
#include <linux/dma-fence.h>

u64 dma_fence_context_alloc(unsigned num)
{
	static atomic64_t dma_fence_context_counter = ATOMIC64_INIT(1);
	WARN_ON(!num);
	return atomic64_add_return(num, &dma_fence_context_counter) - num;
}


#include <linux/dma-resv.h>

void dma_resv_init(struct dma_resv * obj)
{
	lx_emul_trace(__func__);
}


#include <linux/dma-mapping.h>

int dma_supported(struct device *dev, u64 mask)
{
	return 1;
}


#include <linux/fb.h>

int fb_get_options(const char * name,char ** option)
{
	*option = "";
	return 0;
}


#include <linux/gpio/consumer.h>

void gpiod_set_value_cansleep(struct gpio_desc * desc,int value)
{
	lx_emul_trace(__func__);
}


#include <linux/utsname.h>
#include <linux/user_namespace.h>

struct user_namespace init_user_ns;


#include <linux/fs.h>

void iput(struct inode * inode)
{
	kfree(inode);
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


#include <linux/mm.h>

bool is_vmalloc_addr(const void * x)
{
	lx_emul_trace(__func__);
	return false;
}


#include <linux/kobject.h>

struct kobject *kernel_kobj;


#include <linux/kernfs.h>

void kernfs_put(struct kernfs_node * kn) { }


#include <linux/kobject.h>

int kobject_uevent_env(struct kobject * kobj,enum kobject_action action,char * envp_ext[])
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/mux/consumer.h>

int mux_control_try_select(struct mux_control * mux,unsigned int state)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/clk/clk-conf.h>

int of_clk_set_defaults(struct device_node * node,bool clk_supplier)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/of_iommu.h>

const struct iommu_ops * of_iommu_configure(struct device * dev,
                                            struct device_node * master_np,
                                            const u32 *id)
{
	static struct iommu_ops ops;
	lx_emul_trace(__func__);
	return &ops;
}


#include <linux/kernel.h>

int oops_in_progress = 0;		/* If set, an oops, panic(), BUG() or die() is in progress */


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

void pm_runtime_no_callbacks(struct device * dev)
{
	lx_emul_trace(__func__);
}


#include <linux/pm_runtime.h>

void pm_runtime_set_autosuspend_delay(struct device * dev,int delay)
{
	lx_emul_trace(__func__);
}


#include <linux/rcutree.h>

void rcu_irq_enter_irqson(void)
{
	lx_emul_trace(__func__);
}


#include <linux/rcutree.h>

void rcu_irq_exit_irqson(void)
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


#include <linux/sysrq.h>

int register_sysrq_key(int key, const struct sysrq_key_op * op_p)
{
	lx_emul_trace(__func__);
	return 0;
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


#include <linux/sched.h>

void sched_set_fifo(struct task_struct * p)
{
	lx_emul_trace(__func__);
}


#include <linux/shmem_fs.h>

struct file * shmem_file_setup(const char * name,loff_t size,unsigned long flags)
{
	static struct file file;
	lx_emul_trace(__func__);
	return &file;
}


#include <linux/fs.h>
#include <linux/mount.h>

int simple_pin_fs(struct file_system_type * type, struct vfsmount ** mount, int * count)
{
	*mount = kmalloc(sizeof(struct vfsmount), GFP_KERNEL);
	return 0;
}


#include <linux/fs.h>

void simple_release_fs(struct vfsmount ** mount,int * count)
{
	kfree(*mount);
}


#include <linux/sys_soc.h>

const struct soc_device_attribute * soc_device_match(const struct soc_device_attribute * matches)
{
	if (!matches) { return NULL; }

	for (; matches->machine && matches->family &&
	       matches->revision && matches->soc_id; matches++) {
		if (strcmp(matches->soc_id, "i.MX8MQ") == 0) { return matches; }
	}

	return NULL;
}


#include <linux/sysfs.h>

void sysfs_remove_file_ns(struct kobject * kobj,const struct attribute * attr,const void * ns)
{
	lx_emul_trace(__func__);
}


#include <linux/sysfs.h>

void sysfs_remove_link(struct kobject * kobj,const char * name) { }


extern void unregister_handler_proc(unsigned int irq,struct irqaction * action);
void unregister_handler_proc(unsigned int irq,struct irqaction * action)
{
	lx_emul_trace(__func__);
}
