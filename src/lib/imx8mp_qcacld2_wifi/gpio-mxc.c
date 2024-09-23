/*
 * \brief  Stub variant of the Linux Kernel's i.MX GPIO driver
 * \author Josef Soentgen
 * \date   2024-05-30
 */

/*
 * Copyright (C) 2024 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#include <linux/module.h>
#include <linux/gpio/driver.h>
#include <linux/platform_device.h>


extern bool lx_emul_ccm_probed;


static const struct of_device_id mxc_gpio_dt_ids[] = {
	{ .compatible = "fsl,imx8mp-gpio" },
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, mxc_gpio_dt_ids);

static int mxc_gpio_probe(struct platform_device *pdev)
{
	if (!lx_emul_ccm_probed)
		return -EPROBE_DEFER;

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
