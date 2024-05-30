TARGET   = imx8mq_platform
REQUIRES = arm_v8
SRC_CC   = ccm.cc

include $(call select_from_repositories,src/drivers/platform/target.inc)
