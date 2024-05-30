TARGET  := imx8mq_fb
REQUIRES = arm_v8a
LIBS     = base blit
INC_DIR  = $(PRG_DIR)
SRC_CC   = i2c.cc
SRC_CC  += main.cc
SRC_CC  += reset.cc
SRC_C    = dummies.c
SRC_C   += fb.c
SRC_C   += i2c_imx.c
SRC_C   += lx_emul.c
SRC_C   += lx_user.c
SRC_C   += reset_core.c
SRC_C   += $(notdir $(wildcard $(PRG_DIR)/generated_dummies.c))

CC_OPT_i2c_imx  = -DKBUILD_MODFILE='"i2c_imx"'
CC_OPT_i2c_imx += -DKBUILD_BASENAME='"i2c_imx"'
CC_OPT_i2c_imx += -DKBUILD_MODNAME='"i2c_imx"'

# Turn off some warnings
CC_OPT_drivers/gpu/drm/bridge/cadence/cdns-mhdp-audio += -Wno-unused-function
CC_OPT_drivers/gpu/drm/drm_plane_helper               += -Wno-uninitialized
CC_OPT_drivers/gpu/drm/imx/cdn-mhdp-imxdrv            += -Wno-unused-variable

# Driver-specific device-tree binary data
BOARDS                        := mnt_reform2 mnt_reform2-hdmi imx8q_evk
DTS_PATH(mnt_reform2)         := arch/arm64/boot/dts/freescale/imx8mq-mnt-reform2.dts
DTS_EXTRACT(mnt_reform2)      := --select dcss --select edp_bridge --select lcdif
DTS_PATH(mnt_reform2-hdmi)    := arch/arm64/boot/dts/freescale/imx8mq-mnt-reform2-hdmi.dts
DTS_EXTRACT(mnt_reform2-hdmi) := --select dcss --select edp_bridge --select lcdif --select hdmi
DTS_PATH(imx8q_evk)           := arch/arm64/boot/dts/freescale/imx8mq-evk.dts
DTS_EXTRACT(imx8q_evk)        := --select dcss --select hdmi

include $(REP_DIR)/src/drivers/linux_mnt_reform2_drv_target_arm_v8.inc
