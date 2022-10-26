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


#include <linux/reset.h>

struct reset_control * __reset_control_get(struct device * dev,const char * id,int index,bool shared,bool optional,bool acquired)
{
	lx_emul_trace(__func__);
	return NULL;
}


#include <linux/skbuff.h>

void __skb_get_hash(struct sk_buff * skb)
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


#include <linux/filter.h>
#include <linux/jump_label.h> /* for DEFINE_STATIC_KEY_FALSE */

void bpf_prog_change_xdp(struct bpf_prog *prev_prog, struct bpf_prog *prog)
{
	lx_emul_trace_and_stop(__func__);
}

DEFINE_STATIC_KEY_FALSE(bpf_stats_enabled_key);


#include <linux/netdevice.h>

int __init dev_proc_init(void)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/pm_wakeup.h>

int device_set_wakeup_enable(struct device * dev,bool enable)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/regulator/driver.h>

struct regulator_dev * devm_regulator_register(struct device * dev,const struct regulator_desc * regulator_desc,const struct regulator_config * config)
{
	static struct regulator_dev rdev;
	lx_emul_trace(__func__);
	return &rdev;
}


#include <linux/stringhash.h>

unsigned int full_name_hash(const void * salt,const char * name,unsigned int len)
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


#include <linux/pm_wakeup.h>

int device_init_wakeup(struct device * dev,bool enable)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/gpio.h>

int devm_gpio_request_one(struct device * dev,unsigned gpio,unsigned long flags,const char * label)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/regulator/consumer.h>
struct regulator { unsigned dummy; };

struct regulator * devm_regulator_get_optional(struct device * dev,const char * id)
{
	static struct regulator ret;
	lx_emul_trace(__func__);
	return &ret;
}


extern void dpm_sysfs_remove(struct device * dev);
void dpm_sysfs_remove(struct device * dev)
{
	lx_emul_trace(__func__);
}


#include <linux/gfp.h>

void free_pages(unsigned long addr,unsigned int order)
{
	lx_emul_trace(__func__);
}


#include <linux/kernel.h>

char * get_options(const char * str,int nints,int * ints)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/gpio/consumer.h>

struct gpio_desc { unsigned dummy; };
struct gpio_desc * gpio_to_desc(unsigned gpio)
{
	static struct gpio_desc ret;
	lx_emul_trace(__func__);
	return &ret;
}


#include <linux/gpio/consumer.h>

struct gpio_desc * __must_check gpiod_get_optional(struct device * dev,const char * con_id,enum gpiod_flags flags)
{
	lx_emul_trace(__func__);
	return NULL;
}


#include <linux/gpio/consumer.h>

void gpiod_set_raw_value_cansleep(struct gpio_desc * desc,int value)
{
	lx_emul_trace(__func__);
}


extern void irq_pm_install_action(struct irq_desc * desc,struct irqaction * action);
void irq_pm_install_action(struct irq_desc * desc,struct irqaction * action)
{
	lx_emul_trace(__func__);
}


#include <net/sock.h>

DEFINE_STATIC_KEY_FALSE(memalloc_socks_key);


int __init netdev_kobject_init(void);
int __init netdev_kobject_init(void)
{
	lx_emul_trace(__func__);
	return 0;
}


extern int netdev_register_kobject(struct net_device * ndev);
int netdev_register_kobject(struct net_device * ndev)
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


#include <linux/of_gpio.h>

int of_get_named_gpio_flags(struct device_node * np,const char * list_name,int index,enum of_gpio_flags * flags)
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

int pinctrl_pm_select_default_state(struct device * dev)
{
	lx_emul_trace(__func__);
	return  0;
}


#include <linux/pinctrl/consumer.h>

int pinctrl_pm_select_sleep_state(struct device * dev)
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


#include <linux/proc_ns.h>

int proc_alloc_inum(unsigned int * inum)
{
	*inum = 1; /* according to linux/proc_ns.h without CONFIG_PROC_FS */
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


#include <net/rtnetlink.h>

void rtnl_register(int protocol,int msgtype,rtnl_doit_func doit,rtnl_dumpit_func dumpit,unsigned int flags)
{
	lx_emul_trace(__func__);
}


#include <linux/rcutree.h>

void synchronize_rcu_expedited(void)
{
	lx_emul_trace(__func__);
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

void sysfs_remove_file_ns(struct kobject * kobj,const struct attribute * attr,const void * ns)
{
	lx_emul_trace(__func__);
}


#include <linux/sysfs.h>

void sysfs_remove_link(struct kobject * kobj,const char * name)
{
	lx_emul_trace(__func__);
}


#include <linux/wait_bit.h>

void __init wait_bit_init(void)
{
	lx_emul_trace(__func__);
}


/* All definitions of tracepoints related to BPF. */
#define CREATE_TRACE_POINTS
#include <linux/bpf_trace.h>

EXPORT_TRACEPOINT_SYMBOL_GPL(xdp_exception);
EXPORT_TRACEPOINT_SYMBOL_GPL(xdp_bulk_tx);
