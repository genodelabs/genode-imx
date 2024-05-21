#
# Content hosted in the dde_linux repository
#

MIRRORED_FROM_DDE_LINUX := src/lib/lx_emul \
                           src/lib/lx_kit \
                           src/include/lx_emul \
                           src/include/lx_user \
                           src/include/spec/arm_v7/lx_kit \
                           src/include/spec/arm_v8/lx_kit \
                           src/include/lx_kit \
                           lib/import/import-lx_emul_common.inc

content: $(MIRRORED_FROM_DDE_LINUX)
$(MIRRORED_FROM_DDE_LINUX):
	mkdir -p $(dir $@); cp -r $(GENODE_DIR)/repos/dde_linux/$@ $(dir $@)


#
# Content hosted in the imx repository
#

MIRRORED_FROM_REP_DIR := lib/mk/imx_lx_emul.mk \
                         lib/mk/spec/arm_v7/imx_linux_generated.mk \
                         lib/mk/spec/arm_v8/imx_linux_generated.mk \
                         lib/import/import-imx_lx_emul.mk \
                         src/imx_linux/arm_v7a/target.inc \
                         src/imx_linux/arm_v8a/target.inc

content: $(MIRRORED_FROM_REP_DIR)
$(MIRRORED_FROM_REP_DIR):
	$(mirror_from_rep_dir)


#
# Content from the Linux source tree
#

PORT_DIR := $(call port_dir,$(REP_DIR)/ports/linux-imx)
LX_REL_DIR := linux-imx
LX_ABS_DIR := $(addsuffix /$(LX_REL_DIR),$(PORT_DIR))

LX_FILES += $(shell cd $(LX_ABS_DIR); find -name "Kconfig*" -printf "%P\n")

# add content listed in the repository's source.list or dep.list files
LX_FILE_LISTS := $(shell find -H $(REP_DIR)/src/lib -name dep.list -or -name source.list)
LX_FILES += $(shell cat $(LX_FILE_LISTS))
LX_USB_FILE_LISTS := $(shell find -H $(REP_DIR)/src/driver/usb_host/imx -name dep.list -or -name source.list)
LX_USB_FILE_LISTS += $(shell find -H $(REP_DIR)/src/driver/usb_host/imx8mq -name dep.list -or -name source.list)
LX_FILES += $(shell cat $(LX_USB_FILE_LISTS))
LX_GPU_FILE_LISTS := $(shell find -H $(REP_DIR)/src/driver/gpu/imx8mq -name dep.list -or -name source.list)
LX_FILES += $(shell cat $(LX_GPU_FILE_LISTS))
LX_NIC_FILE_LISTS := $(shell find -H $(REP_DIR)/src/driver/nic/fec -name dep.list -or -name source.list)
LX_FILES += $(shell cat $(LX_NIC_FILE_LISTS))
LX_FILES := $(sort $(LX_FILES))
MIRRORED_FROM_PORT_DIR += $(addprefix $(LX_REL_DIR)/,$(LX_FILES))

content: $(MIRRORED_FROM_PORT_DIR)
$(MIRRORED_FROM_PORT_DIR):
	mkdir -p $(dir $@)
	cp -r $(addprefix $(PORT_DIR)/,$@) $@

content: LICENSE
LICENSE:
	cp $(PORT_DIR)/linux-imx/COPYING $@
