/*
 * \brief  Stripped down dummy variant of i.MX pinctrl driver
 * \author Stefan Kalkowski
 * \date   2024-09-10
 */

// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2016 Freescale Semiconductor, Inc.
 * Copyright 2017-2018 NXP
 * Copyright (C) 2018 Pengutronix, Lucas Stach <kernel@pengutronix.de>
 */

#include <linux/err.h>
#include <linux/init.h>
#include <linux/io.h>
#include <linux/mod_devicetable.h>
#include <linux/module.h>
#include <linux/pinctrl/pinctrl.h>
#include <linux/platform_device.h>


static const struct of_device_id imx_pinctrl_of_match[] = {
	{ .compatible = "fsl,imx8mq-iomuxc", },
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, imx_pinctrl_of_match);

static int imx_pinctrl_probe(struct platform_device *pdev)
{
	return 0;
}

static struct platform_driver imx_pinctrl_driver = {
	.driver = {
		.name = "imx-pinctrl",
		.of_match_table = imx_pinctrl_of_match,
		.suppress_bind_attrs = true,
	},
	.probe = imx_pinctrl_probe,
};

static int __init imx8mq_pinctrl_init(void)
{
	return platform_driver_register(&imx_pinctrl_driver);
}
arch_initcall(imx8mq_pinctrl_init);
