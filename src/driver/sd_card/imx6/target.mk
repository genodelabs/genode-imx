TARGET   = imx6_sd_card
REQUIRES = arm_v7a

GENERIC_DRV_DIR := $(dir $(call select_from_repositories,src/driver/sd_card/sd_card.h))

LIBS    = base
SRC_CC  = main.cc adma2.cc imx/driver.cc imx6/driver.cc
INC_DIR = $(PRG_DIR)/../imx $(GENERIC_DRV_DIR)

vpath %.cc $(PRG_DIR)/..
vpath %.cc $(GENERIC_DRV_DIR)
