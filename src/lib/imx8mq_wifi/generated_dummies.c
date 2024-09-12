/*
 * \brief  Dummy definitions of Linux Kernel functions
 * \author Automatically generated file - do no edit
 * \date   2024-09-12
 */

#include <lx_emul.h>


#include <linux/ratelimit_types.h>

int ___ratelimit(struct ratelimit_state * rs,const char * func)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/cpumask.h>

struct cpumask __cpu_active_mask;


#include <linux/ethtool.h>

int __ethtool_get_link_ksettings(struct net_device * dev,struct ethtool_link_ksettings * link_ksettings)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sched.h>

char * __get_task_comm(char * buf,size_t buf_size,struct task_struct * tsk)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/of.h>

int __of_parse_phandle_with_args(const struct device_node * np,const char * list_name,const char * cells_name,int cell_count,int index,struct of_phandle_args * out_args)
{
	lx_emul_trace_and_stop(__func__);
}


#include <asm-generic/percpu.h>

unsigned long __per_cpu_offset[NR_CPUS] = {};


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


#include <linux/cred.h>

void __put_cred(struct cred * cred)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sched/task.h>

void __put_task_struct(struct task_struct * tsk)
{
	lx_emul_trace_and_stop(__func__);
}


#include <net/scm.h>

void __scm_destroy(struct scm_cookie * scm)
{
	lx_emul_trace_and_stop(__func__);
}


#include <net/scm.h>

int __scm_send(struct socket * sock,struct msghdr * msg,struct scm_cookie * p)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/mm.h>

void __show_mem(unsigned int filter,nodemask_t * nodemask,int max_zone_idx)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/skbuff.h>

u32 __skb_get_hash_symmetric(const struct sk_buff * skb)
{
	lx_emul_trace_and_stop(__func__);
}


#include <net/gso.h>

struct sk_buff * __skb_gso_segment(struct sk_buff * skb,netdev_features_t features,bool tx_path)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/printk.h>

int _printk_deferred(const char * fmt,...)
{
	lx_emul_trace_and_stop(__func__);
}


#include <crypto/arc4.h>

void arc4_crypt(struct arc4_ctx * ctx,u8 * out,const u8 * in,unsigned int len)
{
	lx_emul_trace_and_stop(__func__);
}


#include <crypto/arc4.h>

int arc4_setkey(struct arc4_ctx * ctx,const u8 * in_key,unsigned int key_len)
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


#include <linux/filter.h>

int bpf_prog_create_from_user(struct bpf_prog ** pfp,struct sock_fprog * fprog,bpf_aux_classic_check_t trans,bool save_orig)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/filter.h>

void bpf_prog_destroy(struct bpf_prog * fp)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/filter.h>

void bpf_warn_invalid_xdp_action(struct net_device * dev,struct bpf_prog * prog,u32 act)
{
	lx_emul_trace_and_stop(__func__);
}


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


#include <linux/filter.h>

int copy_bpf_fprog_from_user(struct sock_fprog * dst,sockptr_t src,int len)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/uio.h>

size_t copy_page_from_iter(struct page * page,size_t offset,size_t bytes,struct iov_iter * i)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/fs.h>

ssize_t copy_splice_read(struct file * in,loff_t * ppos,struct pipe_inode_info * pipe,size_t len,unsigned int flags)
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


#include <asm-generic/checksum.h>

__wsum csum_partial(const void * buff,int len,__wsum wsum)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/netdevice.h>

int dev_ifconf(struct net * net,struct ifconf __user * uifc)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/netdevice.h>

int dev_ioctl(struct net * net,unsigned int cmd,struct ifreq * ifr,void __user * data,bool * need_copyout)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/netdevice.h>

void dev_load(struct net * net,const char * name)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pm_domain.h>

int dev_pm_domain_attach(struct device * dev,bool power_on)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pm_domain.h>

void dev_pm_domain_detach(struct device * dev,bool power_off)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/property.h>

int device_create_managed_software_node(struct device * dev,const struct property_entry * properties,const struct software_node * parent)
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


#include <linux/dma-map-ops.h>

bool dma_default_coherent;


extern void dpm_sysfs_remove(struct device * dev);
void dpm_sysfs_remove(struct device * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <net/dst.h>

void dst_release(struct dst_entry * dst)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/printk.h>

asmlinkage __visible void dump_stack_lvl(const char * log_lvl)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/dcache.h>

char * dynamic_dname(char * buffer,int buflen,const char * fmt,...)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/reboot.h>

void emergency_restart(void)
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


#include <linux/fs.h>

pid_t f_getown(struct file * filp)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/fs.h>

int f_setown(struct file * filp,int who,int force)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/fs.h>

int fasync_helper(int fd,struct file * filp,int on,struct fasync_struct ** fapp)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sched.h>

struct task_struct * find_task_by_vpid(pid_t vnr)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/rcuwait.h>

void finish_rcuwait(struct rcuwait * w)
{
	lx_emul_trace_and_stop(__func__);
}


#include <net/flow_dissector.h>

struct flow_dissector flow_keys_basic_dissector;


#include <linux/gcd.h>

unsigned long gcd(unsigned long a,unsigned long b)
{
	lx_emul_trace_and_stop(__func__);
}


#include <net/gen_stats.h>

void gen_kill_estimator(struct net_rate_estimator __rcu ** rate_est)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kernel.h>

int get_option(char ** str,int * pint)
{
	lx_emul_trace_and_stop(__func__);
}


#include <crypto/gf128mul.h>

void gf128mul_4k_lle(be128 * a,const struct gf128mul_4k * t)
{
	lx_emul_trace_and_stop(__func__);
}


#include <crypto/gf128mul.h>

struct gf128mul_4k * gf128mul_init_4k_lle(const be128 * g)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/gfp.h>

bool gfp_pfmemalloc_allowed(gfp_t gfp_mask)
{
	lx_emul_trace_and_stop(__func__);
}


#include <net/gen_stats.h>

void gnet_stats_add_basic(struct gnet_stats_basic_sync * bstats,struct gnet_stats_basic_sync __percpu * cpu,struct gnet_stats_basic_sync * b,bool running)
{
	lx_emul_trace_and_stop(__func__);
}


#include <net/gen_stats.h>

void gnet_stats_add_queue(struct gnet_stats_queue * qstats,const struct gnet_stats_queue __percpu * cpu,const struct gnet_stats_queue * q)
{
	lx_emul_trace_and_stop(__func__);
}


#include <net/gen_stats.h>

int gnet_stats_copy_basic(struct gnet_dump * d,struct gnet_stats_basic_sync __percpu * cpu,struct gnet_stats_basic_sync * b,bool running)
{
	lx_emul_trace_and_stop(__func__);
}


#include <net/gen_stats.h>

int gnet_stats_copy_queue(struct gnet_dump * d,struct gnet_stats_queue __percpu * cpu_q,struct gnet_stats_queue * q,__u32 qlen)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/gpio.h>

void gpio_free(unsigned gpio)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/gpio.h>

int gpio_request_one(unsigned gpio,unsigned long flags,const char * label)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/gpio/consumer.h>

struct gpio_desc * gpio_to_desc(unsigned gpio)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/gpio/consumer.h>

int gpiod_get_raw_value(const struct gpio_desc * desc)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/gpio/consumer.h>

void gpiod_put(struct gpio_desc * desc)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/gpio/consumer.h>

void gpiod_set_raw_value(struct gpio_desc * desc,int value)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/gpio/consumer.h>

void gpiod_set_value_cansleep(struct gpio_desc * desc,int value)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/capability.h>

bool has_capability_noaudit(struct task_struct * t,int cap)
{
	lx_emul_trace_and_stop(__func__);
}


#include <net/inet_connection_sock.h>

int inet_csk_get_port(struct sock * sk,unsigned short snum)
{
	lx_emul_trace_and_stop(__func__);
}


#include <net/inet_common.h>

const struct proto_ops inet_dgram_ops;


#include <linux/utsname.h>

struct user_namespace init_user_ns;


#include <linux/utsname.h>

struct uts_namespace init_uts_ns;


#include <linux/init.h>

bool initcall_debug;


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


#include <linux/uio.h>

void iov_iter_advance(struct iov_iter * i,size_t size)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/uio.h>

void iov_iter_revert(struct iov_iter * i,size_t unroll)
{
	lx_emul_trace_and_stop(__func__);
}


#include <net/ip.h>

struct sk_buff * ip_check_defrag(struct net * net,struct sk_buff * skb,u32 user)
{
	lx_emul_trace_and_stop(__func__);
}


#include <net/ip.h>

void ip_send_check(struct iphdr * iph)
{
	lx_emul_trace_and_stop(__func__);
}


#include <net/ipv6.h>

bool ipv6_ext_hdr(u8 nexthdr)
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

key_ref_t key_create_or_update(key_ref_t keyring_ref,const char * type,const char * description,const void * payload,size_t plen,key_perm_t perm,unsigned long flags)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/key.h>

void key_put(struct key * key)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sched.h>

void kick_process(struct task_struct * p)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/fs.h>

void kill_anon_super(struct super_block * sb)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/fs.h>

void kill_fasync(struct fasync_struct ** fp,int sig,int band)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kmsg_dump.h>

void kmsg_dump(enum kmsg_dump_reason reason)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/delay.h>

unsigned long loops_per_jiffy;


#include <linux/delay.h>

unsigned long lpj_fine;


#include <linux/preempt.h>

void migrate_disable(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/preempt.h>

void migrate_enable(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/math64.h>

u64 mul_u64_u64_div_u64(u64 a,u64 b,u64 c)
{
	lx_emul_trace_and_stop(__func__);
}


#include <net/neighbour.h>

const struct nla_policy nda_policy[] = {};


#include <linux/net.h>

int net_ratelimit(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/netdevice.h>

void netdev_rss_key_fill(void * buffer,size_t len)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/irq.h>

struct irq_chip no_irq_chip;


#include <linux/irq.h>

void note_interrupt(struct irq_desc * desc,irqreturn_t action_ret)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/clk/clk-conf.h>

int of_clk_set_defaults(struct device_node * node,bool clk_supplier)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/of_device.h>

ssize_t of_device_modalias(struct device * dev,char * str,ssize_t len)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/of_device.h>

int of_dma_configure_id(struct device * dev,struct device_node * np,bool force_dma,const u32 * id)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/of.h>

struct property * of_find_property(const struct device_node * np,const char * name,int * lenp)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/of.h>

const struct fwnode_operations of_fwnode_ops;


#include <linux/of_net.h>

int of_get_mac_address(struct device_node * np,u8 * addr)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/of.h>

struct device_node * of_get_next_parent(struct device_node * node)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/of.h>

struct device_node * of_get_parent(const struct device_node * node)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/of_device.h>

const struct of_device_id * of_match_device(const struct of_device_id * matches,const struct device * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/of.h>

bool of_node_name_eq(const struct device_node * np,const char * name)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/of.h>

const char * of_prop_next_string(struct property * prop,const char * cur)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/of.h>

int of_property_match_string(const struct device_node * np,const char * propname,const char * string)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/of.h>

int of_property_read_string(const struct device_node * np,const char * propname,const char ** out_string)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/proc_fs.h>

int open_related_ns(struct ns_common * ns,struct ns_common * (* get_ns)(struct ns_common * ns))
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/highuid.h>

int overflowgid;


#include <linux/highuid.h>

int overflowuid;


#include <net/page_pool/types.h>

void page_pool_destroy(struct page_pool * pool)
{
	lx_emul_trace_and_stop(__func__);
}


#include <net/page_pool/types.h>

void page_pool_put_defragged_page(struct page_pool * pool,struct page * page,unsigned int dma_sync_size,bool allow_direct)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/reboot.h>

enum reboot_mode panic_reboot_mode;


#include <linux/blkdev.h>

const struct device_type part_type;


extern int pci_bridge_wait_for_secondary_bus(struct pci_dev * dev,char * reset_type);
int pci_bridge_wait_for_secondary_bus(struct pci_dev * dev,char * reset_type)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

void pci_disable_device(struct pci_dev * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

void pci_disable_msi(struct pci_dev * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

int pci_enable_msix_range(struct pci_dev * dev,struct msix_entry * entries,int minvec,int maxvec)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

int pci_enable_wake(struct pci_dev * pci_dev,pci_power_t state,bool enable)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

u16 pci_find_ext_capability(struct pci_dev * dev,int cap)
{
	lx_emul_trace_and_stop(__func__);
}


extern int pci_finish_runtime_suspend(struct pci_dev * dev);
int pci_finish_runtime_suspend(struct pci_dev * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

void pci_fixup_device(enum pci_fixup_pass pass,struct pci_dev * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <asm-generic/pci_iomap.h>

void pci_iounmap(struct pci_dev * dev,void __iomem * p)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

void pci_lock_rescan_remove(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

bool pci_pme_capable(struct pci_dev * dev,pci_power_t state)
{
	lx_emul_trace_and_stop(__func__);
}


extern void pci_pme_restore(struct pci_dev * dev);
void pci_pme_restore(struct pci_dev * dev)
{
	lx_emul_trace_and_stop(__func__);
}


extern int pci_power_up(struct pci_dev * dev);
int pci_power_up(struct pci_dev * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

unsigned int pci_rescan_bus(struct pci_bus * bus)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

void pci_restore_state(struct pci_dev * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

void pci_resume_bus(struct pci_bus * bus)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

int pci_save_state(struct pci_dev * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

void pci_stop_and_remove_bus_device(struct pci_dev * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

void pci_unlock_rescan_remove(void)
{
	lx_emul_trace_and_stop(__func__);
}


extern void pci_update_current_state(struct pci_dev * dev,pci_power_t state);
void pci_update_current_state(struct pci_dev * dev,pci_power_t state)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

void pci_walk_bus(struct pci_bus * top,int (* cb)(struct pci_dev *,void *),void * userdata)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

int pci_write_config_word(const struct pci_dev * dev,int where,u16 val)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

int pcie_capability_clear_and_set_word_locked(struct pci_dev * dev,int pos,u16 clear,u16 set)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pm_runtime.h>

void pm_runtime_drop_link(struct device_link * link)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pm_runtime.h>

void pm_runtime_new_link(struct device * dev)
{
	lx_emul_trace_and_stop(__func__);
}


extern void pm_runtime_reinit(struct device * dev);
void pm_runtime_reinit(struct device * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pm_runtime.h>

void pm_runtime_release_supplier(struct device_link * link)
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


#include <linux/proc_ns.h>

void proc_free_inum(unsigned int inum)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/ptp_clock_kernel.h>

int ptp_clock_index(struct ptp_clock * ptp)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/ptp_clock_kernel.h>

struct ptp_clock * ptp_clock_register(struct ptp_clock_info * info,struct device * parent)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/ptp_clock_kernel.h>

int ptp_clock_unregister(struct ptp_clock * ptp)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/ptp_clock_kernel.h>

ktime_t ptp_convert_timestamp(const ktime_t * hwtstamp,int vclock_index)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/ptp_clock_kernel.h>

int ptp_get_vclocks_index(int pclock_index,int ** vclock_index)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/socket.h>

int put_cmsg(struct msghdr * msg,int level,int type,int len,void * data)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/socket.h>

void put_cmsg_scm_timestamping(struct msghdr * msg,struct scm_timestamping_internal * tss_internal)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/socket.h>

void put_cmsg_scm_timestamping64(struct msghdr * msg,struct scm_timestamping_internal * tss_internal)
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


#include <linux/rcuref.h>

bool rcuref_get_slowpath(rcuref_t * ref)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/reboot.h>

enum reboot_mode reboot_mode;


#include <linux/proc_fs.h>

void remove_proc_entry(const char * name,struct proc_dir_entry * parent)
{
	lx_emul_trace_and_stop(__func__);
}


#include <net/sock_reuseport.h>

int reuseport_detach_prog(struct sock * sk)
{
	lx_emul_trace_and_stop(__func__);
}


#include <net/sock_reuseport.h>

void reuseport_detach_sock(struct sock * sk)
{
	lx_emul_trace_and_stop(__func__);
}


#include <net/sock_reuseport.h>

void reuseport_update_incoming_cpu(struct sock * sk,int val)
{
	lx_emul_trace_and_stop(__func__);
}


#include <net/scm.h>

void scm_detach_fds(struct msghdr * msg,struct scm_cookie * scm)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/seq_file.h>

struct hlist_node * seq_hlist_next_rcu(void * v,struct hlist_head * head,loff_t * ppos)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/seq_file.h>

struct hlist_node * seq_hlist_start_head_rcu(struct hlist_head * head,loff_t pos)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/seq_file.h>

struct list_head * seq_list_next(void * v,struct list_head * head,loff_t * ppos)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/seq_file.h>

struct list_head * seq_list_start(struct list_head * head,loff_t pos)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/seq_file.h>

struct list_head * seq_list_start_head(struct list_head * head,loff_t pos)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/seq_file.h>

void seq_printf(struct seq_file * m,const char * f,...)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/seq_file.h>

void seq_putc(struct seq_file * m,char c)
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


#include <crypto/sha2.h>

void sha224_final(struct sha256_state * sctx,u8 * out)
{
	lx_emul_trace_and_stop(__func__);
}


#include <crypto/sha2.h>

void sha256_final(struct sha256_state * sctx,u8 * out)
{
	lx_emul_trace_and_stop(__func__);
}


#include <crypto/sha2.h>

void sha256_update(struct sha256_state * sctx,const u8 * data,unsigned int len)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sched/debug.h>

void show_state_filter(unsigned int state_filter)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/fs.h>

int simple_setattr(struct mnt_idmap * idmap,struct dentry * dentry,struct iattr * iattr)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/fs.h>

int simple_statfs(struct dentry * dentry,struct kstatfs * buf)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/filter.h>

int sk_attach_bpf(u32 ufd,struct sock * sk)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/filter.h>

int sk_attach_filter(struct sock_fprog * fprog,struct sock * sk)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/filter.h>

int sk_detach_filter(struct sock * sk)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/filter.h>

void sk_filter_uncharge(struct sock * sk,struct sk_filter * fp)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/filter.h>

int sk_reuseport_attach_bpf(u32 ufd,struct sock * sk)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/filter.h>

int sk_reuseport_attach_filter(struct sock_fprog * fprog,struct sock * sk)
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


#include <linux/sock_diag.h>

void sock_diag_broadcast_destroy(struct sock * sk)
{
	lx_emul_trace_and_stop(__func__);
}


#include <net/sock.h>

void sock_edemux(struct sk_buff * skb)
{
	lx_emul_trace_and_stop(__func__);
}


extern void software_node_notify_remove(struct device * dev);
void software_node_notify_remove(struct device * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/splice.h>

ssize_t splice_to_socket(struct pipe_inode_info * pipe,struct file * out,loff_t * ppos,size_t len,unsigned int flags)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/jump_label.h>

bool static_key_initialized;


#include <linux/fs.h>

int stream_open(struct inode * inode,struct file * filp)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/printk.h>

int suppress_printk;


#include <linux/sysctl.h>

const int sysctl_vals[] = {};


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

void sysfs_remove_bin_file(struct kobject * kobj,const struct bin_attribute * attr)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sysfs.h>

void sysfs_remove_group(struct kobject * kobj,const struct attribute_group * grp)
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


#include <linux/tcp.h>

struct sk_buff * tcp_get_timestamping_opt_stats(const struct sock * sk,const struct sk_buff * orig_skb,const struct sk_buff * ack_skb)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/thermal.h>

struct thermal_cooling_device * thermal_cooling_device_register(const char * type,void * devdata,const struct thermal_cooling_device_ops * ops)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/thermal.h>

void thermal_cooling_device_unregister(struct thermal_cooling_device * cdev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/thermal.h>

int thermal_zone_device_enable(struct thermal_zone_device * tz)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/thermal.h>

void * thermal_zone_device_priv(struct thermal_zone_device * tzd)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/thermal.h>

struct thermal_zone_device * thermal_zone_device_register_with_trips(const char * type,struct thermal_trip * trips,int num_trips,int mask,void * devdata,struct thermal_zone_device_ops * ops,const struct thermal_zone_params * tzp,int passive_delay,int polling_delay)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/thermal.h>

void thermal_zone_device_unregister(struct thermal_zone_device * tz)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/thermal.h>

void thermal_zone_device_update(struct thermal_zone_device * tz,enum thermal_notify_event event)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/clockchips.h>

void tick_broadcast(const struct cpumask * mask)
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

int tso_start(struct sk_buff * skb,struct tso_t * tso)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/fs.h>

int unregister_filesystem(struct file_system_type * fs)
{
	lx_emul_trace_and_stop(__func__);
}


extern void unregister_handler_proc(unsigned int irq,struct irqaction * action);
void unregister_handler_proc(unsigned int irq,struct irqaction * action)
{
	lx_emul_trace_and_stop(__func__);
}


#include <net/addrconf.h>

int unregister_inet6addr_notifier(struct notifier_block * nb)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/inetdevice.h>

int unregister_inetaddr_notifier(struct notifier_block * nb)
{
	lx_emul_trace_and_stop(__func__);
}


extern void update_group_capacity(struct sched_domain * sd,int cpu);
void update_group_capacity(struct sched_domain * sd,int cpu)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/vmalloc.h>

void vfree_atomic(const void * addr)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/mm.h>

int vm_insert_page(struct vm_area_struct * vma,unsigned long addr,struct page * page)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/mm.h>

struct page * vmalloc_to_page(const void * vmalloc_addr)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/filter.h>

int xdp_do_generic_redirect(struct net_device * dev,struct sk_buff * skb,struct xdp_buff * xdp,struct bpf_prog * xdp_prog)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/filter.h>

u32 xdp_master_redirect(struct xdp_buff * xdp)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sched.h>

void __sched yield(void)
{
	lx_emul_trace_and_stop(__func__);
}

