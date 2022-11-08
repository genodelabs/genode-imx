TARGET  := imx8mq_usb_host_drv
REQUIRES = arm_v8a
LIBS     = base
INC_DIR  = $(PRG_DIR)
SRC_CC  += main.cc
SRC_CC  += time.cc
SRC_CC  += lx_emul/shared_dma_buffer.cc
SRC_C   += dummies.c
SRC_C   += lx_emul.c
SRC_C   += lx_emul/usb.c
SRC_C   += $(notdir $(wildcard $(PRG_DIR)/generated_dummies.c))

CC_OPT_drivers/usb/dwc3/trace      += -I$(LX_CONTRIB_DIR)/drivers/usb/dwc3
CC_OPT_drivers/usb/host/xhci-trace += -I$(LX_CONTRIB_DIR)/drivers/usb/host

#
# Genode C-API backends
#

SRC_CC  += genode_c_api/usb.cc

vpath genode_c_api/usb.cc $(subst /genode_c_api,,$(call select_from_repositories,src/lib/genode_c_api))

# Driver-specific device-tree binary data
BOARDS                   := mnt_reform2 imx8q_evk
DTS_PATH(mnt_reform2)    := arch/arm64/boot/dts/freescale/imx8mq-mnt-reform2.dts
DTS_EXTRACT(mnt_reform2) := --select usb_dwc3_0 --select usb_dwc3_1
DTS_PATH(imx8q_evk)      := arch/arm64/boot/dts/freescale/imx8mq-evk.dts
DTS_EXTRACT(imx8q_evk)   := --select usb_dwc3_0 --select usb_dwc3_1

include $(REP_DIR)/src/drivers/linux_mnt_reform2_drv_target_arm_v8.inc
