/*
 * \brief  Linux emulation environment dummies
 * \author Stefan Kalkowski
 * \author Josef Soentgen
 * \date   2023-05-03
 */

/*
 * Copyright (C) 2023 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#include <lx_emul.h>

#include <linux/kernel_stat.h>

void account_process_tick(struct task_struct * p,int user_tick)
{
	lx_emul_trace(__func__);
}


#include <linux/tracepoint-defs.h>

const struct trace_print_flags gfpflag_names[]  = { {0,NULL}};
const struct trace_print_flags vmaflag_names[]  = { {0,NULL}};


u64 vabits_actual;
EXPORT_SYMBOL(vabits_actual);


struct ieee80211_hw;
struct cfg80211_wowlan;

extern int __ieee80211_suspend(struct ieee80211_hw * hw,struct cfg80211_wowlan * wowlan);
int __ieee80211_suspend(struct ieee80211_hw * hw,struct cfg80211_wowlan * wowlan)
{
	lx_emul_trace_and_stop(__func__);
}


#include <asm-generic/sections.h>

char __start_rodata[] = {};
char __end_rodata[]   = {};


#include <linux/srcutree.h>

void synchronize_srcu(struct srcu_struct * ssp)
{
	lx_emul_trace(__func__);
}


unsigned long __must_check __arch_copy_from_user(void *to, const void __user *from, unsigned long n);
unsigned long __must_check __arch_copy_from_user(void *to, const void __user *from, unsigned long n)
{
	memcpy(to, from, n);
	return 0;
}


unsigned long __must_check __arch_copy_to_user(void __user *to, const void *from, unsigned long n);
unsigned long __must_check __arch_copy_to_user(void __user *to, const void *from, unsigned long n)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/random.h>

u16 get_random_u16(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/filter.h>
#include <linux/jump_label.h> /* for DEFINE_STATIC_KEY_FALSE */

void bpf_prog_change_xdp(struct bpf_prog *prev_prog, struct bpf_prog *prog)
{
	lx_emul_trace(__func__);
}


DEFINE_STATIC_KEY_FALSE(bpf_master_redirect_enabled_key);
EXPORT_SYMBOL_GPL(bpf_master_redirect_enabled_key);

DEFINE_STATIC_KEY_FALSE(bpf_stats_enabled_key);
EXPORT_SYMBOL_GPL(bpf_stats_enabled_key);


u8 get_random_u8(void)
{
	lx_emul_trace_and_stop(__func__);
}


const u8 shipped_regdb_certs[] = { };
unsigned int shipped_regdb_certs_len = sizeof (shipped_regdb_certs);


#include <linux/rcutree.h>

void synchronize_rcu_expedited(void)
{
	lx_emul_trace(__func__);
}


#include <linux/leds.h>

int led_classdev_register_ext(struct device *parent,
                              struct led_classdev *led_cdev,
                              struct led_init_data *init_data)
{
	lx_emul_trace(__func__);
	return 0;
}


void led_classdev_unregister(struct led_classdev *led_cdev)
{
	lx_emul_trace_and_stop(__func__);
}


void led_trigger_event(struct led_trigger *trigger,  enum led_brightness event)
{
	lx_emul_trace(__func__);
}


void led_trigger_blink(struct led_trigger *trigger, unsigned long delay_on,
                       unsigned long delay_off)
{
	lx_emul_trace(__func__);
}


void led_trigger_blink_oneshot(struct led_trigger *trigger,
                               unsigned long delay_on,
                               unsigned long delay_off,
                               int invert)
{
	lx_emul_trace(__func__);
}


int led_trigger_register(struct led_trigger *trigger)
{
	lx_emul_trace(__func__);
	return 0;
}


void led_trigger_unregister(struct led_trigger *trigger)
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


#include <linux/proc_ns.h>

int proc_alloc_inum(unsigned int * inum)
{
	*inum = 1; /* according to linux/proc_ns.h without CONFIG_PROC_FS */
	return 0;
}


#include <linux/sched/signal.h>

void ignore_signals(struct task_struct * t)
{
	lx_emul_trace(__func__);
}


#include <linux/sysfs.h>

int sysfs_create_dir_ns(struct kobject * kobj,const void * ns)
{
	if (!kobj)
		return -EINVAL;

	kobj->sd = kzalloc(sizeof(*kobj->sd), GFP_KERNEL);
	return 0;
}


void sysfs_remove_dir(struct kobject * kobj)
{
	if (!kobj)
		return;

	kfree(kobj->sd);
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


void pm_runtime_init(struct device *dev)
{
	lx_emul_trace(__func__);
}


int pm_runtime_barrier(struct device *dev)
{
	lx_emul_trace(__func__);
	return 0;
}


int __pm_runtime_idle(struct device *dev, int rpmflags)
{
	return -ENOSYS;
}


int __pm_runtime_resume(struct device * dev,int rpmflags)
{
	lx_emul_trace(__func__);
	return 0;
}


void pm_runtime_set_memalloc_noio(struct device *dev,
                                  bool enable)
{
	lx_emul_trace(__func__);
}


void pm_runtime_remove(struct device *dev)
{
	lx_emul_trace(__func__);
}


void pm_runtime_put_suppliers(struct device *dev)
{
	lx_emul_trace(__func__);
}


int pm_generic_runtime_suspend(struct device *dev)
{
	lx_emul_trace(__func__);
	return 0;
}


int pm_generic_runtime_resume(struct device *dev)
{
	lx_emul_trace(__func__);
	return 0;
}


void pm_runtime_get_suppliers(struct device *dev)
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


#include <net/net_namespace.h>

__init int net_sysctl_init(void)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/ptp_classify.h>

void __init ptp_classifier_init(void)
{
	lx_emul_trace(__func__);
}


#include <linux/proc_fs.h>
#include <../fs/proc/internal.h>

struct proc_dir_entry * proc_create_net_data(const char * name,umode_t mode,struct proc_dir_entry * parent,const struct seq_operations * ops,unsigned int state_size,void * data)
{
	static struct proc_dir_entry ret;
	lx_emul_trace(__func__);
	return &ret;
}


#include <linux/fs.h>

unsigned int get_next_ino(void)
{
	static unsigned int count = 0;
	lx_emul_trace(__func__);
	return ++count;
}


extern int __init dev_proc_init(void);
int __init dev_proc_init(void)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/stringhash.h>

unsigned int full_name_hash(const void * salt,const char * name,unsigned int len)
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


#include <linux/sysfs.h>

int sysfs_create_group(struct kobject * kobj,const struct attribute_group * grp)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/random.h>

void add_device_randomness(const void * buf,size_t len)
{
	lx_emul_trace(__func__);
}


#include <linux/proc_fs.h>

struct proc_dir_entry * proc_create_seq_private(const char * name,umode_t mode,struct proc_dir_entry * parent,const struct seq_operations * ops,unsigned int state_size,void * data)
{
	static struct proc_dir_entry ret;
	lx_emul_trace(__func__);
	return &ret;
}


#include <linux/sysctl.h>

void __register_sysctl_init(const char *path, struct ctl_table *table,
                            const char *table_name, size_t table_size)
{
	lx_emul_trace(__func__);
}


#include <linux/syscore_ops.h>

void register_syscore_ops(struct syscore_ops * ops)
{
	lx_emul_trace(__func__);
}


#include <net/gen_stats.h>

void gnet_stats_basic_sync_init(struct gnet_stats_basic_sync * b)
{
	lx_emul_trace(__func__);
}


#include <linux/sysfs.h>

int sysfs_add_file_to_group(struct kobject * kobj,const struct attribute * attr,const char * group)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/key.h>

struct key * keyring_alloc(const char * description,kuid_t uid,kgid_t gid,const struct cred * cred,key_perm_t perm,unsigned long flags,struct key_restriction * restrict_link,struct key * dest)
{
	static struct key ret;
	lx_emul_trace(__func__);
	return &ret;
}


#include <linux/verification.h>

int verify_pkcs7_signature(const void * data,size_t len,const void * raw_pkcs7,size_t pkcs7_len,struct key * trusted_keys,enum key_being_used_for usage,int (* view_content)(void * ctx,const void * data,size_t len,size_t asn1hdrlen),void * ctx)
{
	lx_emul_trace(__func__);
	return 1;
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


#include <linux/kernel.h>

bool parse_option_str(const char * str,const char * option)
{
	lx_emul_trace(__func__);
	return false;
}


#include <linux/pinctrl/devinfo.h>

int pinctrl_bind_pins(struct device * dev)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/pci.h>

int pcim_iomap_regions(struct pci_dev * pdev,int mask,const char * name)
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


#include <net/cfg80211.h>

void wiphy_read_of_freq_limits(struct wiphy * wiphy)
{
	lx_emul_trace(__func__);
}


#include <linux/moduleparam.h>

void kernel_param_lock(struct module * mod)
{
	lx_emul_trace(__func__);
}


#include <linux/moduleparam.h>

void kernel_param_unlock(struct module * mod)
{
	lx_emul_trace(__func__);
}


#include <linux/inetdevice.h>

int register_inetaddr_notifier(struct notifier_block * nb)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <net/addrconf.h>

int register_inet6addr_notifier(struct notifier_block * nb)
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


#include <linux/sysfs.h>

void sysfs_remove_file_ns(struct kobject * kobj,const struct attribute * attr,const void * ns)
{
	lx_emul_trace(__func__);
}


#include <asm-generic/softirq_stack.h>

void do_softirq_own_stack(void)
{
	__do_softirq();
}


#include <linux/pid.h>

pid_t pid_vnr(struct pid * pid)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/filter.h>

int sk_filter_trim_cap(struct sock * sk,struct sk_buff * skb,unsigned int cap)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/pid.h>

void put_pid(struct pid * pid)
{
	lx_emul_trace(__func__);
}


#include <linux/capability.h>

bool ns_capable(struct user_namespace * ns,int cap)
{
	lx_emul_trace(__func__);
	return 1;
}


#include <linux/capability.h>

bool file_ns_capable(const struct file * file,struct user_namespace * ns,int cap)
{
	lx_emul_trace(__func__);
	return true;
}


#include <linux/rcupdate.h>

void synchronize_rcu(void)
{
	lx_emul_trace(__func__);
}


#include <linux/pci.h>

int pci_disable_link_state(struct pci_dev * pdev,int state)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/pci.h>

int pci_enable_msi(struct pci_dev * dev)
{
	lx_emul_trace(__func__);
	return -ENOSYS;
}


#include <linux/pci.h>

int pcie_capability_read_word(struct pci_dev * dev,int pos,u16 * val)
{
	lx_emul_trace(__func__);
	return -1;
}


#include <linux/context_tracking_irq.h>

noinstr void ct_irq_enter(void)
{
	lx_emul_trace(__func__);
}


#include <linux/random.h>

void add_interrupt_randomness(int irq)
{
	lx_emul_trace(__func__);
}


#include <linux/context_tracking_irq.h>

noinstr void ct_irq_exit(void)
{
	lx_emul_trace(__func__);
}


#include <linux/skbuff.h>

void __skb_get_hash(struct sk_buff * skb)
{
	lx_emul_trace(__func__);
}


#include <linux/skbuff.h>

bool __skb_flow_dissect(const struct net * net,const struct sk_buff * skb,struct flow_dissector * flow_dissector,void * target_container,const void * data,__be16 proto,int nhoff,int hlen,unsigned int flags)
{
	lx_emul_trace(__func__);
	return false;
}


#include <crypto/algapi.h>

/*
 * For the moment implement here as the it will otherwise clash with
 * older kernel versions, 5.14.x on the PinePhone, where it is implmented
 * in 'crypto/algapi.c.
 */
void __crypto_xor(u8 *dst, const u8 *src1, const u8 *src2, unsigned int len)
{
	while (len--)
		*dst++ = *src1++ ^ *src2++;
}


/*
 * AFAICT this function can be a NOP as its intended purpose [1]
 * is not there in our case.
 *
 * [1] "This function is called when a page has been modified by the kernel.
 *      Mark it as dirty for later flushing when mapped in user space [...]"
 *      -- arm64/mm/flush.c
 *
 */
extern void flush_dcache_page(struct page * page);
void flush_dcache_page(struct page * page)
{
	lx_emul_trace(__func__);
}


#include <linux/mnt_idmapping.h>

struct mnt_idmap { int dummy; };
struct mnt_idmap nop_mnt_idmap;


#include <linux/fs.h>

void inode_init_once(struct inode * inode)
{
	lx_emul_trace(__func__);
}


#include <linux/of_reserved_mem.h>
#include <linux/mod_devicetable.h>

const struct of_device_id __reservedmem_of_table[] = {};


#include <linux/kernfs.h>

struct kernfs_node * kernfs_find_and_get_ns(struct kernfs_node * parent,const char * name, const void * ns)
{
	static struct kernfs_node _node;
	lx_emul_trace(__func__);
	return &_node;
}


#include <linux/kernfs.h>

void kernfs_put(struct kernfs_node * kn)
{
	lx_emul_trace(__func__);
}


#include <linux/sysfs.h>

int sysfs_create_bin_file(struct kobject * kobj,const struct bin_attribute * attr)
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

int sysfs_emit(char * buf,const char * fmt,...)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/sysfs.h>

int sysfs_emit_at(char * buf,int at,const char * fmt,...)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/sysfs.h>

void sysfs_remove_group(struct kobject * kobj,const struct attribute_group * grp)
{
	lx_emul_trace(__func__);
}


#include <linux/sysfs.h>

void sysfs_remove_groups(struct kobject * kobj,const struct attribute_group ** groups)
{
	lx_emul_trace(__func__);
}


#include <linux/sysfs.h>

void sysfs_remove_link(struct kobject * kobj,const char * name)
{
	lx_emul_trace(__func__);
}


#include <linux/sysfs.h>

int sysfs_rename_dir_ns(struct kobject * kobj,const char * new_name,const void * new_ns)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/sysfs.h>

int sysfs_rename_link_ns(struct kobject * kobj,struct kobject * targ,const char * old,const char * new,const void * new_ns)
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


#include <linux/logic_pio.h>

struct logic_pio_hwaddr * find_io_range_by_fwnode(struct fwnode_handle * fwnode)
{
	lx_emul_trace(__func__);
	return NULL;
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


#include <linux/pm_domain.h>

int dev_pm_domain_attach(struct device * dev,bool power_on)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/pm_domain.h>

void dev_pm_domain_detach(struct device * dev,bool power_off)
{
	lx_emul_trace(__func__);
}


#include <linux/pm_runtime.h>

void pm_runtime_drop_link(struct device_link * link)
{
	lx_emul_trace(__func__);
}


#include <linux/pm_runtime.h>

void pm_runtime_enable(struct device * dev)
{
	lx_emul_trace(__func__);
}


#include <linux/pm_runtime.h>

void pm_runtime_new_link(struct device * dev)
{
	lx_emul_trace(__func__);
}


extern void pm_runtime_reinit(struct device * dev);
void pm_runtime_reinit(struct device * dev)
{
	lx_emul_trace(__func__);
}


#include <linux/pm_runtime.h>

void pm_runtime_release_supplier(struct device_link * link)
{
	lx_emul_trace(__func__);
}


#include <linux/pm_runtime.h>

void pm_runtime_set_autosuspend_delay(struct device * dev,int delay)
{
	lx_emul_trace(__func__);
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


#include <linux/pinctrl/consumer.h>

int pinctrl_select_default_state(struct device * dev)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/pinctrl/consumer.h>

int pinctrl_select_state(struct pinctrl * p,struct pinctrl_state * state)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/gpio/consumer.h>

struct gpio_desc * __must_check devm_gpiod_get_index(struct device * dev,const char * con_id,unsigned int idx,enum gpiod_flags flags)
{
	lx_emul_trace(__func__);
	return NULL;
}


#include <linux/regulator/consumer.h>

int regulator_count_voltages(struct regulator * regulator)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/regulator/consumer.h>

int regulator_disable(struct regulator * regulator)
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

static int vmmc_regulator;

struct regulator * devm_regulator_get_optional(struct device * dev,const char * id)
{
	if (strcmp(id, "vqmmc") == 0)
		return ERR_PTR(-ENOSYS);

	if (strcmp(id, "vmmc") == 0)
		return (struct regulator*)&vmmc_regulator;

	return NULL;
}


int regulator_get_voltage(struct regulator * regulator)
{
	if (regulator == (struct regulator *)&vmmc_regulator)
		return 3300000;

	return 0;
}


#include <linux/regulator/consumer.h>

int regulator_set_voltage(struct regulator * regulator,int min_uV,int max_uV)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/leds.h>

void led_trigger_register_simple(const char * name,struct led_trigger ** tp)
{
	lx_emul_trace(__func__);
}


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


extern void dpm_sysfs_remove(struct device * dev);
void dpm_sysfs_remove(struct device * dev)
{
	lx_emul_trace(__func__);
}


extern void software_node_notify_remove(struct device * dev);
void software_node_notify_remove(struct device * dev)
{
	lx_emul_trace(__func__);
}


#include <linux/ratelimit_types.h>

int ___ratelimit(struct ratelimit_state * rs,const char * func)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/nvmem-consumer.h>

struct nvmem_cell * devm_nvmem_cell_get(struct device * dev,const char * id)
{
	lx_emul_trace(__func__);
	return NULL;
}


#include <linux/nvmem-consumer.h>

void * nvmem_cell_read(struct nvmem_cell * cell,size_t * len)
{
	lx_emul_trace(__func__);
	return NULL;
}


struct cpu_topology cpu_topology[NR_CPUS];
EXPORT_SYMBOL_GPL(cpu_topology);


#include <linux/proc_fs.h>

struct proc_dir_entry *proc_mkdir(const char *name, struct proc_dir_entry *parent)
{
	lx_emul_trace(__func__);
	return NULL;
}


#include <linux/proc_fs.h>

void remove_proc_entry(const char *, struct proc_dir_entry *)
{
	lx_emul_trace(__func__);
}


#include <net/addrconf.h>

int unregister_inet6addr_notifier(struct notifier_block * nb)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/inetdevice.h>

int unregister_inetaddr_notifier(struct notifier_block * nb)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <net/gen_stats.h>

void gen_kill_estimator(struct net_rate_estimator __rcu ** rate_est)
{
	lx_emul_trace(__func__);
}


#include <linux/rcutree.h>

void rcu_barrier(void)
{
	lx_emul_trace(__func__);
}


#include <linux/leds.h>

void led_trigger_unregister_simple(struct led_trigger * trig)
{
	lx_emul_trace(__func__);
}
