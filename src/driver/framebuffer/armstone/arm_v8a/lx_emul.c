/*
 * \brief  Common definitions of Linux Kernel functions
 * \author Stefan Kalkowski
 * \date   2022-02-08
 */

/*
 * Copyright (C) 2021 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#include <asm/io.h>
#include <lx_emul/io_mem.h>

void __iomem * ioremap_prot(phys_addr_t phys_addr,size_t size,unsigned long prot)
{
	return lx_emul_io_mem_map(phys_addr, size);
}


#include <linux/mount.h>
#include <linux/fs.h>
#include <linux/slab.h>

struct vfsmount * kern_mount(struct file_system_type * type)
{
	struct vfsmount *m;

	m = kzalloc(sizeof (struct vfsmount), 0);
	if (!m) {
		return (struct vfsmount*)ERR_PTR(-ENOMEM);
	}

	return m;
}


#include <linux/random.h>
#include <lx_emul/random.h>

size_t __must_check get_random_bytes_arch(void *buf, size_t nbytes)
{
	if (nbytes < 0)
		return -1;

	lx_emul_random_gen_bytes(buf, nbytes);
	return nbytes;
}


void get_random_bytes(void *buf, size_t nbytes)
{
	nbytes = get_random_bytes_arch(buf, nbytes);
}


#include <linux/init.h>
#include <linux/mod_devicetable.h>
#include <linux/module.h>
#include <linux/platform_device.h>


//static const struct of_device_id imx_hdmiblk_of_match[] = {
//	{ .compatible = "fsl,imx8mp-hdmi-blk-ctrl", },
//	{ /* sentinel */ }
//};
//MODULE_DEVICE_TABLE(of, imx_hdmiblk_of_match);

//static struct platform_driver imx_blk_ctrl_driver = {
//	.driver = {
//		.name = "imx-hdmiblk",
//		.of_match_table = imx_hdmiblk_of_match,
//		.suppress_bind_attrs = true,
//	},
//	.probe = imx_probe,
//};
//module_platform_driver(imx_blk_ctrl_driver);

//struct imx8m_pm_domain {
//	struct device *dev;
//	struct generic_pm_domain pd;
//	u32 domain_index;
//	struct clk *clk[MAX_CLK_NUM];
//	unsigned int num_clks;
//	struct regulator *reg;
//};
//
//static int imx8m_pd_power_on(struct generic_pm_domain *genpd)
//{
//}
//
//static int imx_power_probe(struct platform_device *pdev)
//{
//	int ret;
//	struct device *dev = &pdev->dev;
//	struct device_node *np = dev->of_node;
//	struct of_phandle_args parent, child;
//	struct generic_pm_domain *pd = kmalloc(sizeof(struct generic_pm_domain), GFP_KERNEL);
//
//	pd->power_off = imx_pm_power_off;
//	pd->power_on  = imx_pm_power_on;
//	pm_genpd_init(pd, NULL, true);
//
//	ret = of_genpd_add_provider_simple(np, pd);
//		if (ret) {
//		dev_err(dev, "failed to add the domain provider\n");
//		pm_genpd_remove(pd);
//		return ret;
//	}
//
//	/* add it as subdomain if necessary */
//	if (!of_parse_phandle_with_args(np, "parent-domains",
//			"#power-domain-cells", 0, &parent)) {
//		ret = of_genpd_add_subdomain(&parent, &child);
//		of_node_put(parent.np);
//
//		if (ret < 0) {
//			dev_dbg(dev, "failed to add the subdomain: %s: %d",
//				domain->pd.name, ret);
//			of_genpd_del_provider(np);
//			pm_genpd_remove(&domain->pd);
//			imx8m_pd_put_clocks(domain);
//			return -EPROBE_DEFER;
//		}
//	}
//
//	return 0;
//}
//
//
//static const struct of_device_id imx8m_pm_domain_ids[] = {
//	{.compatible = "fsl,imx8m-pm-domain"},
//	{},
//};
//
//
//static struct platform_driver imx8m_pm_domain_driver = {
//	.driver = {
//		.name	= "imx8m_pm_domain",
//		.owner	= THIS_MODULE,
//		.of_match_table = imx8m_pm_domain_ids,
//	},
//	.probe = imx_power_probe,
//};
//module_platform_driver(imx8m_pm_domain_driver);


#include <linux/fs.h>

int simple_pin_fs(struct file_system_type * type,struct vfsmount ** mount,int * count)
{
	*mount = kzalloc(sizeof(struct vfsmount), GFP_KERNEL);
	return 0;
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
	memcpy(to, from, n);
	return 0;
}


#include <soc/imx/imx_sip.h>
#include <linux/arm-smccc.h>

extern void lx_emul_power_enable(const char *name);
extern void lx_emul_power_disable(const char *name);

asmlinkage void __arm_smccc_smc(unsigned long a0, unsigned long a1,
			unsigned long a2, unsigned long a3, unsigned long a4,
			unsigned long a5, unsigned long a6, unsigned long a7,
			struct arm_smccc_res *res, struct arm_smccc_quirk *quirk)
{
	if (a0 != IMX_SIP_GPC || a1 != IMX_SIP_CONFIG_GPC_PM_DOMAIN) {
		printk("Unknown SMC call!\n");
		lx_emul_trace_and_stop(__func__);
	}

	if (a2 == 17) {
		if (a3 == 0) lx_emul_power_disable("hdmimix");
		else         lx_emul_power_enable("hdmimix");
	}

	if (a2 == 18) {
		if (a3 == 0) lx_emul_power_disable("hdmi");
		else         lx_emul_power_enable("hdmi");
	}
}


struct workqueue_struct *pm_wq;
EXPORT_SYMBOL_GPL(pm_wq);

static int __init pm_start_workqueue(void)
{
	pm_wq = alloc_workqueue("pm", WQ_FREEZABLE, 0);

	return pm_wq ? 0 : -ENOMEM;
}

static int __init pm_init(void)
{
	return pm_start_workqueue();
}

core_initcall(pm_init);
