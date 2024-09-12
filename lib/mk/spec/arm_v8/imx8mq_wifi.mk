REQUIRES := arm_v8a

include $(call select_from_repositories,lib/mk/wifi.inc)

TARGET_LIB_DIR := $(REP_DIR)/src/lib/imx8mq_wifi

LIBS    += imx_linux_generated imx_lx_emul

INC_DIR += $(TARGET_LIB_DIR)

SRC_CC  += dtb_helper_no_dtb.cc
SRC_CC  += lx_emul/pci.cc
SRC_CC  += lx_emul/random.cc

SRC_C   += $(notdir $(wildcard $(TARGET_LIB_DIR)/generated_dummies.c))

SRC_C   += lx_emul/common_dummies.c
SRC_C   += lx_emul/shadow/drivers/char/random.c
SRC_C   += lx_emul/shadow/drivers/pci/host-bridge.c
SRC_C   += lx_emul/shadow/drivers/pci/pci-sysfs.c
SRC_C   += lx_emul/shadow/drivers/pci/pci-sysfs.c
SRC_C   += lx_emul/shadow/drivers/pci/pci.c
SRC_C   += lx_emul/shadow/drivers/pci/search.c
SRC_C   += lx_emul/shadow/drivers/pci/setup-irq.c
SRC_C   += lx_emul/shadow/drivers/pci/setup-res.c
SRC_C   += lx_emul/shadow/fs/libfs.c
SRC_C   += lx_emul/shadow/mm/dmapool.c
SRC_C   += lx_emul/shadow/mm/page_alloc.c
SRC_C   += lx_emul/shadow/mm/vmalloc.c
SRC_C   += lx_emul_pci.c
SRC_C   += lx_emul/pci_bus.c


CC_OPT_net/mac80211/trace += -I$(LX_SRC_DIR)/net/mac80211
CC_OPT_net/wireless/trace += -I$(LX_SRC_DIR)/net/wireless

CC_C_OPT += -I$(LX_SRC_DIR)/drivers/net/wireless/intel/iwlwifi
CC_C_OPT += -I$(LX_SRC_DIR)/drivers/net/wireless/realtek/rtlwifi
CC_C_OPT += -I$(LX_SRC_DIR)/drivers/net/wireless/realtek/rtlwifi/rtl8188ee

vpath lx_emul/common_dummies.c $(REP_DIR)/src/lib/imx
vpath %.c  $(TARGET_LIB_DIR)
vpath %.cc $(TARGET_LIB_DIR)
