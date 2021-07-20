PORT_DIR := $(call port_dir,$(REP_DIR)/ports/mnt_reform2_linux)

MIRROR_FROM_PORT_DIR := $(addprefix linux/,$(shell cat $(REP_DIR)/src/drivers/sd_card/imx8mq/source.list)) \
                        $(addprefix linux/,$(shell cat $(REP_DIR)/src/drivers/sd_card/imx8mq/deps.list))

MIRROR_FROM_DDE_DIR  := src/include/lx_emul \
                        src/include/lx_kit \
                        src/include/lx_user \
                        src/include/spec/arm_64/lx_kit \
                        src/lib/lx_emul \
                        src/lib/lx_kit

MIRROR_FROM_REP_DIR  := src/drivers/sd_card/imx8mq \
                        src/include/imx8mq \
                        src/lib/imx8mq

MIRROR_FROM_OS_DIR   := src/lib/genode_c_api/block.cc

content: LICENSE $(MIRROR_FROM_REP_DIR) $(MIRROR_FROM_PORT_DIR) $(MIRROR_FROM_DDE_DIR) $(MIRROR_FROM_OS_DIR)

$(MIRROR_FROM_REP_DIR):
	$(mirror_from_rep_dir)

$(MIRROR_FROM_PORT_DIR):
	mkdir -p $(dir $@)
	cp $(PORT_DIR)/$@ $@

$(MIRROR_FROM_DDE_DIR):
	mkdir -p $(dir $@)
	cp -r $(GENODE_DIR)/repos/dde_linux/$@ $@

$(MIRROR_FROM_OS_DIR):
	mkdir -p $(dir $@)
	cp -r $(GENODE_DIR)/repos/os/$@ $@

LICENSE:
	( echo "GNU General Public License version 2, see:"; \
	  echo "https://www.kernel.org/pub/linux/kernel/COPYING" ) > $@
