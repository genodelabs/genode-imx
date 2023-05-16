TARGET              = imx8q_evk_uboot
REQUIRES            = arm_v8a
CUSTOM_TARGET_DEPS  = flash.bin
UBOOT_CONTRIB_DIR  := $(call select_from_ports,imx8q_evk_uboot)/uboot
ATF_CONTRIB_DIR    := $(call select_from_ports,imx8q_evk_uboot)/atf
IMG_CONTRIB_DIR    := $(call select_from_ports,imx8q_evk_uboot)/mkimage
FWI_CONTRIB_DIR    := $(call select_from_ports,imx8q_evk_uboot)/firmware

# do not confuse third-party sub-makes
unexport BOARD
unexport MAKEFLAGS
unexport .SHELLFLAGS

$(CUSTOM_TARGET_DEPS):
	$(MAKE) -C $(UBOOT_CONTRIB_DIR) O=$(PWD)/$(PRG_REL_DIR)/uboot ARCH=arm CROSS_COMPILE=$(CROSS_DEV_PREFIX) imx8mq_evk_defconfig
	$(MAKE) -C $(UBOOT_CONTRIB_DIR) O=$(PWD)/$(PRG_REL_DIR)/uboot LDFLAGS=--no-warn-rwx-segments ARCH=arm CROSS_COMPILE=$(CROSS_DEV_PREFIX)
	$(VERBOSE)cp -r $(ATF_CONTRIB_DIR) $(PWD)/$(PRG_REL_DIR)/atf
	$(MAKE) -C $(PWD)/$(PRG_REL_DIR)/atf LDFLAGS=--no-warn-rwx-segments PLAT=imx8mq CROSS_COMPILE=$(CROSS_DEV_PREFIX) bl31
	$(VERBOSE)cp -r $(IMG_CONTRIB_DIR) $(PWD)/$(PRG_REL_DIR)/mkimage
	$(VERBOSE)ln -s $(PWD)/$(PRG_REL_DIR)/uboot/tools/mkimage $(PWD)/$(PRG_REL_DIR)/mkimage/iMX8M/mkimage_uboot
	$(VERBOSE)ln -s $(PWD)/$(PRG_REL_DIR)/uboot/spl/u-boot-spl.bin $(PWD)/$(PRG_REL_DIR)/mkimage/iMX8M/
	$(VERBOSE)ln -s $(PWD)/$(PRG_REL_DIR)/uboot/u-boot-nodtb.bin $(PWD)/$(PRG_REL_DIR)/mkimage/iMX8M/
	$(VERBOSE)ln -s $(PWD)/$(PRG_REL_DIR)/uboot/arch/arm/dts/fsl-imx8mq-evk.dtb $(PWD)/$(PRG_REL_DIR)/mkimage/iMX8M/
	$(VERBOSE)ln -s $(PWD)/$(PRG_REL_DIR)/atf/build/imx8mq/release/bl31.bin $(PWD)/$(PRG_REL_DIR)/mkimage/iMX8M/
	$(VERBOSE)ln -s $(FWI_CONTRIB_DIR)/firmware-imx-8.1/firmware/hdmi/cadence/signed_hdmi_imx8m.bin  $(PWD)/$(PRG_REL_DIR)/mkimage/iMX8M/
	$(VERBOSE)ln -s $(FWI_CONTRIB_DIR)/firmware-imx-8.1/firmware/ddr/synopsys/lpddr4_pmu_train_1d_dmem.bin $(PWD)/$(PRG_REL_DIR)/mkimage/iMX8M/
	$(VERBOSE)ln -s $(FWI_CONTRIB_DIR)/firmware-imx-8.1/firmware/ddr/synopsys/lpddr4_pmu_train_1d_imem.bin $(PWD)/$(PRG_REL_DIR)/mkimage/iMX8M/
	$(VERBOSE)ln -s $(FWI_CONTRIB_DIR)/firmware-imx-8.1/firmware/ddr/synopsys/lpddr4_pmu_train_2d_dmem.bin $(PWD)/$(PRG_REL_DIR)/mkimage/iMX8M/
	$(VERBOSE)ln -s $(FWI_CONTRIB_DIR)/firmware-imx-8.1/firmware/ddr/synopsys/lpddr4_pmu_train_2d_imem.bin $(PWD)/$(PRG_REL_DIR)/mkimage/iMX8M/
	$(VERBOSE)echo "#define MKIMAGE_COMMIT 0x1" > $(PWD)/$(PRG_REL_DIR)/mkimage/src/build_info.h
	$(MAKE) -C $(PWD)/$(PRG_REL_DIR)/mkimage SOC=iMX8M flash_evk
	$(VERBOSE)cp $(PWD)/$(PRG_REL_DIR)/mkimage/iMX8M/flash.bin $@
