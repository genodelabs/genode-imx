DRIVER   := stmmac_nic
TARGET   := $(DRIVER)
REQUIRES := arm_v8a
LIBS     := base imx_linux_generated imx_lx_emul jitterentropy
INC_DIR  := $(PRG_DIR)

SRC_CC   += main.cc
SRC_CC   += lx_emul/random.cc
SRC_CC   += lx_emul/shared_dma_buffer.cc

SRC_C    += dummies.c
SRC_C    += lx_emul.c
SRC_C    += lx_emul/common_dummies.c
SRC_C    += lx_emul/nic.c
SRC_C    += lx_emul/shadow/drivers/base/power/runtime.c
SRC_C    += lx_emul/shadow/drivers/char/random.c
SRC_C    += lx_user.c
SRC_C    += gpio.c
SRC_C    += ocotp.c
SRC_C    += pinctrl.c
SRC_C    += $(notdir $(wildcard $(PRG_DIR)/generated_dummies.c))

CC_OPT_drivers/base/regmap/regmap += -I$(LX_SRC_DIR)/drivers/base/regmap

CC_OPT_gpio  = -DKBUILD_MODFILE='"gpio"'
CC_OPT_gpio += -DKBUILD_BASENAME='"gpio"'
CC_OPT_gpio += -DKBUILD_MODNAME='"gpio"'
CC_OPT_ocotp  = -DKBUILD_MODFILE='"ocotp"'
CC_OPT_ocotp += -DKBUILD_BASENAME='"ocotp"'
CC_OPT_ocotp += -DKBUILD_MODNAME='"ocotp"'

vpath lx_emul/common_dummies.c $(REP_DIR)/src/lib/imx

#
# Genode C-API backends
#

SRC_CC  += genode_c_api/uplink.cc
SRC_CC  += genode_c_api/mac_address_reporter.cc

GENODE_C_API_SRC_DIR := $(call select_from_repositories,src/lib/genode_c_api)
vpath % $(dir $(GENODE_C_API_SRC_DIR))

# Driver-specific device-tree binary data
BOARDS                       := imx8mp_iot_gate mnt_pocket
DTS_PATH(imx8mp_iot_gate)    := arch/arm64/boot/dts/compulab/iot-gate-imx8plus.dts
DTS_EXTRACT(imx8mp_iot_gate) := --select eqos
DTS_PATH(mnt_pocket)         := arch/arm64/boot/dts/freescale/imx8mq-mnt-pocket.dts
DTS_EXTRACT(mnt_pocket)      := --select eqos
