DRIVER   := fec_nic
TARGET   := $(DRIVER)
LIBS     := base imx_linux_generated imx_lx_emul jitterentropy

INC_DIR  := $(PRG_DIR)/../..
INC_DIR  += $(PRG_DIR)/include/lx_emul/shadow

SRC_CC   += main.cc
SRC_CC   += lx_emul/random.cc

SRC_C    += dummies.c
SRC_C    += lx_emul.c
SRC_C    += lx_emul/common_dummies.c
SRC_C    += lx_emul/shadow/drivers/char/random.c
SRC_C    += lx_user.c
SRC_C    += ocotp.c
SRC_C    += pinctrl.c
SRC_C    += $(notdir $(wildcard $(PRG_DIR)/generated_dummies.c))

CC_OPT_drivers/base/regmap/regmap   += -I$(LX_SRC_DIR)/drivers/base/regmap

# for including 'net-sysfs.h'
CC_OPT_dummies += -I$(LX_SRC_DIR)/net/core

CC_OPT_ocotp  = -DKBUILD_MODFILE='"ocotp"'
CC_OPT_ocotp += -DKBUILD_BASENAME='"ocotp"'
CC_OPT_ocotp += -DKBUILD_MODNAME='"ocotp"'

#
# Genode C-API backends
#

SRC_CC += genode_c_api/uplink.cc \
          genode_c_api/mac_address_reporter.cc

GENODE_C_API_SRC_DIR := $(call select_from_repositories,src/lib/genode_c_api)
vpath % $(dir $(GENODE_C_API_SRC_DIR))

vpath lx_emul/common_dummies.c $(REP_DIR)/src/lib/imx

vpath %.c  $(PRG_DIR)/../..
vpath %.cc $(PRG_DIR)/../..
