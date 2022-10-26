TARGET  := imx8mq_sd_card_drv
REQUIRES = arm_v8a
LIBS     = base
INC_DIR  = $(PRG_DIR)
SRC_CC  += main.cc
SRC_CC  += time.cc
SRC_CC  += lx_emul/shared_dma_buffer.cc
SRC_C   += block.c
SRC_C   += dummies.c
SRC_C   += lx_emul.c
SRC_C   += $(notdir $(wildcard $(PRG_DIR)/generated_dummies.c))

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

include $(REP_DIR)/src/drivers/linux_mnt_reform2_drv_target_arm_v8.inc
