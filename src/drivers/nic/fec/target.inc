TARGET     := fec_nic_drv
LIBS        = base
INC_DIR    += $(PRG_DIR)/../..
SRC_CC     += main.cc
SRC_C      += dummies.c
SRC_C      += lx_emul.c
SRC_C      += lx_user.c
SRC_C      += $(notdir $(wildcard $(PRG_DIR)/generated_dummies.c))

CC_OPT_dummies  = -DKBUILD_MODFILE='"dummies"'
CC_OPT_dummies += -DKBUILD_BASENAME='"dummies"'
CC_OPT_dummies += -DKBUILD_MODNAME='"dummies"'

CC_OPT_generated_dummies  = -DKBUILD_MODFILE='"dummies"'
CC_OPT_generated_dummies += -DKBUILD_BASENAME='"dummies"'
CC_OPT_generated_dummies += -DKBUILD_MODNAME='"dummies"'


#
# Genode C-API backends
#

SRC_CC  += genode_c_api/uplink.cc
GENODE_C_API_SRC_DIR := $(call select_from_repositories,src/lib/genode_c_api)
vpath % $(dir $(GENODE_C_API_SRC_DIR))

vpath %.c  $(PRG_DIR)/../..
vpath %.cc $(PRG_DIR)/../..
