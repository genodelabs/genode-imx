TARGET  := imx8mq_fb_drv
REQUIRES = arm_v8a
LIBS     = base blit
INC_DIR  = $(PRG_DIR)
SRC_CC   = i2c.cc
SRC_CC  += main.cc
SRC_CC  += reset.cc
SRC_C    = dummies.c
SRC_C   += fb.c
SRC_C   += i2c_imx.c
SRC_C   += lx_user.c
SRC_C   += reset_core.c
SRC_C   += $(notdir $(wildcard $(PRG_DIR)/generated_dummies.c))

CC_OPT_i2c_imx  = -DKBUILD_MODFILE='"i2c_imx"'
CC_OPT_i2c_imx += -DKBUILD_BASENAME='"i2c_imx"'
CC_OPT_i2c_imx += -DKBUILD_MODNAME='"i2c_imx"'

# Turn off some warnings
CC_OPT_drivers/gpu/drm/drm_plane_helper    += -Wno-uninitialized
CC_OPT_drivers/gpu/drm/imx/cdn-mhdp-imxdrv += -Wno-unused-variable

# Driver-specific device-tree binary data
BOARDS                   := mnt_reform2
DTS_PATH(mnt_reform2)    := arch/arm64/boot/dts/freescale/imx8mq-mnt-reform2.dts
DTS_EXTRACT(mnt_reform2) := --select dcss --select edp_bridge --select lcdif

include $(REP_DIR)/src/drivers/linux_mnt_reform2_drv_target.inc
