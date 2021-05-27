PORT_DIR := $(call port_dir,$(REP_DIR)/ports/mnt_reform2_linux)

MIRROR_FROM_PORT_DIR := $(addprefix linux/,$(shell cat $(REP_DIR)/src/drivers/framebuffer/source.list)) \
                        $(addprefix linux/,$(shell cat $(REP_DIR)/src/drivers/framebuffer/deps.list))

MIRROR_FROM_REP_DIR  := src/drivers/framebuffer \
                        src/include/lx_emul \
                        src/include/lx_kit \
                        src/include/spec/arm_64/lx_kit \
                        src/lib/lx_emul \
                        src/lib/lx_kit

content: LICENSE $(MIRROR_FROM_REP_DIR) $(MIRROR_FROM_PORT_DIR)

$(MIRROR_FROM_REP_DIR):
	$(mirror_from_rep_dir)

$(MIRROR_FROM_PORT_DIR):
	mkdir -p $(dir $@)
	cp $(PORT_DIR)/$@ $@

LICENSE:
	( echo "GNU General Public License version 2, see:"; \
	  echo "https://www.kernel.org/pub/linux/kernel/COPYING" ) > $@
