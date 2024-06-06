MIRRORED_FROM_REP_DIR := src/include/spec/arm_v8a/lx_emul \
                         src/driver/nic/stmmac

content: $(MIRRORED_FROM_REP_DIR)
$(MIRRORED_FROM_REP_DIR):
	$(mirror_from_rep_dir)

PORT_DIR := $(call port_dir,$(REP_DIR)/ports/linux-imx)

content: LICENSE
LICENSE:
	cp $(PORT_DIR)/linux-imx/COPYING $@
