/*
 * \brief  Dummy definitions of Linux Kernel functions
 * \author Automatically generated file - do no edit
 * \date   2024-09-09
 */

#include <lx_emul.h>


#include <linux/ratelimit_types.h>

int ___ratelimit(struct ratelimit_state * rs,const char * func)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/cpumask.h>

struct cpumask __cpu_active_mask;


#include <linux/ioport.h>

struct resource * __devm_request_region(struct device * dev,struct resource * parent,resource_size_t start,resource_size_t n,const char * name)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/reset.h>

struct reset_control * __devm_reset_control_get(struct device * dev,const char * id,int index,bool shared,bool optional,bool acquired)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/serial_core.h>

const struct earlycon_id __earlycon_table[] = {};


#include <linux/serial_core.h>

const struct earlycon_id __earlycon_table_end[] = {};


#include <linux/printk.h>

int __printk_ratelimit(const char * func)
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


#include <linux/mm.h>

void __show_mem(unsigned int filter,nodemask_t * nodemask,int max_zone_idx)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/fs.h>

void __unregister_chrdev(unsigned int major,unsigned int baseminor,unsigned int count,const char * name)
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

struct bus_type amba_bustype;


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


#include <linux/amba/bus.h>

void amba_device_unregister(struct amba_device * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/async.h>

async_cookie_t async_schedule_node(async_func_t func,void * data,int node)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/async.h>

void async_synchronize_full(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/blkdev.h>

struct class block_class;


#include <linux/init.h>

char __initdata boot_command_line[] = {};


#include <linux/kernel.h>

void bust_spinlocks(int yes)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/cdev.h>

void cdev_del(struct cdev * p)
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


#include <linux/pm_qos.h>

enum pm_qos_flags_status dev_pm_qos_flags(struct device * dev,s32 mask)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/dma-map-ops.h>

bool dma_default_coherent;


#include <linux/dma-mapping.h>

int dma_mmap_attrs(struct device * dev,struct vm_area_struct * vma,void * cpu_addr,dma_addr_t dma_addr,size_t size,unsigned long attrs)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/dmapool.h>

void dma_pool_destroy(struct dma_pool * pool)
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


#include <linux/genalloc.h>

void * gen_pool_dma_alloc(struct gen_pool * pool,size_t size,dma_addr_t * dma)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/genalloc.h>

void * gen_pool_dma_alloc_align(struct gen_pool * pool,size_t size,dma_addr_t * dma,int align)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/genalloc.h>

void gen_pool_free_owner(struct gen_pool * pool,unsigned long addr,size_t size,void ** owner)
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


#include <linux/uuid.h>

const u8 guid_index[16] = {};


#include <linux/capability.h>

bool has_capability_noaudit(struct task_struct * t,int cap)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/utsname.h>

struct uts_namespace init_uts_ns;


#include <linux/init.h>

bool initcall_debug;


#include <linux/fs.h>

struct timespec64 inode_set_ctime_current(struct inode * inode)
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


#include <asm-generic/io.h>

void __iomem * ioremap_prot(phys_addr_t phys_addr,size_t size,unsigned long prot)
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


#include <linux/kobject.h>

struct kobject *kernel_kobj;


#include <linux/sched/signal.h>

int kill_pid_usb_asyncio(int sig,int errno,sigval_t addr,struct pid * pid,const struct cred * cred)
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

loff_t no_seek_end_llseek(struct file * file,loff_t offset,int whence)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/fs.h>

loff_t noop_llseek(struct file * file,loff_t offset,int whence)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/irq.h>

void note_interrupt(struct irq_desc * desc,irqreturn_t action_ret)
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


#include <linux/pci.h>

int pci_alloc_irq_vectors(struct pci_dev * dev,unsigned int min_vecs,unsigned int max_vecs,unsigned int flags)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

struct bus_type pci_bus_type;


#include <linux/pci.h>

pci_power_t pci_choose_state(struct pci_dev * dev,pm_message_t state)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

void pci_d3cold_disable(struct pci_dev * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

void pci_dev_put(struct pci_dev * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

bool pci_dev_run_wake(struct pci_dev * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

void pci_disable_device(struct pci_dev * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

int pci_enable_device(struct pci_dev * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

void pci_free_irq_vectors(struct pci_dev * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

struct pci_dev * pci_get_device(unsigned int vendor,unsigned int device,struct pci_dev * from)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

void __iomem * pci_ioremap_bar(struct pci_dev * pdev,int bar)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

int pci_irq_vector(struct pci_dev * dev,unsigned int nr)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

const struct pci_device_id * pci_match_id(const struct pci_device_id * ids,struct pci_dev * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

int pci_read_config_byte(const struct pci_dev * dev,int where,u8 * val)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

int pci_read_config_dword(const struct pci_dev * dev,int where,u32 * val)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

int pci_read_config_word(const struct pci_dev * dev,int where,u16 * val)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

void pci_set_master(struct pci_dev * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

int pci_set_mwi(struct pci_dev * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

int pci_set_power_state(struct pci_dev * dev,pci_power_t state)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

int pci_write_config_byte(const struct pci_dev * dev,int where,u8 val)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

int pci_write_config_dword(const struct pci_dev * dev,int where,u32 val)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

int pci_write_config_word(const struct pci_dev * dev,int where,u16 val)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/initrd.h>

unsigned long phys_initrd_size;


#include <linux/initrd.h>

phys_addr_t phys_initrd_start;


#include <linux/pm_runtime.h>

struct workqueue_struct *pm_wq;


#include <linux/pm.h>

const char power_group_name[] = {};		/* = power */


#include <linux/power_supply.h>

struct power_supply * power_supply_get_by_name(const char * name)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/power_supply.h>

void power_supply_put(struct power_supply * psy)
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


#include <linux/reboot.h>

enum reboot_mode reboot_mode;


#include <linux/refcount.h>

void refcount_warn_saturate(refcount_t * r,enum refcount_saturation_type t)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/regulator/consumer.h>

int regulator_disable(struct regulator * regulator)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/regulator/consumer.h>

void regulator_put(struct regulator * regulator)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/ioport.h>

int release_resource(struct resource * old)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/mm.h>

int remap_pfn_range(struct vm_area_struct * vma,unsigned long addr,unsigned long pfn,unsigned long size,pgprot_t prot)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/mm.h>

void __meminit reserve_bootmem_region(phys_addr_t start,phys_addr_t end,int nid)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/reset.h>

int reset_control_reset(struct reset_control * rstc)
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

void smp_send_stop(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/jump_label.h>

bool static_key_initialized;


#include <linux/printk.h>

int suppress_printk;


#include <linux/sysctl.h>

const int sysctl_vals[] = {};


#include <linux/sysfs.h>

struct kernfs_node * sysfs_break_active_protection(struct kobject * kobj,const struct attribute * attr)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sysfs.h>

void sysfs_unbreak_active_protection(struct kernfs_node * kn)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sysfs.h>

int sysfs_update_group(struct kobject * kobj,const struct attribute_group * grp)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/clockchips.h>

void tick_broadcast(const struct cpumask * mask)
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

