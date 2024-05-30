DRIVER   := imx_usb_host
TARGET   := $(DRIVER)
REQUIRES := arm_v7a
LIBS      = base imx_linux_generated imx_lx_emul jitterentropy
INC_DIR   = $(PRG_DIR)
SRC_CC   += main.cc
SRC_C    += dummies.c
SRC_C    += lx_emul.c
SRC_C    += lx_emul/shadow/drivers/char/random.c
SRC_CC   += lx_emul/shared_dma_buffer.cc
SRC_CC   += lx_emul/random.cc
SRC_C    += lx_emul/usb.c
SRC_C    += $(notdir $(wildcard $(PRG_DIR)/generated_dummies.c))

# Genode C-API backends
SRC_CC   += genode_c_api/usb.cc

vpath genode_c_api/usb.cc $(subst /genode_c_api,,$(call select_from_repositories,src/lib/genode_c_api))


CC_OPT_drivers/base/regmap/regmap   += -I$(LX_SRC_DIR)/drivers/base/regmap
CC_OPT_drivers/usb/gadget/udc/trace += -I$(LX_SRC_DIR)/drivers/usb/gadget/udc

# Driver-specific device-tree binary data
BOARDS                       := imx53_qsb imx6q_sabrelite imx7d_sabre
DTS_EXTRACT(imx53_qsb)       := --select usbh1 --select usbotg
DTS_EXTRACT(imx6q_sabrelite) := --select usbh1 --select usbh2 --select usbh3 --select usbotg --select aliases
DTS_EXTRACT(imx7d_sabre)     := --select usbh --select usbotg1 --select usbotg2
