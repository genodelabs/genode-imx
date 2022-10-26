PORT_DIR := $(call port_dir,$(REP_DIR)/ports/mnt_reform2_linux)

LX_FILE_LISTS := $(shell find -H $(REP_DIR)/src/drivers/$(DRIVER) -name deps.list -or -name source.list)
MIRROR_FROM_PORT_DIR := $(sort $(addprefix linux/,$(shell cat $(LX_FILE_LISTS))))

MIRROR_FROM_DDE_DIR  := src/include/lx_emul \
                        src/include/lx_kit \
                        src/include/lx_user \
                        src/include/spec/arm/lx_kit \
                        src/include/spec/arm_64/lx_kit \
                        src/lib/lx_emul \
                        src/lib/lx_kit

MIRROR_FROM_REP_DIR  := src/drivers/$(DRIVER) \
                        src/drivers/linux_mnt_reform2_drv_target.inc \
                        src/drivers/linux_mnt_reform2_drv_target_arm_v7.inc \
                        src/drivers/linux_mnt_reform2_drv_target_arm_v8.inc \
                        src/include/mnt_reform2_linux \
                        src/lib/mnt_reform2_linux

content: LICENSE $(MIRROR_FROM_REP_DIR) $(MIRROR_FROM_PORT_DIR) $(MIRROR_FROM_DDE_DIR)

$(MIRROR_FROM_REP_DIR):
	$(mirror_from_rep_dir)

$(MIRROR_FROM_PORT_DIR):
	mkdir -p $(dir $@)
	cp $(PORT_DIR)/$@ $@

$(MIRROR_FROM_DDE_DIR):
	mkdir -p $(dir $@)
	cp -r $(GENODE_DIR)/repos/dde_linux/$@ $@

LICENSE:
	( echo "GNU General Public License version 2, see:"; \
	  echo "https://www.kernel.org/pub/linux/kernel/COPYING" ) > $@
