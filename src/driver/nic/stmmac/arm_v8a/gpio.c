// SPDX-License-Identifier: GPL-2.0+
//
// MXC GPIO support. (c) 2008 Daniel Mack <daniel@caiaq.de>
// Copyright 2008 Juergen Beisert, kernel@pengutronix.de
//
// Based on code from Freescale Semiconductor,
// Authors: Daniel Mack, Juergen Beisert.
// Copyright (C) 2004-2010 Freescale Semiconductor, Inc. All Rights Reserved.

#include <linux/clk.h>
#include <linux/err.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/irq.h>
#include <linux/irqdomain.h>
#include <linux/irqchip/chained_irq.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/spinlock.h>
#include <linux/syscore_ops.h>
#include <linux/gpio/driver.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/bug.h>

static const struct of_device_id mxc_gpio_dt_ids[] = {
	{ .compatible = "fsl,imx35-gpio" },
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, mxc_gpio_dt_ids);


static int mxc_gpio_probe(struct platform_device *pdev)
{
	return 0;
}

static struct platform_driver mxc_gpio_driver = {
	.driver		= {
		.name	= "gpio-mxc",
		.of_match_table = mxc_gpio_dt_ids,
		.suppress_bind_attrs = true,
	},
	.probe		= mxc_gpio_probe,
};

static int __init gpio_mxc_init(void)
{
	return platform_driver_register(&mxc_gpio_driver);
}
subsys_initcall(gpio_mxc_init);

MODULE_AUTHOR("Shawn Guo <shawn.guo@linaro.org>");
MODULE_DESCRIPTION("i.MX GPIO Driver");
MODULE_LICENSE("GPL");
