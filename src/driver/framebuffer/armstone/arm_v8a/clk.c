#include <dt-bindings/clock/imx8mp-clock.h>
#include <dt-bindings/reset/imx8mp-reset.h>
#include <clk.h>
#include <clk-blk-ctrl.h>
#include <linux/clk.h>
#include <linux/clk-provider.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <lx_emul/clock.h>

static struct device_node *ccm_of_node;

static const char *imx_hdmi_phy_clks_sels[] = { "hdmi_glb_24m", "dummy",};
static const char *imx_lcdif_clks_sels[] = { "dummy", "hdmi_glb_pix", };
static const char *imx_hdmi_pipe_clks_sels[] = {"dummy","hdmi_glb_pix", };

static struct imx_blk_ctrl_hw imx8mp_hdmi_blk_ctrl_hws[] = {
	/* clocks */
	IMX_BLK_CTRL_CLK_GATE("hdmi_glb_apb", IMX8MP_CLK_HDMI_BLK_CTRL_GLOBAL_APB_CLK, 0x40, 0, "hdmi_apb"),
	IMX_BLK_CTRL_CLK_GATE("hdmi_glb_b", IMX8MP_CLK_HDMI_BLK_CTRL_GLOBAL_B_CLK, 0x40, 1, "hdmi_axi"),
	IMX_BLK_CTRL_CLK_GATE("hdmi_glb_ref_266m", IMX8MP_CLK_HDMI_BLK_CTRL_GLOBAL_REF266M_CLK, 0x40, 2, "hdmi_ref_266m"),
	IMX_BLK_CTRL_CLK_GATE("hdmi_glb_24m", IMX8MP_CLK_HDMI_BLK_CTRL_GLOBAL_XTAL24M_CLK, 0x40, 4, "hdmi_24m"),
	IMX_BLK_CTRL_CLK_GATE("hdmi_glb_32k", IMX8MP_CLK_HDMI_BLK_CTRL_GLOBAL_XTAL32K_CLK, 0x40, 5, "osc_32k"),
	IMX_BLK_CTRL_CLK_GATE("hdmi_glb_pix", IMX8MP_CLK_HDMI_BLK_CTRL_GLOBAL_TX_PIX_CLK, 0x40, 7, "hdmi_phy"),
	IMX_BLK_CTRL_CLK_GATE("hdmi_irq_steer", IMX8MP_CLK_HDMI_BLK_CTRL_IRQS_STEER_CLK, 0x40, 9, "hdmi_glb_apb"),
	IMX_BLK_CTRL_CLK_GATE("hdmi_noc", IMX8MP_CLK_HDMI_BLK_CTRL_NOC_HDMI_CLK, 0x40, 10, "hdmi_glb_apb"),
	IMX_BLK_CTRL_CLK_GATE("hdcp_noc", IMX8MP_CLK_HDMI_BLK_CTRL_NOC_HDCP_CLK, 0x40, 11,  "hdmi_glb_apb"),
	IMX_BLK_CTRL_CLK_GATE("lcdif3_apb", IMX8MP_CLK_HDMI_BLK_CTRL_LCDIF_APB_CLK, 0x40, 16, "hdmi_glb_apb"),
	IMX_BLK_CTRL_CLK_GATE("lcdif3_b", IMX8MP_CLK_HDMI_BLK_CTRL_LCDIF_B_CLK, 0x40, 17, "hdmi_glb_b"),
	IMX_BLK_CTRL_CLK_GATE("lcdif3_pdi", IMX8MP_CLK_HDMI_BLK_CTRL_LCDIF_PDI_CLK, 0x40, 18, "hdmi_glb_apb"),
	IMX_BLK_CTRL_CLK_GATE("lcdif3_pxl", IMX8MP_CLK_HDMI_BLK_CTRL_LCDIF_PIX_CLK, 0x40, 19, "hdmi_glb_pix"),
	IMX_BLK_CTRL_CLK_GATE("lcdif3_spu", IMX8MP_CLK_HDMI_BLK_CTRL_LCDIF_SPU_CLK, 0x40, 20, "hdmi_glb_apb"),
	IMX_BLK_CTRL_CLK_GATE("hdmi_fdcc_ref", IMX8MP_CLK_HDMI_BLK_CTRL_FDCC_REF_CLK, 0x50, 2, "hdmi_fdcc_tst"),
	IMX_BLK_CTRL_CLK_GATE("hrv_mwr_apb", IMX8MP_CLK_HDMI_BLK_CTRL_HRV_MWR_APB_CLK, 0x50, 3, "hdmi_glb_apb"),
	IMX_BLK_CTRL_CLK_GATE("hrv_mwr_b", IMX8MP_CLK_HDMI_BLK_CTRL_HRV_MWR_B_CLK, 0x50, 4, "hdmi_glb_axi"),
	IMX_BLK_CTRL_CLK_GATE("hrv_mwr_cea", IMX8MP_CLK_HDMI_BLK_CTRL_HRV_MWR_CEA_CLK, 0x50, 5, "hdmi_glb_apb"),
	IMX_BLK_CTRL_CLK_GATE("vsfd_cea", IMX8MP_CLK_HDMI_BLK_CTRL_VSFD_CEA_CLK, 0x50, 6, "hdmi_glb_apb"),
	IMX_BLK_CTRL_CLK_GATE("hdmi_tx_hpi", IMX8MP_CLK_HDMI_BLK_CTRL_TX_HPI_CLK, 0x50, 13, "hdmi_glb_apb"),
	IMX_BLK_CTRL_CLK_GATE("hdmi_tx_apb", IMX8MP_CLK_HDMI_BLK_CTRL_TX_APB_CLK, 0x50, 14, "hdmi_glb_apb"),
	IMX_BLK_CTRL_CLK_GATE("hdmi_cec", IMX8MP_CLK_HDMI_BLK_CTRL_TX_CEC_CLK, 0x50, 15, "hdmi_glb_32k"),
	IMX_BLK_CTRL_CLK_GATE("hdmi_esm", IMX8MP_CLK_HDMI_BLK_CTRL_TX_ESM_CLK, 0x50, 16, "hdmi_glb_ref_266m"),
	IMX_BLK_CTRL_CLK_GATE("hdmi_tx_gpa", IMX8MP_CLK_HDMI_BLK_CTRL_TX_GPA_CLK, 0x50, 17, "hdmi_glb_apb"),
	IMX_BLK_CTRL_CLK_GATE("hdmi_tx_pix", IMX8MP_CLK_HDMI_BLK_CTRL_TX_PIXEL_CLK, 0x50, 18, "hdmi_glb_pix"),
	IMX_BLK_CTRL_CLK_GATE("hdmi_tx_sfr", IMX8MP_CLK_HDMI_BLK_CTRL_TX_SFR_CLK, 0x50, 19, "hdmi_glb_apb"),
	IMX_BLK_CTRL_CLK_GATE("hdmi_tx_skp", IMX8MP_CLK_HDMI_BLK_CTRL_TX_SKP_CLK, 0x50, 20, "hdmi_glb_apb"),
	IMX_BLK_CTRL_CLK_GATE("hdmi_tx_prep", IMX8MP_CLK_HDMI_BLK_CTRL_TX_PREP_CLK, 0x50, 21, "hdmi_glb_apb"),
	IMX_BLK_CTRL_CLK_GATE("hdmi_phy_apb", IMX8MP_CLK_HDMI_BLK_CTRL_TX_PHY_APB_CLK, 0x50, 22, "hdmi_glb_apb"),
	IMX_BLK_CTRL_CLK_GATE("hdmi_phy_int", IMX8MP_CLK_HDMI_BLK_CTRL_TX_PHY_INT_CLK, 0x50, 24, "hdmi_glb_apb"),
	IMX_BLK_CTRL_CLK_GATE("hdmi_sec_mem", IMX8MP_CLK_HDMI_BLK_CTRL_TX_SEC_MEM_CLK, 0x50, 25, "hdmi_glb_ref_266m"),
	IMX_BLK_CTRL_CLK_GATE("hdmi_trng_skp", IMX8MP_CLK_HDMI_BLK_CTRL_TX_TRNG_SKP_CLK, 0x50, 27, "hdmi_glb_apb"),
	IMX_BLK_CTRL_CLK_GATE("hdmi_vid_pix",  IMX8MP_CLK_HDMI_BLK_CTRL_TX_VID_LINK_PIX_CLK, 0x50, 28, "hdmi_glb_pix"),
	IMX_BLK_CTRL_CLK_GATE("hdmi_trng_apb", IMX8MP_CLK_HDMI_BLK_CTRL_TX_TRNG_APB_CLK, 0x50, 30, "hdmi_glb_apb"),
	IMX_BLK_CTRL_CLK_MUX("hdmi_phy_sel", IMX8MP_CLK_HDMI_BLK_CTRL_HTXPHY_CLK_SEL, 0x50, 10, 1, imx_hdmi_phy_clks_sels),
	IMX_BLK_CTRL_CLK_MUX("lcdif_clk_sel", IMX8MP_CLK_HDMI_BLK_CTRL_LCDIF_CLK_SEL, 0x50, 11, 1, imx_lcdif_clks_sels),
	IMX_BLK_CTRL_CLK_MUX("hdmi_pipe_sel", IMX8MP_CLK_HDMI_BLK_CTRL_TX_PIPE_CLK_SEL, 0x50, 12, 1, imx_hdmi_pipe_clks_sels),

	/* resets */
	IMX_BLK_CTRL_RESET_MASK(IMX8MP_HDMI_BLK_CTRL_HDMI_TX_RESET, 0x20, 6, 0x33),
	IMX_BLK_CTRL_RESET(IMX8MP_HDMI_BLK_CTRL_HDMI_PHY_RESET, 0x20, 12),
	IMX_BLK_CTRL_RESET(IMX8MP_HDMI_BLK_CTRL_HDMI_PAI_RESET, 0x20, 18),
	IMX_BLK_CTRL_RESET(IMX8MP_HDMI_BLK_CTRL_HDMI_PVI_RESET, 0x20, 22),
	IMX_BLK_CTRL_RESET(IMX8MP_HDMI_BLK_CTRL_HDMI_TRNG_RESET, 0x20, 20),
	IMX_BLK_CTRL_RESET(IMX8MP_HDMI_BLK_CTRL_IRQ_STEER_RESET, 0x20, 16),
	IMX_BLK_CTRL_RESET(IMX8MP_HDMI_BLK_CTRL_HDMI_HDCP_RESET, 0x20, 13),
	IMX_BLK_CTRL_RESET_MASK(IMX8MP_HDMI_BLK_CTRL_LCDIF_RESET, 0x20, 4, 0x3),
};


const struct imx_blk_ctrl_dev_data imx8mp_hdmi_blk_ctrl_dev_data = {
	.hws = imx8mp_hdmi_blk_ctrl_hws,
	.hws_num = ARRAY_SIZE(imx8mp_hdmi_blk_ctrl_hws),
	.clocks_max = IMX8MP_CLK_HDMI_BLK_CTRL_END,
	.resets_max = IMX8MP_HDMI_BLK_CTRL_RESET_NUM,
	.pm_runtime_saved_regs_num = 0
};
EXPORT_SYMBOL_GPL(imx8mp_hdmi_blk_ctrl_dev_data);


const struct imx_blk_ctrl_dev_data imx8mp_audio_blk_ctrl_dev_data = {
	.hws = NULL,
	.hws_num = 0,
	.clocks_max = 0,
	.resets_max = 0,
	.pm_runtime_saved_regs_num = 0
};
EXPORT_SYMBOL_GPL(imx8mp_audio_blk_ctrl_dev_data);


const struct imx_blk_ctrl_dev_data imx8mp_media_blk_ctrl_dev_data = {
	.hws = NULL,
	.hws_num = 0,
	.clocks_max = 0,
	.resets_max = 0,
	.pm_runtime_saved_regs_num = 0
};
EXPORT_SYMBOL_GPL(imx8mp_media_blk_ctrl_dev_data);


static unsigned long my_clk_recalc_rate(struct clk_hw *hw,
                                     unsigned long parent_rate)
{
	struct clk *c = lx_emul_clock_get(ccm_of_node, clk_hw_get_name(hw));
	return c ? lx_emul_clock_get_rate(c) : 0;
}


static long my_clk_round_rate(struct clk_hw *hw, unsigned long rate,
                                    unsigned long * parent_rate)
{
	return rate;
}


static int dummy_clk_set_rate(struct clk_hw *hw, unsigned long rate,
                        unsigned long parent_rate)
{
	return 0;
}


static int dummy_clk_is_enabled(struct clk_hw *hw)
{
	return 1;
}


static int dummy_clk_enable(struct clk_hw *hw)
{
	return 0;
}


static void dummy_clk_disable(struct clk_hw *hw) { }


static const struct clk_ops clk_ops = {
	.enable = dummy_clk_enable,
	.disable = dummy_clk_disable,
	.is_enabled = dummy_clk_is_enabled,
	.set_rate = dummy_clk_set_rate,
	.recalc_rate = my_clk_recalc_rate,
	.round_rate = my_clk_round_rate
};


static struct clk_hw *genode_clk_hw(const char *name)
{
	struct clk_hw *hw;
	int ret;

	struct clk_init_data *init = kmalloc(sizeof(struct clk_init_data), GFP_KERNEL);

	init->name = name;
	init->ops = &clk_ops;
	init->flags = 0;
	init->num_parents = 0;

	hw = kmalloc(sizeof(struct clk_hw), GFP_KERNEL);
	hw->init = init;

	ret = clk_hw_register(NULL, hw);
	if (ret) {
		kfree(hw);
		return ERR_PTR(ret);
	}

	return hw;
}


static int imx8mp_clocks_probe(struct platform_device *pdev)
{
	int err;
	struct clk_hw **hws;
	struct clk_hw_onecell_data *clk_hw_data = kmalloc(struct_size(clk_hw_data, hws, IMX8MP_CLK_END), GFP_KERNEL);
	if (WARN_ON(!clk_hw_data))
		return -ENOMEM;

	ccm_of_node = pdev->dev.of_node;

	clk_hw_data->num = IMX8MP_CLK_END;
	hws = clk_hw_data->hws;

	hws[IMX8MP_CLK_DUMMY] = imx_clk_hw_fixed("dummy",            0);
	hws[IMX8MP_CLK_24M]   = imx_clk_hw_fixed("osc_24m",   24000000);
	hws[IMX8MP_CLK_32K]   = imx_clk_hw_fixed("osc_32k",      32000);
	hws[IMX8MP_CLK_EXT1]  = imx_clk_hw_fixed("clk_ext1", 133000000);
	hws[IMX8MP_CLK_EXT2]  = imx_clk_hw_fixed("clk_ext2", 133000000);
	hws[IMX8MP_CLK_EXT3]  = imx_clk_hw_fixed("clk_ext3", 133000000);
	hws[IMX8MP_CLK_EXT4]  = imx_clk_hw_fixed("clk_ext4", 133000000);

	hws[IMX8MP_SYS_PLL1_133M] = imx_clk_hw_fixed("sys_pll1_133", 133000000);
	hws[IMX8MP_SYS_PLL2_500M] = imx_clk_hw_fixed("sys_pll2_500", 500000000);
	hws[IMX8MP_CLK_24M]       = imx_clk_hw_fixed("clk_24m",       24000000);

	hws[IMX8MP_CLK_HDMI_APB]  = imx_clk_hw_fixed("hdmi_apb", 133333333);
	hws[IMX8MP_CLK_HDMI_AXI]  = imx_clk_hw_fixed("hdmi_axi", 500000000);
	hws[IMX8MP_CLK_HDMI_24M]  = imx_clk_hw_fixed("hdmi_24m", 24000000);

	hws[IMX8MP_CLK_HDMI_ROOT]     = imx_clk_hw_fixed("hdmi_root_clk", 500000000);
	hws[IMX8MP_CLK_HDMI_REF_266M] = imx_clk_hw_fixed("hdmi_ref_266m", 24000000);

	err = of_clk_add_hw_provider(pdev->dev.of_node, of_clk_hw_onecell_get, clk_hw_data);
	if (err < 0) {
		printk("failed to register hws for i.MX8MP\n");
		imx_unregister_hw_clocks(hws, IMX8MP_CLK_END);
		return err;
	}

	return 0;
}


static const struct of_device_id imx8mp_clk_of_match[] = {
	{ .compatible = "fsl,imx8mp-ccm" },
	{ /* Sentinel */ }
};
MODULE_DEVICE_TABLE(of, imx8mp_clk_of_match);

static struct platform_driver imx8mp_clk_driver = {
	.probe = imx8mp_clocks_probe,
	.driver = {
		.name = "imx8mp-ccm",
		/*
		 * Disable bind attributes: clocks are not removed and
		 * reloading the driver will crash or break devices.
		 */
		.suppress_bind_attrs = true,
		.of_match_table = imx8mp_clk_of_match,
	},
};
module_platform_driver(imx8mp_clk_driver);
