DRIVER   := imx8mq_fb
TARGET   := $(DRIVER)
REQUIRES := arm_v8a
LIBS     := base blit imx_linux_generated imx_lx_emul jitterentropy

INC_DIR  := $(PRG_DIR)

SRC_CC   := i2c.cc
SRC_CC   += lx_emul/random.cc
SRC_CC   += main.cc
SRC_CC   += reset.cc

SRC_C    := dummies.c
SRC_C    += fb.c
SRC_C    += gpcv2.c
SRC_C    += gpio-mxc.c
SRC_C    += i2c_imx.c
SRC_C    += lx_emul.c
SRC_C    += lx_emul/common_dummies.c
SRC_C    += lx_emul/shadow/drivers/base/power/runtime.c
SRC_C    += lx_emul/shadow/drivers/char/random.c
SRC_C    += lx_user.c
SRC_C    += pinctrl.c
SRC_C    += pwm-imx27.c
SRC_C    += regulator-fixed.c
SRC_C    += reset_core.c
SRC_C    += $(notdir $(wildcard $(PRG_DIR)/generated_dummies.c))

CC_OPT_gpio-mxc := -DKBUILD_MODFILE='"gpio_mxc"'
CC_OPT_gpio-mxc += -DKBUILD_BASENAME='"gpio_mxc"'
CC_OPT_gpio-mxc += -DKBUILD_MODNAME='"gpio_mxc"'

CC_OPT_i2c_imx := -DKBUILD_MODFILE='"i2c_imx"'
CC_OPT_i2c_imx += -DKBUILD_BASENAME='"i2c_imx"'
CC_OPT_i2c_imx += -DKBUILD_MODNAME='"i2c_imx"'

CC_OPT_pwm-imx27 := -DKBUILD_MODFILE='"pwm_imx27"'
CC_OPT_pwm-imx27 += -DKBUILD_BASENAME='"pwm_imx27"'
CC_OPT_pwm-imx27 += -DKBUILD_MODNAME='"pwm_imx27"'

CC_OPT_regulator-fixed := -DKBUILD_MODFILE='"regulator_fixed"'
CC_OPT_regulator-fixed += -DKBUILD_BASENAME='"regulator_fixed"'
CC_OPT_regulator-fixed += -DKBUILD_MODNAME='"regulator_fixed"'

CC_OPT_drivers/base/regmap/regmap += -I$(LX_SRC_DIR)/drivers/base/regmap

# Turn off some warnings
CC_OPT_drivers/gpu/drm/bridge/cadence/cdns-mhdp-audio += -Wno-unused-function
CC_OPT_drivers/gpu/drm/drm_plane_helper               += -Wno-uninitialized
CC_OPT_drivers/gpu/drm/imx/cdn-mhdp-imxdrv            += -Wno-unused-variable

vpath lx_emul/common_dummies.c $(REP_DIR)/src/lib/imx

# Driver-specific device-tree binary data

BOARDS                        := mnt_reform2 mnt_reform2-hdmi imx8q_evk
DTS_PATH(mnt_reform2)         := arch/arm64/boot/dts/freescale/imx8mq-mnt-reform2.dts
DTS_EXTRACT(mnt_reform2)      := --select dcss --select edp_bridge --select lcdif
DTS_PATH(mnt_reform2-hdmi)    := arch/arm64/boot/dts/freescale/imx8mq-mnt-reform2-hdmi.dts
DTS_EXTRACT(mnt_reform2-hdmi) := --select dcss --select edp_bridge --select lcdif --select hdmi
DTS_PATH(imx8q_evk)           := arch/arm64/boot/dts/freescale/imx8mq-evk.dts
DTS_EXTRACT(imx8q_evk)        := --select dcss --select hdmi
