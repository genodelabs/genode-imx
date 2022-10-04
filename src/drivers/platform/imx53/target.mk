TARGET   = imx53_platform_drv
REQUIRES = arm_v7

include $(call select_from_repositories,src/drivers/platform/target.inc)
