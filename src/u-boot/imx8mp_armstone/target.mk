TARGET              = armstone_uboot
REQUIRES            = arm_v8a
CUSTOM_TARGET_DEPS  = u-boot.bin
UBOOT_CONTRIB_DIR  := $(call select_from_ports,fus_uboot)/uboot

# do not confuse third-party sub-makes
unexport BOARD
unexport MAKEFLAGS
unexport .SHELLFLAGS

$(CUSTOM_TARGET_DEPS):
	$(MAKE) -C $(UBOOT_CONTRIB_DIR) O=$(PWD)/$(PRG_REL_DIR) ARCH=arm CROSS_COMPILE=$(CROSS_DEV_PREFIX) fsimx8mp_defconfig
	$(MAKE) -C $(PWD)/$(PRG_REL_DIR) ARCH=arm CROSS_COMPILE=$(CROSS_DEV_PREFIX) u-boot.bin
