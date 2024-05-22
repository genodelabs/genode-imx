TARGET   = imx8mp_platform
REQUIRES = arm_v8
SRC_CC   = ccm.cc
SRC_CC  += common/ccm.cc
INC_DIR += $(PRG_DIR)/../

vpath common/ccm.cc $(PRG_DIR)/../

include $(call select_from_repositories,src/driver/platform/target.inc)
