/*
 * \brief  Dummy platform drivers for driver-supplier matching
 * \author Sebastian Sumpf
 * \date   2024-09-05
 */

/*
 * Copyright (C) 2024 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#include <linux/of.h>
#include <linux/platform_device.h>


static bool ccm_probed = false;

/*
 * GPCv2
 */
static int imx_gpcv2_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *pgc_np;

	pgc_np = of_get_child_by_name(dev->of_node, "pgc");
	if (!pgc_np) {
		printk("No power domains specified in DT\n");
		return -EINVAL;
	}

	/*
	 * On imx8mp gpcv2 has to wait for the probing  of "imxm8p-ccm" below because
	 * it is linked (fw/of) as proxy-supplier (SYNC_STATE_ONLY) for its children.
	 * Otherwise the following message will appear for all children: "imx-gpcv2
	 * 303a0000.gpc: Failed to create device link (0x180) with
	 * 30380000.clock-controller" which are quite a few.
	 */
	if (!ccm_probed && of_device_is_compatible(dev->of_node, "fsl,imx8mp-gpc"))
		return -EPROBE_DEFER;

	return 0;
}


static const struct of_device_id imx_gpcv2_dt_ids[] = {
	{ .compatible = "fsl,imx8mp-gpc" },
	{ .compatible = "fsl,imx8mq-gpc" },
	{ }
};


static struct platform_driver imx_gpc_driver = {
	.driver = {
		.name = "imx-gpcv2",
		.of_match_table = imx_gpcv2_dt_ids,
	},
	.probe = imx_gpcv2_probe,
};

builtin_platform_driver(imx_gpc_driver)


/*
 * Pincontrol
 */
static int imx8mp_probe_pinctrl(struct platform_device *pdev)
{
	return 0;
};


static const struct of_device_id imx8mp_pinctrl_dt_ids[] = {
	{ .compatible = "fsl,imx8mp-iomuxc", },
	{ }
};


static struct platform_driver imx8mp_pinctrl_driver = {
	.driver = {
		.name = "imx8mp-pinctrl",
		.of_match_table = imx8mp_pinctrl_dt_ids,
	},
	.probe = imx8mp_probe_pinctrl
};


static int __init imx8mp_pinctrl_init(void)
{
	return platform_driver_register(&imx8mp_pinctrl_driver);
}

arch_initcall(imx8mp_pinctrl_init);


/*
 * Clock driver
 */
static int imx8mp_probe_ccm(struct platform_device *pdev)
{
	ccm_probed = true;
	return 0;
};


static const struct of_device_id imx8mp_clk_dt_ids[] = {
	{ .compatible = "fsl,imx8mp-ccm" },
	{  }
};


static struct platform_driver imx8mp_clk_driver = {
	.probe = imx8mp_probe_ccm,
	.driver = {
		.name = "imx8mp-ccm",
		.of_match_table = imx8mp_clk_dt_ids,
	},
};

builtin_platform_driver(imx8mp_clk_driver);
