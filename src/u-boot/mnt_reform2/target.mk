TARGET             = mnt_reform2_uboot
REQUIRES           = arm_v8a
CUSTOM_TARGET_DEPS = flash.bin
UBOOT_CONTRIB_DIR  = $(call select_from_ports,mnt_reform2_uboot)/uboot

unexport BOARD
unexport MAKEFLAGS

$(CUSTOM_TARGET_DEPS):
	cp $(UBOOT_CONTRIB_DIR)/bl31-iMX8MQ.bin $(PWD)/$(PRG_REL_DIR)/
	cp $(UBOOT_CONTRIB_DIR)/mntreform-config $(PWD)/$(PRG_REL_DIR)/.config
	$(MAKE) -C $(UBOOT_CONTRIB_DIR) O=$(PWD)/$(PRG_REL_DIR) ARCH=arm CROSS_COMPILE=$(CROSS_DEV_PREFIX) flash.bin
