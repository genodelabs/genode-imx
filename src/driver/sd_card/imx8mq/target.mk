DRIVER  := imx8mq_sd_card
TARGET  := $(DRIVER)
REQUIRES = arm_v8a
LIBS     = base imx_linux_generated imx_lx_emul jitterentropy
INC_DIR  = $(PRG_DIR)
SRC_CC  += main.cc
SRC_CC  += lx_emul/random.cc
SRC_CC  += lx_emul/shared_dma_buffer.cc

SRC_C   += lx_emul/block.c

SRC_C   += dummies.c
SRC_C   += lx_emul.c
SRC_C   += lx_emul/common_dummies.c
SRC_C   += lx_emul/shadow/drivers/char/random.c
SRC_C   += pinctrl.c
SRC_C   += $(notdir $(wildcard $(PRG_DIR)/generated_dummies.c))

CC_OPT_drivers/base/regmap/regmap += -I$(LX_SRC_DIR)/drivers/base/regmap

vpath lx_emul/common_dummies.c $(REP_DIR)/src/lib/imx


#
# Genode C-API backends
#

SRC_CC  += genode_c_api/block.cc

vpath genode_c_api/block.cc $(subst /genode_c_api,,$(call select_from_repositories,src/lib/genode_c_api))

# Driver-specific device-tree binary data
BOARDS                       := mnt_pocket mnt_reform2 imx8q_evk imx8mp_iot_gate imx8mp_armstone
DTS_PATH(mnt_pocket)         := arch/arm64/boot/dts/freescale/imx8mq-mnt-pocket.dts
DTS_EXTRACT(mnt_pocket)      := --select usdhc1 --select usdhc3
DTS_PATH(mnt_reform2)        := arch/arm64/boot/dts/freescale/imx8mq-mnt-reform2.dts
DTS_EXTRACT(mnt_reform2)     := --select usdhc1 --select usdhc2
DTS_PATH(imx8q_evk)          := arch/arm64/boot/dts/freescale/imx8mq-evk.dts
DTS_EXTRACT(imx8q_evk)       := --select usdhc2
DTS_PATH(imx8mp_iot_gate)    := arch/arm64/boot/dts/compulab/iot-gate-imx8plus.dts
DTS_EXTRACT(imx8mp_iot_gate) := --select usdhc3
DTS_PATH(imx8mp_armstone)    := arch/arm64/boot/dts/F+S/armstonemx8mp.dts
DTS_EXTRACT(imx8mp_armstone) := --select usdhc1 --select usdhc3
