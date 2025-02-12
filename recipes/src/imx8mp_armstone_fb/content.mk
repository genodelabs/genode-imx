#
# Content hosted in the dde_linux repository
#

MIRRORED_FROM_DDE_LINUX := src/lib/lx_emul \
                           src/lib/lx_kit \
                           src/include/lx_emul \
                           src/include/lx_user \
                           src/include/spec/arm_v8/lx_kit \
                           src/include/lx_kit \
                           lib/import/import-lx_emul_common.inc

content: $(MIRRORED_FROM_DDE_LINUX)
$(MIRRORED_FROM_DDE_LINUX):
	mkdir -p $(dir $@); cp -r $(GENODE_DIR)/repos/dde_linux/$@ $(dir $@)


#
# Content hosted in the imx repository
#

MIRRORED_FROM_REP_DIR := lib/mk/spec/arm_v8/fus_linux_generated.mk \
                         src/fus_linux/arm_v8a/target.inc \
                         src/include/spec/arm_v8a/lx_emul \
                         src/driver/framebuffer/imx8mq \
                         src/driver/framebuffer/armstone \
                         src/lib/imx/lx_emul


content: $(MIRRORED_FROM_REP_DIR)
$(MIRRORED_FROM_REP_DIR):
	$(mirror_from_rep_dir)


#
# Content from the Linux source tree
#

PORT_DIR := $(call port_dir,$(REP_DIR)/ports/fus_linux)
LX_REL_DIR := fus-linux
LX_ABS_DIR := $(addsuffix /$(LX_REL_DIR),$(PORT_DIR))

LX_FILES += $(shell cd $(LX_ABS_DIR); find -name "Kbuild*" -printf "%P\n")
LX_FILES += $(shell cd $(LX_ABS_DIR); find -name "Kconfig*" -printf "%P\n")
LX_FILES += $(shell cd $(LX_ABS_DIR); find -name "Makefile*" -printf "%P\n")

# add content listed in the repository's source.list or dep.list files
LX_FB_FILE_LISTS := $(REP_DIR)/src/driver/framebuffer/armstone/arm_v8a/dep.list \
                    $(REP_DIR)/src/driver/framebuffer/armstone/arm_v8a/source.list
LX_FILES += $(shell cat $(LX_FB_FILE_LISTS))
LX_FILES := $(sort $(LX_FILES))
MIRRORED_FROM_PORT_DIR += $(addprefix $(LX_REL_DIR)/,$(LX_FILES))

content: $(MIRRORED_FROM_PORT_DIR)
$(MIRRORED_FROM_PORT_DIR):
	mkdir -p $(dir $@)
	cp -r $(addprefix $(PORT_DIR)/,$@) $@

content: LICENSE
LICENSE:
	cp $(PORT_DIR)/fus-linux/COPYING $@
