/*
 * \brief  Stub variant of the Linux Kernel' i.MX GPCv2 driver
 * \author Josef Soentgen
 * \date   2024-09-20
 */

/*
 * Copyright (C) 2024 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */


#include <linux/of.h>
#include <linux/platform_device.h>


static int imx_gpcv2_probe(struct platform_device *pdev)
{
	return 0;
}


static const struct of_device_id imx_gpcv2_dt_ids[] = {
    { .compatible = "fsl,imx8mp-gpc", },
    { /* sentinel */ }
};


static struct platform_driver imx_gpc_driver = {
    .driver = {
        .name = "imx-gpcv2",
        .of_match_table = imx_gpcv2_dt_ids,
    },
    .probe = imx_gpcv2_probe,
};


builtin_platform_driver(imx_gpc_driver)


extern bool driver_deferred_probe_enable;

bool lx_emul_ccm_probed;

/*
 * Clock driver
 */
static int imx8mp_probe_ccm(struct platform_device *pdev)
{
	lx_emul_ccm_probed = true;

	/*
	 * Normally deferred probing will be enabled via a late initcall
	 * after all normal initcalls were executed. However, due to the
	 * way we initialize the qcacld2 module, we do not reach the
	 * late stage in the first place as we depend on supplier that
	 * are already part of the deferred list (such as GPIO and
	 * regulator-fixed).
	 *
	 * By enabling deferred probing here we instruct the kernel
	 * to process the deferred list after the CCM has been bound.
	 */
	driver_deferred_probe_enable = true;
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
