/*
 * \brief  Stub variant of the Linux Kernel's fixed-clock driver
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


static int of_fixed_clk_probe(struct platform_device *pdev)
{
	return 0;
}


static const struct of_device_id of_fixed_clk_ids[] = {
	{ .compatible = "fixed-clock" },
	{ }
};


static struct platform_driver of_fixed_clk_driver = {
	.driver = {
		.name = "of_fixed_clk",
		.of_match_table = of_fixed_clk_ids,
	},
	.probe = of_fixed_clk_probe,
};
builtin_platform_driver(of_fixed_clk_driver);
