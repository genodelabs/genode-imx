/*
 * \brief  Dummy definitions of Linux Kernel functions
 * \author Automatically generated file - do no edit
 * \date   2024-09-11
 */

#include <lx_emul.h>


#include <linux/cpumask.h>

struct cpumask __cpu_active_mask;


#include <linux/serial_core.h>

const struct earlycon_id __earlycon_table[] = {};


#include <linux/serial_core.h>

const struct earlycon_id __earlycon_table_end[] = {};


#include <linux/pagemap.h>

void __folio_lock(struct folio * folio)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/printk.h>

void __printk_safe_enter(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/printk.h>

void __printk_safe_exit(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/fs.h>

void __remove_inode_hash(struct inode * inode)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/mm.h>

void __show_mem(unsigned int filter,nodemask_t * nodemask,int max_zone_idx)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/vmalloc.h>

void * __vmalloc_node_range(unsigned long size,unsigned long align,unsigned long start,unsigned long end,gfp_t gfp_mask,pgprot_t prot,unsigned long vm_flags,int node,const void * caller)
{
	lx_emul_trace_and_stop(__func__);
}


extern noinline unsigned int _parse_integer(const char * s,unsigned int base,unsigned long long * p);
noinline unsigned int _parse_integer(const char * s,unsigned int base,unsigned long long * p)
{
	lx_emul_trace_and_stop(__func__);
}


extern noinline const char * _parse_integer_fixup_radix(const char * s,unsigned int * base);
noinline const char * _parse_integer_fixup_radix(const char * s,unsigned int * base)
{
	lx_emul_trace_and_stop(__func__);
}


extern noinline unsigned int _parse_integer_limit(const char * s,unsigned int base,unsigned long long * p,size_t max_chars);
noinline unsigned int _parse_integer_limit(const char * s,unsigned int base,unsigned long long * p,size_t max_chars)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/printk.h>

int _printk_deferred(const char * fmt,...)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/mm.h>

atomic_long_t _totalram_pages;


#include <linux/random.h>

void __init add_bootloader_randomness(const void * buf,size_t len)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kobject.h>

int add_uevent_var(struct kobj_uevent_env * env,const char * format,...)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/amba/bus.h>

int amba_device_add(struct amba_device * dev,struct resource * parent)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/amba/bus.h>

struct amba_device * amba_device_alloc(const char * name,resource_size_t base,size_t size)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/amba/bus.h>

void amba_device_put(struct amba_device * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/badblocks.h>

ssize_t badblocks_show(struct badblocks * bb,char * page,int unack)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/badblocks.h>

ssize_t badblocks_store(struct badblocks * bb,const char * page,size_t len,int unack)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/blkdev.h>

void bdev_mark_dead(struct block_device * bdev,bool surprise)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/backing-dev.h>

void bdi_put(struct backing_dev_info * bdi)
{
	lx_emul_trace_and_stop(__func__);
}


extern void blk_free_queue_stats(struct blk_queue_stats * stats);
void blk_free_queue_stats(struct blk_queue_stats * stats)
{
	lx_emul_trace_and_stop(__func__);
}


extern void blk_mq_sysfs_deinit(struct request_queue * q);
void blk_mq_sysfs_deinit(struct request_queue * q)
{
	lx_emul_trace_and_stop(__func__);
}


extern void blk_stat_add(struct request * rq,u64 now);
void blk_stat_add(struct request * rq,u64 now)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/init.h>

char __initdata boot_command_line[] = {};


#include <linux/kernel.h>

void bust_spinlocks(int yes)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/capability.h>

bool capable(int cap)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/cdev.h>

void cdev_device_del(struct cdev * cdev,struct device * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/srcu.h>

void cleanup_srcu_struct(struct srcu_struct * ssp)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/console.h>

void console_flush_on_panic(enum con_flush_mode mode)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/console.h>

void console_unblank(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/printk.h>

void console_verbose(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/cpumask.h>

unsigned int cpumask_any_and_distribute(const struct cpumask * src1p,const struct cpumask * src2p)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sched/topology.h>

bool cpus_share_cache(int this_cpu,int that_cpu)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pm_domain.h>

void dev_pm_domain_detach(struct device * dev,bool power_off)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pm_domain.h>

int dev_pm_genpd_set_performance_state(struct device * dev,unsigned int state)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/gpio/consumer.h>

struct gpio_desc * __must_check devm_gpiod_get(struct device * dev,const char * con_id,enum gpiod_flags flags)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/gpio/consumer.h>

struct gpio_descs * __must_check devm_gpiod_get_array(struct device * dev,const char * con_id,enum gpiod_flags flags)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/dma-map-ops.h>

bool dma_default_coherent;


#include <linux/dma-mapping.h>

unsigned long dma_get_merge_boundary(struct device * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/dma-mapping.h>

size_t dma_max_mapping_size(struct device * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/dma-mapping.h>

void dma_sync_sg_for_cpu(struct device * dev,struct scatterlist * sg,int nelems,enum dma_data_direction dir)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/dma-mapping.h>

void * dmam_alloc_attrs(struct device * dev,size_t size,dma_addr_t * dma_handle,gfp_t gfp,unsigned long attrs)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/dma-mapping.h>

void dmam_free_coherent(struct device * dev,size_t size,void * vaddr,dma_addr_t dma_handle)
{
	lx_emul_trace_and_stop(__func__);
}


#include <asm-generic/softirq_stack.h>

void do_softirq_own_stack(void)
{
	lx_emul_trace_and_stop(__func__);
}


extern void drop_partition(struct block_device * part);
void drop_partition(struct block_device * part)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/printk.h>

asmlinkage __visible void dump_stack(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/printk.h>

asmlinkage __visible void dump_stack_lvl(const char * log_lvl)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/reboot.h>

void emergency_restart(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/rcuwait.h>

void finish_rcuwait(struct rcuwait * w)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kobject.h>

struct kobject *firmware_kobj;


#include <linux/mmzone.h>

struct pglist_data * first_online_pgdat(void)
{
	lx_emul_trace_and_stop(__func__);
}


extern void flush_dcache_page(struct page * page);
void flush_dcache_page(struct page * page)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/mm.h>

bool folio_mark_dirty(struct folio * folio)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pagemap.h>

void folio_unlock(struct folio * folio)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kernel.h>

int get_option(char ** str,int * pint)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/gfp.h>

bool gfp_pfmemalloc_allowed(gfp_t gfp_mask)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/gpio/consumer.h>

int gpiod_cansleep(const struct gpio_desc * desc)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/gpio/consumer.h>

int gpiod_get_value(const struct gpio_desc * desc)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/gpio/consumer.h>

int gpiod_get_value_cansleep(const struct gpio_desc * desc)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/gpio/consumer.h>

int gpiod_is_active_low(const struct gpio_desc * desc)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/gpio/consumer.h>

void gpiod_put(struct gpio_desc * desc)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/gpio/consumer.h>

int gpiod_set_array_value_cansleep(unsigned int array_size,struct gpio_desc ** desc_array,struct gpio_array * array_info,unsigned long * value_bitmap)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/gpio/consumer.h>

int gpiod_set_consumer_name(struct gpio_desc * desc,const char * name)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/gpio/consumer.h>

void gpiod_set_value(struct gpio_desc * desc,int value)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/gpio/consumer.h>

void gpiod_set_value_cansleep(struct gpio_desc * desc,int value)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/gpio/consumer.h>

int gpiod_to_irq(const struct gpio_desc * desc)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/gpio/consumer.h>

void gpiod_toggle_active_low(struct gpio_desc * desc)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/uuid.h>

const u8 guid_index[16] = {};


#include <linux/capability.h>

bool has_capability_noaudit(struct task_struct * t,int cap)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/init.h>

bool initcall_debug;


#include <linux/ioport.h>

int insert_resource(struct resource * parent,struct resource * new)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sched.h>

void __sched io_schedule(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sched.h>

void io_schedule_finish(int token)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sched.h>

int io_schedule_prepare(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/ioport.h>

struct resource iomem_resource;


#include <linux/ioport.h>

struct resource ioport_resource;


#include <asm-generic/io.h>

void __iomem * ioremap_prot(phys_addr_t phys_addr,size_t size,unsigned long prot)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/fs.h>

void iput(struct inode * inode)
{
	lx_emul_trace_and_stop(__func__);
}


extern bool irq_wait_for_poll(struct irq_desc * desc);
bool irq_wait_for_poll(struct irq_desc * desc)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/irq_work.h>

void irq_work_tick(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/property.h>

bool is_software_node(const struct fwnode_handle * fwnode)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kobject.h>

struct kobject *kernel_kobj;


#include <linux/sched.h>

void kick_process(struct task_struct * p)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kmsg_dump.h>

void kmsg_dump(enum kmsg_dump_reason reason)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kobject.h>

int kobject_synth_uevent(struct kobject * kobj,const char * buf,size_t count)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kstrtox.h>

noinline int kstrtobool(const char * s,bool * res)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kstrtox.h>

noinline int kstrtoint(const char * s,unsigned int base,int * res)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kstrtox.h>

noinline int kstrtoll(const char * s,unsigned int base,long long * res)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kstrtox.h>

noinline int kstrtoull(const char * s,unsigned int base,unsigned long long * res)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/writeback.h>

void laptop_io_completion(struct backing_dev_info * info)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/writeback.h>

int laptop_mode;


#include <linux/leds.h>

void led_classdev_unregister(struct led_classdev * led_cdev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/leds.h>

void led_trigger_unregister_simple(struct led_trigger * trig)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/linear_range.h>

unsigned int linear_range_get_max_value(const struct linear_range * r)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/linear_range.h>

int linear_range_get_selector_high(const struct linear_range * r,unsigned int val,unsigned int * selector,bool * found)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/linear_range.h>

int linear_range_get_value_array(const struct linear_range * r,int ranges,unsigned int selector,unsigned int * val)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/linear_range.h>

unsigned int linear_range_values_in_range(const struct linear_range * r)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/llist.h>

bool llist_add_batch(struct llist_node * new_first,struct llist_node * new_last,struct llist_head * head)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/llist.h>

struct llist_node * llist_reverse_order(struct llist_node * head)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/logic_pio.h>

unsigned long logic_pio_trans_hwaddr(struct fwnode_handle * fwnode,resource_size_t addr,resource_size_t size)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/delay.h>

unsigned long loops_per_jiffy;


#include <linux/delay.h>

unsigned long lpj_fine;


#include <linux/string.h>

ssize_t memory_read_from_buffer(void * to,size_t count,loff_t * ppos,const void * from,size_t available)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/mmzone.h>

struct pglist_data * next_online_pgdat(struct pglist_data * pgdat)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/irq.h>

struct irq_chip no_irq_chip;


#include <linux/fs.h>

int nonseekable_open(struct inode * inode,struct file * filp)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/irq.h>

void note_interrupt(struct irq_desc * desc,irqreturn_t action_ret)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/clk.h>

struct clk * of_clk_get(struct device_node * np,int index)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/of.h>

ssize_t of_modalias(const struct device_node * np,char * str,ssize_t len)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/serial_core.h>

int __init of_setup_earlycon(const struct earlycon_id * match,unsigned long node,const char * options)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/reboot.h>

enum reboot_mode panic_reboot_mode;


#include <linux/blkdev.h>

const struct device_type part_type;


#include <linux/initrd.h>

unsigned long phys_initrd_size;


#include <linux/initrd.h>

phys_addr_t phys_initrd_start;


#include <linux/pm_runtime.h>

int pm_generic_runtime_resume(struct device * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pm_runtime.h>

int pm_generic_runtime_suspend(struct device * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pm_runtime.h>

void pm_runtime_new_link(struct device * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sysctl.h>

int proc_dointvec_minmax(struct ctl_table * table,int write,void * buffer,size_t * lenp,loff_t * ppos)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sysctl.h>

int proc_douintvec(struct ctl_table * table,int write,void * buffer,size_t * lenp,loff_t * ppos)
{
	lx_emul_trace_and_stop(__func__);
}


extern void raw_spin_rq_lock_nested(struct rq * rq,int subclass);
void raw_spin_rq_lock_nested(struct rq * rq,int subclass)
{
	lx_emul_trace_and_stop(__func__);
}


extern void raw_spin_rq_unlock(struct rq * rq);
void raw_spin_rq_unlock(struct rq * rq)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/rcutree.h>

void rcu_barrier(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/reboot.h>

enum reboot_mode reboot_mode;


#include <linux/refcount.h>

void refcount_warn_saturate(refcount_t * r,enum refcount_saturation_type t)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/reboot.h>

int register_restart_handler(struct notifier_block * nb)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/ioport.h>

int release_resource(struct resource * old)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/mm.h>

void __meminit reserve_bootmem_region(phys_addr_t start,phys_addr_t end,int nid)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/seq_file.h>

void seq_printf(struct seq_file * m,const char * f,...)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/seq_file.h>

void seq_puts(struct seq_file * m,const char * s)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/seq_file.h>

void seq_vprintf(struct seq_file * m,const char * f,va_list args)
{
	lx_emul_trace_and_stop(__func__);
}


extern void set_rq_offline(struct rq * rq);
void set_rq_offline(struct rq * rq)
{
	lx_emul_trace_and_stop(__func__);
}


extern void set_rq_online(struct rq * rq);
void set_rq_online(struct rq * rq)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sched/debug.h>

void show_state_filter(unsigned int state_filter)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/siphash.h>

u64 siphash_1u64(const u64 first,const siphash_key_t * key)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/smp.h>

void smp_call_function_many(const struct cpumask * mask,smp_call_func_t func,void * info,bool wait)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/smp.h>

int smp_call_function_single(int cpu,smp_call_func_t func,void * info,int wait)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/smp.h>

int smp_call_function_single_async(int cpu,struct __call_single_data * csd)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/smp.h>

void smp_send_stop(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sys_soc.h>

const struct soc_device_attribute * soc_device_match(const struct soc_device_attribute * matches)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/jump_label.h>

bool static_key_initialized;


#include <linux/printk.h>

int suppress_printk;


#include <linux/rcupdate.h>

void synchronize_rcu(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sysctl.h>

const int sysctl_vals[] = {};


#include <linux/sysfs.h>

int sysfs_emit(char * buf,const char * fmt,...)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sysfs.h>

int sysfs_emit_at(char * buf,int at,const char * fmt,...)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/clockchips.h>

void tick_broadcast(const struct cpumask * mask)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/mm.h>

void unpin_user_page(struct page * page)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/fs.h>

void unregister_chrdev_region(dev_t from,unsigned count)
{
	lx_emul_trace_and_stop(__func__);
}


extern void unregister_handler_proc(unsigned int irq,struct irqaction * action);
void unregister_handler_proc(unsigned int irq,struct irqaction * action)
{
	lx_emul_trace_and_stop(__func__);
}


extern void unregister_irq_proc(unsigned int irq,struct irq_desc * desc);
void unregister_irq_proc(unsigned int irq,struct irq_desc * desc)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/reboot.h>

int unregister_restart_handler(struct notifier_block * nb)
{
	lx_emul_trace_and_stop(__func__);
}


extern void update_group_capacity(struct sched_domain * sd,int cpu);
void update_group_capacity(struct sched_domain * sd,int cpu)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/uuid.h>

const u8 uuid_index[16] = {};


#include <linux/vmalloc.h>

void vfree(const void * addr)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/vmalloc.h>

bool vmalloc_dump_obj(void * object)
{
	lx_emul_trace_and_stop(__func__);
}

