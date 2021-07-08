/*
 * \brief  Dummy definitions of Linux Kernel functions
 * \author Automatically generated file - do no edit
 * \date   2021-07-02
 */

#include <lx_emul.h>


#include <linux/ratelimit_types.h>

int ___ratelimit(struct ratelimit_state * rs,const char * func)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/blk-cgroup.h>

bool __blkcg_punt_bio_submit(struct bio * bio)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/blk-cgroup.h>

u64 __blkg_prfill_u64(struct seq_file * sf,struct blkg_policy_data * pd,u64 v)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/thread_info.h>

void __check_object_size(const void * ptr,unsigned long n,bool to_user)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/clk-provider.h>

const char * __clk_get_name(const struct clk * clk)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/cpuhotplug.h>

int __cpuhp_state_remove_instance(enum cpuhp_state state,struct hlist_node * node,bool invoke)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kexec.h>

void __noclone __crash_kexec(struct pt_regs * regs)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/serial_core.h>

const struct earlycon_id __earlycon_table[] = {};


#include <linux/serial_core.h>

const struct earlycon_id __earlycon_table_end[] = {};


#include <linux/gfp.h>

void __free_pages(struct page * page,unsigned int order)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/genhd.h>

int __invalidate_device(struct block_device * bdev,bool kill_dirty)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/suspend.h>

void __pm_pr_dbg(bool defer,const char * fmt,...)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pm_runtime.h>

void __pm_runtime_disable(struct device * dev,bool check_resume)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/mm.h>

void __put_page(struct page * page)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sched/task.h>

void __put_task_struct(struct task_struct * tsk)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/freezer.h>

bool __refrigerator(bool check_kthr_stop)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/fs.h>

void __remove_inode_hash(struct inode * inode)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sched.h>

pid_t __task_pid_nr_ns(struct task_struct * task,enum pid_type type,struct pid_namespace * ns)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/interrupt.h>

void __tasklet_schedule(struct tasklet_struct * t)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/blktrace_api.h>

void __trace_note_message(struct blk_trace * bt,struct blkcg * blkcg,const char * fmt,...)
{
	lx_emul_trace_and_stop(__func__);
}


#include <asm-generic/delay.h>

void __udelay(unsigned long usecs)
{
	lx_emul_trace_and_stop(__func__);
}


extern unsigned int _parse_integer(const char * s,unsigned int base,unsigned long long * p);
unsigned int _parse_integer(const char * s,unsigned int base,unsigned long long * p)
{
	lx_emul_trace_and_stop(__func__);
}


extern const char * _parse_integer_fixup_radix(const char * s,unsigned int * base);
const char * _parse_integer_fixup_radix(const char * s,unsigned int * base)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kernel_stat.h>

void account_idle_ticks(unsigned long ticks)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/random.h>

void add_bootloader_randomness(const void * buf,unsigned int size)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kobject.h>

int add_uevent_var(struct kobj_uevent_env * env,const char * format,...)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/gfp.h>

struct page * alloc_pages_current(gfp_t gfp,unsigned order)
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


#include <linux/dma-map-ops.h>

void arch_teardown_dma_ops(struct device * dev)
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

struct block_device * bdgrab(struct block_device * bdev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/backing-dev.h>

void bdi_put(struct backing_dev_info * bdi)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/backing-dev.h>

void bdi_unregister(struct backing_dev_info * bdi)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/blkdev.h>

void bdput(struct block_device * bdev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/blkdev.h>

void blk_execute_rq(struct request_queue * q,struct gendisk * bd_disk,struct request * rq,int at_head)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/blktrace_api.h>

void blk_fill_rwbs(char * rwbs,unsigned int op,int bytes)
{
	lx_emul_trace_and_stop(__func__);
}


extern void blk_free_queue_stats(struct blk_queue_stats * stats);
void blk_free_queue_stats(struct blk_queue_stats * stats)
{
	lx_emul_trace_and_stop(__func__);
}


extern void blk_mq_debugfs_register_sched(struct request_queue * q);
void blk_mq_debugfs_register_sched(struct request_queue * q)
{
	lx_emul_trace_and_stop(__func__);
}


extern void blk_mq_debugfs_register_sched_hctx(struct request_queue * q,struct blk_mq_hw_ctx * hctx);
void blk_mq_debugfs_register_sched_hctx(struct request_queue * q,struct blk_mq_hw_ctx * hctx)
{
	lx_emul_trace_and_stop(__func__);
}


extern void blk_mq_debugfs_unregister_hctx(struct blk_mq_hw_ctx * hctx);
void blk_mq_debugfs_unregister_hctx(struct blk_mq_hw_ctx * hctx)
{
	lx_emul_trace_and_stop(__func__);
}


extern void blk_mq_debugfs_unregister_queue_rqos(struct request_queue * q);
void blk_mq_debugfs_unregister_queue_rqos(struct request_queue * q)
{
	lx_emul_trace_and_stop(__func__);
}


extern void blk_mq_debugfs_unregister_sched(struct request_queue * q);
void blk_mq_debugfs_unregister_sched(struct request_queue * q)
{
	lx_emul_trace_and_stop(__func__);
}


extern void blk_mq_debugfs_unregister_sched_hctx(struct blk_mq_hw_ctx * hctx);
void blk_mq_debugfs_unregister_sched_hctx(struct blk_mq_hw_ctx * hctx)
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


extern void blk_stat_free_callback(struct blk_stat_callback * cb);
void blk_stat_free_callback(struct blk_stat_callback * cb)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/blkdev.h>

void blk_unregister_queue(struct gendisk * disk)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/blk-cgroup.h>

void blkcg_print_blkgs(struct seq_file * sf,struct blkcg * blkcg,u64 (* prfill)(struct seq_file *,struct blkg_policy_data *,int),const struct blkcg_policy * pol,int data,bool show_total)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/blk-cgroup.h>

struct blkcg blkcg_root;


#include <linux/blk-cgroup.h>

void blkg_conf_finish(struct blkg_conf_ctx * ctx)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/blk-cgroup.h>

int blkg_conf_prep(struct blkcg * blkcg,const struct blkcg_policy * pol,char * input,struct blkg_conf_ctx * ctx)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/blk-cgroup.h>

const char * blkg_dev_name(struct blkcg_gq * blkg)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/blk-cgroup.h>

struct blkcg_gq * blkg_lookup_slowpath(struct blkcg * blkcg,struct request_queue * q,bool update_hint)
{
	lx_emul_trace_and_stop(__func__);
}


extern u64 blkg_prfill_rwstat(struct seq_file * sf,struct blkg_policy_data * pd,int off);
u64 blkg_prfill_rwstat(struct seq_file * sf,struct blkg_policy_data * pd,int off)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/writeback.h>

int block_dump;


#include <linux/init.h>

char __initdata boot_command_line[] = {};


#include <linux/bsearch.h>

void * bsearch(const void * key,const void * base,size_t num,size_t size,cmp_func_t cmp)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kernel.h>

void bust_spinlocks(int yes)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sched/nohz.h>

void calc_load_nohz_stop(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/rcupdate.h>

void call_rcu(struct rcu_head * head,rcu_callback_t func)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/srcu.h>

void call_srcu(struct srcu_struct * ssp,struct rcu_head * rhp,rcu_callback_t func)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/capability.h>

bool capable(int cap)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/cdev.h>

int cdev_device_add(struct cdev * cdev,struct device * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/cdev.h>

void cdev_device_del(struct cdev * cdev,struct device * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/cdev.h>

void cdev_init(struct cdev * cdev,const struct file_operations * fops)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/console.h>

void console_flush_on_panic(enum con_flush_mode mode)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/printk.h>

int console_printk[] = {};


#include <linux/console.h>

void console_unblank(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pm_qos.h>

void cpu_latency_qos_add_request(struct pm_qos_request * req,s32 value)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pm_qos.h>

void cpu_latency_qos_remove_request(struct pm_qos_request * req)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/arch_topology.h>

struct cpu_topology cpu_topology[NR_CPUS] = {};


#include <linux/sched/topology.h>

bool cpus_share_cache(int this_cpu,int that_cpu)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/cgroup.h>

struct cgroup_subsys_state * css_next_descendant_post(struct cgroup_subsys_state * pos,struct cgroup_subsys_state * root)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/cgroup.h>

struct cgroup_subsys_state * css_next_descendant_pre(struct cgroup_subsys_state * pos,struct cgroup_subsys_state * root)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/debugfs.h>

ssize_t debugfs_attr_read(struct file * file,char __user * buf,size_t len,loff_t * ppos)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/debugfs.h>

ssize_t debugfs_attr_write(struct file * file,const char __user * buf,size_t len,loff_t * ppos)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/debugfs.h>

struct dentry * debugfs_create_bool(const char * name,umode_t mode,struct dentry * parent,bool * value)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/debugfs.h>

void debugfs_create_u32(const char * name,umode_t mode,struct dentry * parent,u32 * value)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/debugfs.h>

int debugfs_file_get(struct dentry * dentry)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/debugfs.h>

void debugfs_file_put(struct dentry * dentry)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/debugfs.h>

ssize_t debugfs_read_file_bool(struct file * file,char __user * user_buf,size_t count,loff_t * ppos)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/debugfs.h>

void debugfs_remove(struct dentry * dentry)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/vmstat.h>

void dec_zone_page_state(struct page * page,enum zone_stat_item item)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/fs.h>

loff_t default_llseek(struct file * file,loff_t offset,int whence)
{
	lx_emul_trace_and_stop(__func__);
}


extern void delete_partition(struct block_device * part);
void delete_partition(struct block_device * part)
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


extern int devtmpfs_delete_node(struct device * dev);
int devtmpfs_delete_node(struct device * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/dma-mapping.h>

unsigned long dma_get_merge_boundary(struct device * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/dma-mapping.h>

dma_addr_t dma_map_page_attrs(struct device * dev,struct page * page,size_t offset,size_t size,enum dma_data_direction dir,unsigned long attrs)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/dma-mapping.h>

void dma_sync_sg_for_cpu(struct device * dev,struct scatterlist * sg,int nelems,enum dma_data_direction dir)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/dma-mapping.h>

void dma_sync_single_for_cpu(struct device * dev,dma_addr_t addr,size_t size,enum dma_data_direction dir)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/dma-mapping.h>

void dma_sync_single_for_device(struct device * dev,dma_addr_t addr,size_t size,enum dma_data_direction dir)
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


extern void dpm_sysfs_remove(struct device * dev);
void dpm_sysfs_remove(struct device * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/printk.h>

asmlinkage __visible void dump_stack(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/crash_dump.h>

unsigned long long elfcorehdr_addr;


#include <linux/reboot.h>

void emergency_restart(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/syscalls.h>

struct trace_event_functions enter_syscall_print_funcs;


#include <linux/errname.h>

const char * errname(int err)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/syscalls.h>

struct trace_event_class event_class_syscall_enter;


#include <linux/syscalls.h>

struct trace_event_class event_class_syscall_exit;


#include <linux/trace_events.h>

enum event_trigger_type event_triggers_call(struct trace_event_file * file,void * rec,struct ring_buffer_event * event)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/syscalls.h>

struct trace_event_functions exit_syscall_print_funcs;


#include <linux/kobject.h>

struct kobject *firmware_kobj;


extern void flush_dcache_page(struct page * page);
void flush_dcache_page(struct page * page)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/percpu.h>

void free_percpu(void __percpu * ptr)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/freezer.h>

bool freezing_slow_path(struct task_struct * p)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/uidgid.h>

gid_t from_kgid(struct user_namespace * targ,kgid_t kgid)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/uidgid.h>

uid_t from_kuid(struct user_namespace * targ,kuid_t kuid)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/blkdev.h>

int fsync_bdev(struct block_device * bdev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kernel.h>

void ftrace_dump(enum ftrace_dump_mode oops_dump_mode)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/property.h>

void fwnode_remove_software_node(struct fwnode_handle * fwnode)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/bug.h>

void generic_bug_clear_once(void)
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


#include <linux/sched/isolation.h>

bool housekeeping_enabled(enum hk_flags flags)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/vmstat.h>

void inc_zone_page_state(struct page * page,enum zone_stat_item item)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/utsname.h>

struct user_namespace init_user_ns;


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


#include <linux/sched.h>

long __sched io_schedule_timeout(long timeout)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/ioport.h>

struct resource iomem_resource;


#include <linux/ioport.h>

struct resource ioport_resource;


extern bool irq_pm_check_wakeup(struct irq_desc * desc);
bool irq_pm_check_wakeup(struct irq_desc * desc)
{
	lx_emul_trace_and_stop(__func__);
}


extern void irq_pm_remove_action(struct irq_desc * desc,struct irqaction * action);
void irq_pm_remove_action(struct irq_desc * desc,struct irqaction * action)
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


#include <linux/mm.h>

bool is_vmalloc_addr(const void * x)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kobject.h>

struct kobject *kernel_kobj;


#include <linux/kernfs.h>

void kernfs_put(struct kernfs_node * kn)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kgdb.h>

void kgdb_panic(const char * msg)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sched.h>

void kick_process(struct task_struct * p)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/slab.h>

void kmem_cache_destroy(struct kmem_cache * s)
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


#include <linux/kobject.h>

int kobject_uevent_env(struct kobject * kobj,enum kobject_action action,char * envp_ext[])
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/string.h>

int kstrtobool(const char * s,bool * res)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kernel.h>

int kstrtobool_from_user(const char __user * s,size_t count,bool * res)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kernel.h>

int kstrtoint(const char * s,unsigned int base,int * res)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kernel.h>

int kstrtoll(const char * s,unsigned int base,long long * res)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kernel.h>

int kstrtouint(const char * s,unsigned int base,unsigned int * res)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kernel.h>

int kstrtoull(const char * s,unsigned int base,unsigned long long * res)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/rcutree.h>

void kvfree_call_rcu(struct rcu_head * head,rcu_callback_t func)
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


#include <linux/writeback.h>

void laptop_mode_timer_fn(struct timer_list * t)
{
	lx_emul_trace_and_stop(__func__);
}


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


#include <linux/logic_pio.h>

unsigned long logic_pio_trans_hwaddr(struct fwnode_handle * fwnode,resource_size_t addr,resource_size_t size)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/delay.h>

unsigned long lpj_fine;


#include <linux/parser.h>

bool match_wildcard(const char * pattern,const char * str)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/memblock.h>

unsigned long max_low_pfn;


#include <linux/memblock.h>

unsigned long max_pfn;


#include <linux/memblock.h>

int __init_memblock memblock_add(phys_addr_t base,phys_addr_t size)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/memblock.h>

phys_addr_t __init_memblock memblock_find_in_range(phys_addr_t start,phys_addr_t end,phys_addr_t size,phys_addr_t align)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/memblock.h>

int __init_memblock memblock_free(phys_addr_t base,phys_addr_t size)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/memblock.h>

int __init_memblock memblock_mark_hotplug(phys_addr_t base,phys_addr_t size)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/memblock.h>

int __init_memblock memblock_remove(phys_addr_t base,phys_addr_t size)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/memblock.h>

int __init_memblock memblock_reserve(phys_addr_t base,phys_addr_t size)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/string.h>

ssize_t memory_read_from_buffer(void * to,size_t count,loff_t * ppos,const void * from,size_t available)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/irq.h>

struct irq_chip no_irq_chip;


#include <linux/fs.h>

loff_t no_llseek(struct file * file,loff_t offset,int whence)
{
	lx_emul_trace_and_stop(__func__);
}


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


#include <linux/cgroup.h>

struct cgroup_subsys_state * of_css(struct kernfs_open_file * of)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pm_opp.h>

int of_get_required_opp_performance_state(struct device_node * np,int index)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/serial_core.h>

int __init of_setup_earlycon(const struct earlycon_id * match,unsigned long node,const char * options)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/smp.h>

void on_each_cpu(smp_call_func_t func,void * info,int wait)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/printk.h>

int oops_in_progress;	/* If set, an oops, panic(), BUG() or die() is in progress */


#include <linux/reboot.h>

enum reboot_mode panic_reboot_mode;


#include <linux/genhd.h>

struct device_type part_type;


#include <linux/trace_events.h>

void * perf_trace_buf_alloc(int size,struct pt_regs ** regs,int * rctxp)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/trace_events.h>

void perf_trace_run_bpf_submit(void * raw_data,int size,int rctx,struct trace_event_call * call,u64 count,struct pt_regs * regs,struct hlist_head * head,struct task_struct * task)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/initrd.h>

unsigned long phys_initrd_size;


#include <linux/initrd.h>

phys_addr_t phys_initrd_start;


#include <linux/pinctrl/consumer.h>

int pinctrl_pm_select_default_state(struct device * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pinctrl/consumer.h>

int pinctrl_pm_select_sleep_state(struct device * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pinctrl/consumer.h>

int pinctrl_select_state(struct pinctrl * p,struct pinctrl_state * state)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pm.h>

int pm_generic_resume(struct device * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pm.h>

int pm_generic_suspend(struct device * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/suspend.h>

suspend_state_t pm_suspend_target_state;


#include <linux/pm_wakeup.h>

void pm_wakeup_ws_event(struct wakeup_source * ws,unsigned int msec,bool hard)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/printk.h>

int printk_deferred(const char * fmt,...)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/printk.h>

void printk_safe_flush_on_panic(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/proc_fs.h>

struct proc_dir_entry * proc_create(const char * name,umode_t mode,struct proc_dir_entry * parent,const struct proc_ops * proc_ops)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/rcutree.h>

void rcu_irq_enter_irqson(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/rcutree.h>

void rcu_irq_exit_irqson(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/reboot.h>

enum reboot_mode reboot_mode;


#include <linux/refcount.h>

bool refcount_dec_not_one(refcount_t * r)
{
	lx_emul_trace_and_stop(__func__);
}


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


#include <linux/rtc.h>

void rtc_class_close(struct rtc_device * rtc)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/rtc.h>

struct rtc_device * rtc_class_open(const char * name)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/rtc.h>

int rtc_set_time(struct rtc_device * rtc,struct rtc_time * tm)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/rtc.h>

void rtc_time64_to_tm(time64_t time,struct rtc_time * tm)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/init.h>

char *saved_command_line;


#include <linux/seq_file.h>

void seq_escape(struct seq_file * m,const char * s,const char * esc)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/seq_file.h>

loff_t seq_lseek(struct file * file,loff_t offset,int whence)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/seq_file.h>

int seq_open_private(struct file * filp,const struct seq_operations * ops,int psize)
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

ssize_t seq_read(struct file * file,char __user * buf,size_t size,loff_t * ppos)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/seq_file.h>

int seq_release_private(struct inode * inode,struct file * file)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/seq_file.h>

void seq_vprintf(struct seq_file * m,const char * f,va_list args)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/mm.h>

int set_page_dirty_lock(struct page * page)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/mm.h>

void show_mem(unsigned int filter,nodemask_t * nodemask)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sched/debug.h>

void show_state_filter(unsigned long state_filter)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/fs.h>

int simple_attr_open(struct inode * inode,struct file * file,int (* get)(void *,u64 *),int (* set)(void *,u64),const char * fmt)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/fs.h>

int simple_attr_release(struct inode * inode,struct file * file)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/fs.h>

int simple_open(struct inode * inode,struct file * file)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/fs.h>

ssize_t simple_read_from_buffer(void __user * to,size_t count,loff_t * ppos,const void * from,size_t available)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/seq_file.h>

int single_open(struct file * file,int (* show)(struct seq_file *,void *),void * data)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/seq_file.h>

int single_release(struct inode * inode,struct file * file)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/siphash.h>

u64 siphash_1u64(const u64 first,const siphash_key_t * key)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/smp.h>

int smp_call_function_single(int cpu,smp_call_func_t func,void * info,int wait)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/smp.h>

int smp_call_function_single_async(int cpu,call_single_data_t * csd)
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


#include <linux/kallsyms.h>

int sprint_backtrace(char * buffer,unsigned long address)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kallsyms.h>

int sprint_symbol(char * buffer,unsigned long address)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kallsyms.h>

int sprint_symbol_no_offset(char * buffer,unsigned long address)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/jump_label.h>

bool static_key_initialized;


#include <linux/printk.h>

int suppress_printk;


#include <linux/swiotlb.h>

unsigned int swiotlb_max_segment(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/rcupdate.h>

void synchronize_rcu(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sched/sysctl.h>

unsigned long sysctl_hung_task_timeout_secs;


#include <linux/sysfs.h>

void sysfs_delete_link(struct kobject * kobj,struct kobject * targ,const char * name)
{
	lx_emul_trace_and_stop(__func__);
}


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


#include <linux/sysfs.h>

void sysfs_remove_dir(struct kobject * kobj)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sysfs.h>

void sysfs_remove_files(struct kobject * kobj,const struct attribute * const * ptr)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sysfs.h>

void sysfs_remove_groups(struct kobject * kobj,const struct attribute_group ** groups)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sysfs.h>

void sysfs_remove_link(struct kobject * kobj,const char * name)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/freezer.h>

atomic_t system_freezing_cnt;	/* nr of freezing conds in effect */


#include <linux/sched/numa_balancing.h>

pid_t task_numa_group_id(struct task_struct * p)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/clockchips.h>

void tick_broadcast(const struct cpumask * mask)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/hrtimer.h>

void timerfd_clock_was_set(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/nmi.h>

notrace void touch_softlockup_watchdog(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/nmi.h>

notrace void touch_softlockup_watchdog_sched(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/trace_events.h>

void trace_event_buffer_commit(struct trace_event_buffer * fbuffer)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/trace_events.h>

void * trace_event_buffer_reserve(struct trace_event_buffer * fbuffer,struct trace_event_file * trace_file,unsigned long len)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/trace_events.h>

bool trace_event_ignore_this_pid(struct trace_event_file * trace_file)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/trace_events.h>

int trace_event_raw_init(struct trace_event_call * call)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/trace_events.h>

int trace_event_reg(struct trace_event_call * call,enum trace_reg type,void * data)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/trace_events.h>

enum print_line_t trace_handle_return(struct trace_seq * s)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/trace_events.h>

const char * trace_print_flags_seq(struct trace_seq * p,const char * delim,unsigned long flags,const struct trace_print_flags * flag_array)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/trace_events.h>

const char * trace_print_symbols_seq(struct trace_seq * p,unsigned long val,const struct trace_print_flags * symbol_array)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/trace_events.h>

int trace_raw_output_prep(struct trace_iterator * iter,struct trace_event * trace_event)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/trace_seq.h>

void trace_seq_printf(struct trace_seq * s,const char * fmt,...)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/vt_kern.h>

void unblank_screen(void)
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


#include <linux/suspend.h>

int unregister_pm_notifier(struct notifier_block * nb)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/reboot.h>

int unregister_restart_handler(struct notifier_block * nb)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/uuid.h>

const u8 uuid_index[16] = {};


#include <linux/sched/wake_q.h>

void wake_q_add(struct wake_q_head * head,struct task_struct * task)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sched/wake_q.h>

void wake_q_add_safe(struct wake_q_head * head,struct task_struct * task)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sched/nohz.h>

void wake_up_nohz_cpu(int cpu)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sched/wake_q.h>

void wake_up_q(struct wake_q_head * head)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pm_wakeup.h>

void wakeup_source_unregister(struct wakeup_source * ws)
{
	lx_emul_trace_and_stop(__func__);
}


extern void wbt_set_write_cache(struct request_queue * q,bool write_cache_on);
void wbt_set_write_cache(struct request_queue * q,bool write_cache_on)
{
	lx_emul_trace_and_stop(__func__);
}


#include <xen/xen.h>

bool xen_biovec_phys_mergeable(const struct bio_vec * vec1,const struct page * page)
{
	lx_emul_trace_and_stop(__func__);
}


#include <xen/xen.h>

enum xen_domain_type xen_domain_type;

