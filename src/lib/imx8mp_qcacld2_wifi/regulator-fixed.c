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
#include <linux/platform_device.h>
#include <linux/of.h>

extern bool lx_emul_ccm_probed;


static int reg_fixed_voltage_probe(struct platform_device *pdev)
{
	if (!lx_emul_ccm_probed)
		return -EPROBE_DEFER;

	return 0;
}

static const struct of_device_id fixed_of_match[] = {
	{ .compatible = "regulator-fixed" },
	{ /* sentinel */ },
};
MODULE_DEVICE_TABLE(of, fixed_of_match);

static struct platform_driver regulator_fixed_voltage_driver = {
	.probe		= reg_fixed_voltage_probe,
	.driver		= {
		.name		= "reg-fixed-voltage",
		.of_match_table = of_match_ptr(fixed_of_match),
	},
};

static int __init regulator_fixed_voltage_init(void)
{
	return platform_driver_register(&regulator_fixed_voltage_driver);
}
subsys_initcall(regulator_fixed_voltage_init);
