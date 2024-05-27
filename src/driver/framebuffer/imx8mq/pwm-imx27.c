/*
 * \brief  Stub variant of the Linux Kernel' i.MX27 PWM driver
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
#include <linux/pwm.h>

static void pwm_imx27_get_state(struct pwm_chip *chip,
                                struct pwm_device *pwm,
                                struct pwm_state *state)
{ }

static int pwm_imx27_apply(struct pwm_chip *chip, struct pwm_device *pwm,
                           const struct pwm_state *state)
{
	return 0;
}

static const struct pwm_ops pwm_imx27_ops = {
	.apply = pwm_imx27_apply,
	.get_state = pwm_imx27_get_state,
	.owner = THIS_MODULE,
};

static const struct of_device_id pwm_imx27_dt_ids[] = {
	{ .compatible = "fsl,imx27-pwm", },
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, pwm_imx27_dt_ids);

static int pwm_imx27_probe(struct platform_device *pdev)
{
	struct pwm_chip *chip;

	chip = devm_kzalloc(&pdev->dev, sizeof(*chip), GFP_KERNEL);
	if (chip == NULL)
		return -ENOMEM;

	chip->ops = &pwm_imx27_ops;
	chip->dev = &pdev->dev;
	chip->npwm = 1;

	return devm_pwmchip_add(&pdev->dev, chip);
}

static struct platform_driver imx_pwm_driver = {
	.driver = {
		.name = "pwm-imx27",
		.of_match_table = pwm_imx27_dt_ids,
	},
	.probe = pwm_imx27_probe,
};
module_platform_driver(imx_pwm_driver);
