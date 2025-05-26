TARGET   := fus_linux
REQUIRES := arm_64 gcc_14_wont_build_linux_5.15

CUSTOM_TARGET_DEPS := kernel_build.phony

LX_DIR := $(call select_from_ports,fus_linux)/fus-linux
PWD    := $(shell pwd)

LX_MK_ARGS = ARCH=arm64 CROSS_COMPILE=$(CROSS_DEV_PREFIX)

#
# Linux kernel configuration
#
# define 'LX_ENABLE' and 'LX_DISABLE'
include $(REP_DIR)/src/fus_linux/arm_v8a/target.inc

# filter for make output of kernel build system
BUILD_OUTPUT_FILTER = 2>&1 | sed "s/^/      [Linux]  /"

# do not confuse third-party sub-makes
unexport .SHELLFLAGS

kernel_config.tag:
	$(MSG_CONFIG)Linux
	$(VERBOSE)$(MAKE) -C $(LX_DIR) O=$(PWD) $(LX_MK_ARGS) tinyconfig $(BUILD_OUTPUT_FILTER)
	$(VERBOSE)$(LX_DIR)/scripts/config $(addprefix --enable ,$(LX_ENABLE))
	$(VERBOSE)$(LX_DIR)/scripts/config $(addprefix --disable ,$(LX_DISABLE))
	$(VERBOSE)$(MAKE) $(LX_MK_ARGS) olddefconfig $(BUILD_OUTPUT_FILTER)
	$(VERBOSE)touch $@

# update Linux kernel config on makefile changes
kernel_config.tag: $(MAKEFILE_LIST)

kernel_build.phony: kernel_config.tag
	$(MSG_BUILD)Linux
	$(VERBOSE)$(MAKE) $(LX_MK_ARGS) dtbs Image Image.gz $(BUILD_OUTPUT_FILTER)

