/*
 * \brief  Stripped down dummy variant of i.MX eFuse driver to only return MAC addresses
 * \author Stefan Kalkowski
 * \date   2024-06-04
 */

// SPDX-License-Identifier: GPL-2.0-only
/*
 * i.MX6 OCOTP fusebox driver
 *
 * Copyright (c) 2015 Pengutronix, Philipp Zabel <p.zabel@pengutronix.de>
 *
 * Copyright 2019 NXP
 *
 * Based on the barebox ocotp driver,
 * Copyright (c) 2010 Baruch Siach <baruch@tkos.co.il>,
 *	Orex Computed Radiography
 *
 * Write support based on the fsl_otp driver,
 * Copyright (C) 2010-2013 Freescale Semiconductor, Inc
 */

#include <linux/clk.h>
#include <linux/device.h>
#include <linux/io.h>
#include <linux/module.h>
#include <linux/nvmem-provider.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/delay.h>

#include <lx_emul.h>

struct ocotp_priv {
	struct device *dev;
	const struct ocotp_params *params;
	struct nvmem_config *config;
};

struct ocotp_params {
	unsigned int nregs;
	unsigned int bank_address_words;
	bool reverse_mac_address;
};

static int imx_ocotp_read(void *context, unsigned int offset,
			  void *val, size_t bytes)
{
	return 0;
}

static int imx_ocotp_cell_pp(void *context, const char *id, int index,
                             unsigned int offset, void *data, size_t bytes)
{
	/* Deal with some post processing of nvmem cell data */
	if (id && !strcmp(id, "mac-address")) {
		lx_emul_get_mac_address(data);
	}

	return 0;
}

static void imx_ocotp_fixup_cell_info(struct nvmem_device *nvmem,
                                     struct nvmem_layout *layout,
                                     struct nvmem_cell_info *cell)
{
	cell->read_post_process = imx_ocotp_cell_pp;
}

static struct nvmem_layout imx_ocotp_layout = {
	.fixup_cell_info = imx_ocotp_fixup_cell_info,
};

static int imx_ocotp_write(void *context, unsigned int offset, void *val,
			   size_t bytes)
{
	return 0;
}

static struct nvmem_config imx_ocotp_nvmem_config = {
	.name = "imx-ocotp",
	.read_only = false,
	.word_size = 4,
	.stride = 1,
	.reg_read = imx_ocotp_read,
	.reg_write = imx_ocotp_write,
};

static const struct ocotp_params imx8mp_params = {
	.nregs = 384,
	.bank_address_words = 0,
	.reverse_mac_address = true,
};

static const struct of_device_id imx_ocotp_dt_ids[] = {
	{ .compatible = "fsl,imx8mp-ocotp", .data = &imx8mp_params },
	{ },
};
MODULE_DEVICE_TABLE(of, imx_ocotp_dt_ids);

static int imx_ocotp_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct ocotp_priv *priv;
	struct nvmem_device *nvmem;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->dev = dev;

	priv->params = of_device_get_match_data(&pdev->dev);
	imx_ocotp_nvmem_config.add_legacy_fixed_of_cells = true;
	imx_ocotp_nvmem_config.size = 4 * priv->params->nregs;
	imx_ocotp_nvmem_config.dev = dev;
	imx_ocotp_nvmem_config.priv = priv;
	imx_ocotp_nvmem_config.layout = &imx_ocotp_layout;
	priv->config = &imx_ocotp_nvmem_config;

	nvmem = devm_nvmem_register(dev, &imx_ocotp_nvmem_config);

	return PTR_ERR_OR_ZERO(nvmem);
}

static struct platform_driver imx_ocotp_driver = {
	.probe	= imx_ocotp_probe,
	.driver = {
		.name	= "imx_ocotp",
		.of_match_table = imx_ocotp_dt_ids,
	},
};
module_platform_driver(imx_ocotp_driver);

MODULE_AUTHOR("Philipp Zabel <p.zabel@pengutronix.de>");
MODULE_DESCRIPTION("i.MX6/i.MX7 OCOTP fuse box driver");
MODULE_LICENSE("GPL v2");
