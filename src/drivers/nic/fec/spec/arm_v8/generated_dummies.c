/*
 * \brief  Dummy definitions of Linux Kernel functions
 * \author Automatically generated file - do no edit
 * \date   2022-10-18
 */

#include <lx_emul.h>


#include <linux/ratelimit_types.h>

int ___ratelimit(struct ratelimit_state * rs,const char * func)
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


#include <linux/kexec.h>

void __noclone __crash_kexec(struct pt_regs * regs)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/serial_core.h>

const struct earlycon_id __earlycon_table[] = {};


#include <linux/serial_core.h>

const struct earlycon_id __earlycon_table_end[] = {};


#include <net/gen_stats.h>

void __gnet_stats_copy_basic(const seqcount_t * running,struct gnet_stats_basic_packed * bstats,struct gnet_stats_basic_cpu __percpu * cpu,struct gnet_stats_basic_packed * b)
{
	lx_emul_trace_and_stop(__func__);
}


#include <net/gen_stats.h>

void __gnet_stats_copy_queue(struct gnet_stats_queue * qstats,const struct gnet_stats_queue __percpu * cpu,const struct gnet_stats_queue * q,__u32 qlen)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/netlink.h>

struct nlmsghdr * __nlmsg_put(struct sk_buff * skb,u32 portid,u32 seq,int type,int len,int flags)
{
	lx_emul_trace_and_stop(__func__);
}


#include <asm-generic/percpu.h>

unsigned long __per_cpu_offset[NR_CPUS] = {};


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


#include <linux/user_namespace.h>

void __put_user_ns(struct user_namespace * ns)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/freezer.h>

bool __refrigerator(bool check_kthr_stop)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/rtnetlink.h>

void __rtnl_unlock(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sock_diag.h>

u64 __sock_gen_cookie(struct sock * sk)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sched.h>

pid_t __task_pid_nr_ns(struct task_struct * task,enum pid_type type,struct pid_namespace * ns)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/vmalloc.h>

void * __vmalloc_node(unsigned long size,unsigned long align,gfp_t gfp_mask,int node,const void * caller)
{
	lx_emul_trace_and_stop(__func__);
}


#include <net/xfrm.h>

void __xfrm_state_destroy(struct xfrm_state * x,bool sync)
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


#include <linux/audit.h>

u32 audit_enabled;


#include <linux/audit.h>

void audit_log(struct audit_context * ctx,gfp_t gfp_mask,int type,const char * fmt,...)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/init.h>

char __initdata boot_command_line[] = {};


#include <linux/bpf.h>

void bpf_prog_inc(struct bpf_prog * prog)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/bpf.h>

void bpf_prog_put(struct bpf_prog * prog)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/filter.h>

void bpf_warn_invalid_xdp_action(u32 act)
{
	lx_emul_trace_and_stop(__func__);
}


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


#include <linux/srcu.h>

void call_srcu(struct srcu_struct * ssp,struct rcu_head * rhp,rcu_callback_t func)
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


#include <linux/bpf.h>

bool cpu_map_prog_allowed(struct bpf_map * map)
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


#include <linux/user_namespace.h>

void dec_ucount(struct ucounts * ucounts,enum ucount_type type)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/fs.h>

loff_t default_llseek(struct file * file,loff_t offset,int whence)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/bpf.h>

bool dev_map_can_have_prog(struct bpf_map * map)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/mux/consumer.h>

struct mux_control * devm_mux_control_get(struct device * dev,const char * mux_name)
{
	lx_emul_trace_and_stop(__func__);
}


extern int devtmpfs_create_node(struct device * dev);
int devtmpfs_create_node(struct device * dev)
{
	lx_emul_trace_and_stop(__func__);
}


extern int devtmpfs_delete_node(struct device * dev);
int devtmpfs_delete_node(struct device * dev)
{
	lx_emul_trace_and_stop(__func__);
}


extern unsigned int __no_sanitize_address do_csum(const unsigned char * buff,int len);
unsigned int __no_sanitize_address do_csum(const unsigned char * buff,int len)
{
	lx_emul_trace_and_stop(__func__);
}


#include <net/dst.h>

void dst_release(struct dst_entry * dst)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/printk.h>

asmlinkage __visible void dump_stack(void)
{
	lx_emul_trace_and_stop(__func__);
}


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


#include <linux/ethtool_netlink.h>

int ethnl_cable_test_alloc(struct phy_device * phydev,u8 cmd)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/ethtool_netlink.h>

int ethnl_cable_test_fault_length(struct phy_device * phydev,u8 pair,u32 cm)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/ethtool_netlink.h>

void ethnl_cable_test_finished(struct phy_device * phydev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/ethtool_netlink.h>

void ethnl_cable_test_free(struct phy_device * phydev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/ethtool_netlink.h>

int ethnl_cable_test_result(struct phy_device * phydev,u8 pair,u8 result)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/ethtool.h>

u32 ethtool_op_get_link(struct net_device * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/ethtool.h>

int ethtool_op_get_ts_info(struct net_device * dev,struct ethtool_ts_info * info)
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


#include <linux/capability.h>

bool file_ns_capable(const struct file * file,struct user_namespace * ns,int cap)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sched.h>

struct task_struct * find_task_by_vpid(pid_t vnr)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kobject.h>

struct kobject *firmware_kobj;


#include <linux/file.h>

void fput(struct file * file)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sched/user.h>

void free_uid(struct user_struct * up)
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


#include <linux/kernel.h>

void ftrace_dump(enum ftrace_dump_mode oops_dump_mode)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/property.h>

struct fwnode_handle * fwnode_create_software_node(const struct property_entry * properties,const struct fwnode_handle * parent)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/gpio/consumer.h>

struct gpio_desc * fwnode_gpiod_get_index(struct fwnode_handle * fwnode,const char * con_id,int index,enum gpiod_flags flags,const char * label)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/property.h>

void fwnode_remove_software_node(struct fwnode_handle * fwnode)
{
	lx_emul_trace_and_stop(__func__);
}


#include <net/gen_stats.h>

void gen_kill_estimator(struct net_rate_estimator __rcu ** rate_est)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/bug.h>

void generic_bug_clear_once(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/gfp.h>

bool gfp_pfmemalloc_allowed(gfp_t gfp_mask)
{
	lx_emul_trace_and_stop(__func__);
}


#include <net/gen_stats.h>

int gnet_stats_copy_basic(const seqcount_t * running,struct gnet_dump * d,struct gnet_stats_basic_cpu __percpu * cpu,struct gnet_stats_basic_packed * b)
{
	lx_emul_trace_and_stop(__func__);
}


#include <net/gen_stats.h>

int gnet_stats_copy_queue(struct gnet_dump * d,struct gnet_stats_queue __percpu * cpu_q,struct gnet_stats_queue * q,__u32 qlen)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/gpio/consumer.h>

int gpiod_get_value_cansleep(const struct gpio_desc * desc)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/gpio/consumer.h>

void gpiod_put(struct gpio_desc * desc)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/gpio/consumer.h>

int gpiod_set_consumer_name(struct gpio_desc * desc,const char * name)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/gpio/consumer.h>

void gpiod_set_value_cansleep(struct gpio_desc * desc,int value)
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

struct user_namespace init_user_ns;


#include <linux/init.h>

bool initcall_debug;


#include <linux/ioport.h>

int insert_resource(struct resource * parent,struct resource * new)
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


#include <linux/kobject.h>

struct kobject *kernel_kobj;


#include <linux/kernfs.h>

void kernfs_put(struct kernfs_node * kn)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/key.h>

void key_remove_domain(struct key_tag * domain_tag)
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


#include <linux/logic_pio.h>

unsigned long logic_pio_trans_hwaddr(struct fwnode_handle * fwnode,resource_size_t addr,resource_size_t size)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/netdevice.h>

struct pernet_operations __net_initdata loopback_net_ops;


#include <linux/delay.h>

unsigned long lpj_fine;


#include <linux/parser.h>

bool match_wildcard(const char * pattern,const char * str)
{
	lx_emul_trace_and_stop(__func__);
}


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


#include <linux/mux/consumer.h>

int mux_control_deselect(struct mux_control * mux)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/mux/consumer.h>

int mux_control_select(struct mux_control * mux,unsigned int state)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/net.h>

int net_ratelimit(void)
{
	lx_emul_trace_and_stop(__func__);
}


extern int netdev_change_owner(struct net_device * ndev,const struct net * net_old,const struct net * net_new);
int netdev_change_owner(struct net_device * ndev,const struct net * net_old,const struct net * net_new)
{
	lx_emul_trace_and_stop(__func__);
}


extern void netdev_unregister_kobject(struct net_device * ndev);
void netdev_unregister_kobject(struct net_device * ndev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/netlink.h>

bool netlink_strict_get_check(struct sk_buff * skb)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/netfilter/nf_conntrack_common.h>

void nf_conntrack_destroy(struct nf_conntrack * nfct)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/netfilter.h>

int nf_hook_slow(struct sk_buff * skb,struct nf_hook_state * state,const struct nf_hook_entries * e,unsigned int s)
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


#include <linux/nodemask.h>

nodemask_t node_states[NR_NODE_STATES] = {};


#include <linux/irq.h>

void note_interrupt(struct irq_desc * desc,irqreturn_t action_ret)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/nodemask.h>

unsigned int nr_node_ids;


#include <linux/capability.h>

bool ns_capable(struct user_namespace * ns,int cap)
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


#include <linux/moduleparam.h>

const struct kernel_param_ops param_ops_byte;


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


#include <linux/proc_ns.h>

void proc_free_inum(unsigned int inum)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/proc_ns.h>

struct file * proc_ns_fget(int fd)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/rcutree.h>

void rcu_barrier(void)
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


#include <linux/regulator/driver.h>

void * rdev_get_drvdata(struct regulator_dev * rdev)
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


#include <linux/regulator/consumer.h>

int regulator_disable(struct regulator * regulator)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/regulator/driver.h>

int regulator_list_voltage_table(struct regulator_dev * rdev,unsigned int selector)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/ioport.h>

int release_resource(struct resource * old)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/reset.h>

int reset_control_assert(struct reset_control * rstc)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/reset.h>

int reset_control_deassert(struct reset_control * rstc)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/reset.h>

void reset_control_put(struct reset_control * rstc)
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


#include <linux/rtnetlink.h>

struct sk_buff * rtmsg_ifinfo_build_skb(int type,struct net_device * dev,unsigned int change,u32 event,gfp_t flags,int * new_nsid,int new_ifindex)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/rtnetlink.h>

void rtmsg_ifinfo_newnet(int type,struct net_device * dev,unsigned int change,gfp_t flags,int * new_nsid,int new_ifindex)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/rtnetlink.h>

void rtmsg_ifinfo_send(struct sk_buff * skb,struct net_device * dev,gfp_t flags)
{
	lx_emul_trace_and_stop(__func__);
}


#include <net/rtnetlink.h>

struct net * rtnl_get_net_ns_capable(struct sock * sk,int netnsid)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/rtnetlink.h>

void rtnl_notify(struct sk_buff * skb,struct net * net,u32 pid,u32 group,struct nlmsghdr * nlh,gfp_t flags)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/rtnetlink.h>

void rtnl_set_sk_err(struct net * net,u32 group,int error)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/rtnetlink.h>

int rtnl_unicast(struct sk_buff * skb,struct net * net,u32 pid)
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


#include <net/sock.h>

void sk_free(struct sock * sk)
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


#include <net/sock.h>

void sock_edemux(struct sk_buff * skb)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/jump_label.h>

bool static_key_initialized;


#include <linux/string_helpers.h>

int string_escape_mem(const char * src,size_t isz,char * dst,size_t osz,unsigned int flags,const char * only)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/string_helpers.h>

int string_unescape(char * src,char * dst,size_t size,unsigned int flags)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/printk.h>

int suppress_printk;


#include <linux/rcupdate.h>

void synchronize_rcu(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/mfd/syscon.h>

struct regmap * syscon_node_to_regmap(struct device_node * np)
{
	lx_emul_trace_and_stop(__func__);
}


#include <net/sock.h>

int sysctl_tstamp_allow_data;


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

void sysfs_remove_bin_file(struct kobject * kobj,const struct bin_attribute * attr)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sysfs.h>

void sysfs_remove_dir(struct kobject * kobj)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sysfs.h>

void sysfs_remove_groups(struct kobject * kobj,const struct attribute_group ** groups)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sysfs.h>

int sysfs_rename_dir_ns(struct kobject * kobj,const char * new_name,const void * new_ns)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sysfs.h>

int sysfs_rename_link_ns(struct kobject * kobj,struct kobject * targ,const char * old,const char * new,const void * new_ns)
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


#include <linux/tcp.h>

struct sk_buff * tcp_get_timestamping_opt_stats(const struct sock * sk,const struct sk_buff * orig_skb)
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

const char * trace_print_hex_seq(struct trace_seq * p,const unsigned char * buf,int buf_len,bool concatenate)
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


#include <net/tso.h>

void tso_build_data(const struct sk_buff * skb,struct tso_t * tso,int size)
{
	lx_emul_trace_and_stop(__func__);
}


#include <net/tso.h>

void tso_build_hdr(const struct sk_buff * skb,char * hdr,struct tso_t * tso,int size,bool is_last)
{
	lx_emul_trace_and_stop(__func__);
}


#include <net/tso.h>

int tso_count_descs(const struct sk_buff * skb)
{
	lx_emul_trace_and_stop(__func__);
}


#include <net/tso.h>

int tso_start(struct sk_buff * skb,struct tso_t * tso)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/vt_kern.h>

void unblank_screen(void)
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


#include <linux/uuid.h>

const u8 uuid_index[16] = {};


#include <linux/vmalloc.h>

void vfree(const void * addr)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sched/wake_q.h>

void wake_q_add_safe(struct wake_q_head * head,struct task_struct * task)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/filter.h>

int xdp_do_generic_redirect(struct net_device * dev,struct sk_buff * skb,struct xdp_buff * xdp,struct bpf_prog * xdp_prog)
{
	lx_emul_trace_and_stop(__func__);
}

