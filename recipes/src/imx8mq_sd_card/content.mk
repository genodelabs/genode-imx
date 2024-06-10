MIRROR_FROM_OS_DIR := src/lib/genode_c_api/block.cc

content: $(MIRROR_FROM_OS_DIR)

$(MIRROR_FROM_OS_DIR):
	mkdir -p $(dir $@)
	cp -r $(GENODE_DIR)/repos/os/$@ $@

MIRRORED_FROM_REP_DIR := src/include/spec/arm_v8a/lx_emul \
                         src/driver/sd_card/imx8mq

content: $(MIRRORED_FROM_REP_DIR)
$(MIRRORED_FROM_REP_DIR):
	$(mirror_from_rep_dir)

PORT_DIR := $(call port_dir,$(REP_DIR)/ports/linux-imx)

content: LICENSE
LICENSE:
	cp $(PORT_DIR)/linux-imx/COPYING $@
