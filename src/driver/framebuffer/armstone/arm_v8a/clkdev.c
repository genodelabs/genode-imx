/*
 * \brief  Replaces drivers/clk/clkdev.c
 * \author Stefan Kalkowski
 * \date   2021-03-16
 */

/*
 * Copyright (C) 2021 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#include <linux/clk.h>
#include <linux/clkdev.h>
#include <linux/device.h>
#include <linux/clk-provider.h>
#include <lx_emul/clock.h>

struct clk {
	unsigned long rate;
};

static struct clk hdmi_phy;


struct clk *clk_get(struct device *dev, const char *con_id)
{
	struct clk * ret;

	if (!dev || !dev->of_node)
		return NULL;

	ret = lx_emul_clock_get(dev->of_node, con_id);

	if (!ret) {
		ret = (strcmp(con_id, "pix") == 0) ? &hdmi_phy : NULL;
		printk("For clock %s use %px\n", con_id, ret);
	}

	return ret ? ret : ERR_PTR(-ENOENT);
}


void clk_put(struct clk *clk) {}


struct clk * devm_clk_register(struct device * dev,struct clk_hw * hw)
{
	static unsigned counter = 0;
	if (counter++)
		printk("Error: %s should be called only once!\n", __func__);

	hw->clk = &hdmi_phy;
	return hw->clk;
}


int of_clk_add_provider(struct device_node * np,struct clk * (* clk_src_get)(struct of_phandle_args * clkspec,void * data),void * data)
{
	lx_emul_trace(__func__);
	return 0;
}


int __must_check clk_bulk_get(struct device * dev,int num_clks,struct clk_bulk_data * clks)
{
	int ret = 0;

	for (int i; i < num_clks; i++) {
		if (!lx_emul_clock_get(dev->of_node, clks[i].id))
			ret = -ENOENT;
	}

	return  ret;
}


int __must_check clk_bulk_prepare(int num_clks,const struct clk_bulk_data * clks)
{
	lx_emul_trace(__func__);
	return 0;
}


int __must_check clk_bulk_enable(int num_clks,const struct clk_bulk_data * clks)
{
	lx_emul_trace(__func__);
	return 0;
}


