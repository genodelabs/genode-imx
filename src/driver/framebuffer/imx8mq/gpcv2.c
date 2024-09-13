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
    { .compatible = "fsl,imx8mq-gpc", },
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
