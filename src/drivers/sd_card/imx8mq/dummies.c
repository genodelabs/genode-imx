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


#include <linux/blk-crypto.h>

int __bio_crypt_clone(struct bio *dst, struct bio *src, gfp_t gfp_mask)
{
	lx_emul_trace_and_stop(__func__);
}


extern void __bio_crypt_free_ctx(struct bio *bio);
void __bio_crypt_free_ctx(struct bio *bio)
{
	lx_emul_trace_and_stop(__func__);
}


extern bool __blk_crypto_bio_prep(struct bio **bio_ptr);
bool __blk_crypto_bio_prep(struct bio **bio_ptr)
{
	lx_emul_trace_and_stop(__func__);
}


extern void __blk_crypto_free_request(struct request *rq);
void __blk_crypto_free_request(struct request *rq)
{
	lx_emul_trace_and_stop(__func__);
}


extern blk_status_t __blk_crypto_init_request(struct request *rq);
blk_status_t __blk_crypto_init_request(struct request *rq)
{
	lx_emul_trace_and_stop(__func__);
}


extern int __blk_crypto_rq_bio_prep(struct request *rq, struct bio *bio, gfp_t gfp_mask);
int __blk_crypto_rq_bio_prep(struct request *rq, struct bio *bio, gfp_t gfp_mask)
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


#include <linux/genhd.h>

int __invalidate_device(struct block_device * bdev,bool kill_dirty)
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


#include <linux/blkdev.h>

void bdput(struct block_device * bdev)
{
	lx_emul_trace(__func__);
}


#include <linux/bio.h>

void bio_associate_blkg(struct bio * bio)
{
	lx_emul_trace(__func__);
}


#include <linux/bio.h>

void bio_clone_blkg_association(struct bio * dst,struct bio * src)
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


extern void blk_mq_debugfs_unregister_hctx(struct blk_mq_hw_ctx * hctx);
void blk_mq_debugfs_unregister_hctx(struct blk_mq_hw_ctx * hctx)
{
	lx_emul_trace(__func__);
}


extern void blk_mq_debugfs_unregister_queue_rqos(struct request_queue * q);
void blk_mq_debugfs_unregister_queue_rqos(struct request_queue * q)
{
	lx_emul_trace(__func__);
}


extern void blk_mq_hctx_kobj_init(struct blk_mq_hw_ctx * hctx);
void blk_mq_hctx_kobj_init(struct blk_mq_hw_ctx * hctx)
{
	lx_emul_trace(__func__);
}


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


extern bool blk_throtl_bio(struct bio *bio);
bool blk_throtl_bio(struct bio *bio)
{
	return false;
}


int blkcg_init_queue(struct request_queue * q)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/blkdev.h>

void blkdev_put(struct block_device * bdev,fmode_t mode)
{
	lx_emul_trace(__func__);
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


#include <linux/blkdev.h>

int fsync_bdev(struct block_device * bdev)
{
	lx_emul_trace(__func__);
	return 0;
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


extern void irq_pm_install_action(struct irq_desc * desc,struct irqaction * action);
void irq_pm_install_action(struct irq_desc * desc,struct irqaction * action)
{
	lx_emul_trace(__func__);
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


#include <../drivers/mmc/core/card.h>

void mmc_add_card_debugfs(struct mmc_card * card)
{
	lx_emul_trace(__func__);
}


void mmc_add_host_debugfs(struct mmc_host * host)
{
	lx_emul_trace(__func__);
}


void mmc_remove_card_debugfs(struct mmc_card * card)
{
	lx_emul_trace(__func__);
}


void mmc_remove_host_debugfs(struct mmc_host * host)
{
	lx_emul_trace(__func__);
}


#include <linux/clk/clk-conf.h>

int of_clk_set_defaults(struct device_node * node,bool clk_supplier)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/of_iommu.h>

const struct iommu_ops * of_iommu_configure(struct device * dev,struct device_node * master_np,const u32 * id)
{
	lx_emul_trace(__func__);
	return NULL;
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


#include <linux/genhd.h>

void rand_initialize_disk(struct gendisk * disk)
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


#include <linux/suspend.h>

int register_pm_notifier(struct notifier_block * nb)
{
	lx_emul_trace(__func__);
	return 0;
}


extern void synchronize_rcu_expedited(void);
void synchronize_rcu_expedited(void)
{
	lx_emul_trace_and_stop(__func__);
}


void synchronize_srcu(struct srcu_struct * ssp)
{
	lx_emul_trace_and_stop(__func__);
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


#include <linux/vmstat.h>

DEFINE_PER_CPU(struct vm_event_state, vm_event_states) = {{0}};
EXPORT_PER_CPU_SYMBOL(vm_event_states);


#include <linux/pm_wakeup.h>

struct wakeup_source * wakeup_source_register(struct device * dev,const char * name)
{
	lx_emul_trace(__func__);
	return NULL;
}


#include <linux/pm_wakeup.h>

void wakeup_source_unregister(struct wakeup_source * ws)
{
	lx_emul_trace(__func__);
}


#include <linux/nmi.h>

notrace void touch_softlockup_watchdog_sched(void)
{
	lx_emul_trace(__func__);
}


#include <linux/wait_bit.h>

void __init wait_bit_init(void)
{
	lx_emul_trace(__func__);
}



#include <linux/skbuff.h>

void skb_init()
{
	lx_emul_trace(__func__);
}
