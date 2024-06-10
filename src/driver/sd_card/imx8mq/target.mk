DRIVER  := imx8mq_sd_card
TARGET  := $(DRIVER)
REQUIRES = arm_v8a
LIBS     = base imx_linux_generated imx_lx_emul jitterentropy
INC_DIR  = $(PRG_DIR)
SRC_CC  += main.cc
SRC_CC  += lx_emul/random.cc
SRC_CC  += lx_emul/shared_dma_buffer.cc

SRC_C   += block.c
SRC_C   += dummies.c
SRC_C   += lx_emul.c
SRC_C   += lx_emul/shadow/drivers/char/random.c
SRC_C   += $(notdir $(wildcard $(PRG_DIR)/generated_dummies.c))

CC_OPT_drivers/base/regmap/regmap += -I$(LX_SRC_DIR)/drivers/base/regmap


#
# Genode C-API backends
#

SRC_CC  += genode_c_api/block.cc

vpath genode_c_api/block.cc $(subst /genode_c_api,,$(call select_from_repositories,src/lib/genode_c_api))

# Driver-specific device-tree binary data
BOARDS                   := mnt_reform2 imx8q_evk
DTS_PATH(mnt_reform2)    := arch/arm64/boot/dts/freescale/imx8mq-mnt-reform2.dts
DTS_EXTRACT(mnt_reform2) := --select usdhc1 --select usdhc2
DTS_PATH(imx8q_evk)      := arch/arm64/boot/dts/freescale/imx8mq-evk.dts
DTS_EXTRACT(imx8q_evk)   := --select usdhc2
