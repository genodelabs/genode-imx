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

	return 0;
}


static const struct of_device_id imx_gpcv2_dt_ids[] = {
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
