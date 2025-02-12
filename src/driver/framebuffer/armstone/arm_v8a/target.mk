DRIVER   := imx8mp_armstone_fb
TARGET   := $(DRIVER)
REQUIRES := arm_v8a
LIBS     := base blit fus_linux_generated jitterentropy

INC_DIR  := $(PRG_DIR) $(REP_DIR)/src/driver/framebuffer/imx8mq

LX_SRC_DIR := $(call select_from_ports,fus_linux)/fus-linux
ifeq ($(wildcard $(LX_SRC_DIR)),)
LX_SRC_DIR := $(call select_from_repositories,fus-linux)
endif

LX_GEN_DIR := $(LIB_CACHE_DIR)/fus_linux_generated

include $(call select_from_repositories,lib/import/import-lx_emul_common.inc)

INC_DIR += $(LX_SRC_DIR)/scripts/dtc/libfdt

SRC_CC  += i2c.cc
SRC_CC  += power.cc
SRC_CC  += lx_emul/clock.cc
SRC_CC  += lx_emul/io_mem.cc
SRC_CC  += lx_emul/io_port.cc
SRC_CC  += lx_emul/irq.cc
SRC_CC  += lx_emul/random.cc
SRC_CC  += lx_kit/device.cc
SRC_CC  += lx_kit/memory_dma.cc
SRC_CC  += main.cc
SRC_CC  += reset.cc
SRC_C   += $(notdir $(wildcard $(PRG_DIR)/generated_dummies.c))
SRC_C   += dummies.c
SRC_C   += clk.c
SRC_C   += fb.c
SRC_C   += gpcv2.c
SRC_C   += gpio-mxc.c
SRC_C   += i2c_imx.c
SRC_C   += lx_emul.c
SRC_C   += lx_emul/common_dummies.c
SRC_C   += lx_emul/shadow/arch/arm64/kernel/smp.c
SRC_C   += lx_emul/shadow/arch/arm64/mm/ioremap.c
SRC_C   += runtime.c
SRC_C   += lx_emul/shadow/kernel/dma/mapping.c
SRC_C   += lx_emul/shadow/kernel/irq/spurious.c
SRC_C   += lx_emul/shadow/kernel/rcu/srcutree.c
SRC_C   += lx_emul/shadow/lib/cpumask.c
SRC_C   += lx_emul/shadow/lib/devres.c
SRC_C   += lx_emul/shadow/lib/smp_processor_id.c
SRC_C   += lx_emul/shadow/mm/memblock.c
SRC_C   += lx_emul/shadow/mm/page_alloc.c
SRC_C   += lx_emul/shadow/mm/slab_common.c
SRC_C   += lx_emul/shadow/mm/slub.c
SRC_C   += lx_user.c
SRC_C   += pinctrl.c

CC_OPT_gpio-mxc := -DKBUILD_MODFILE='"gpio_mxc"'
CC_OPT_gpio-mxc += -DKBUILD_BASENAME='"gpio_mxc"'
CC_OPT_gpio-mxc += -DKBUILD_MODNAME='"gpio_mxc"'

CC_OPT_i2c_imx := -DKBUILD_MODFILE='"i2c_imx"'
CC_OPT_i2c_imx += -DKBUILD_BASENAME='"i2c_imx"'
CC_OPT_i2c_imx += -DKBUILD_MODNAME='"i2c_imx"'

CC_OPT_regulator-fixed := -DKBUILD_MODFILE='"regulator_fixed"'
CC_OPT_regulator-fixed += -DKBUILD_BASENAME='"regulator_fixed"'
CC_OPT_regulator-fixed += -DKBUILD_MODNAME='"regulator_fixed"'

CC_OPT_drivers/base/regmap/regmap += -I$(LX_SRC_DIR)/drivers/base/regmap

CC_OPT_clk += -I$(LX_SRC_DIR)/drivers/clk/imx

CC_OPT_drivers/gpu/drm/imx/lcdif/lcdif-crtc += -I$(LX_SRC_DIR)/drivers/gpu/drm/imx
CC_OPT_drivers/gpu/drm/imx/lcdifv3/lcdifv3-crtc += -I$(LX_SRC_DIR)/drivers/gpu/drm/imx
CC_OPT_drivers/gpu/drm/imx/dpu/dpu-blit += -I$(LX_SRC_DIR)/drivers/gpu/drm/imx
CC_OPT_drivers/gpu/imx/dpu-blit/dpu-blit += -I$(LX_SRC_DIR)/drivers/gpu/imx/dpu

# Turn off some warnings
CC_OPT_drivers/gpu/drm/drm_plane_helper += -Wno-uninitialized
CC_OPT_drivers/video/fbdev/core/fbmem   += -Wno-incompatible-pointer-types

vpath lx_emul/common_dummies.c $(REP_DIR)/src/lib/imx
vpath fb.c                     $(PRG_DIR)
vpath main.cc                  $(PRG_DIR)
vpath lx_emul.c                $(PRG_DIR)
vpath dummies.c                $(PRG_DIR)
vpath generated_dummies.c      $(PRG_DIR)
vpath %                        $(REP_DIR)/src/driver/framebuffer/imx8mq

#
# Generate driver-specific device-tree binary data
#
# The rules below use the tool/dts/extract tool to generate a device tree
# containing the driver parameters for a given board.
#
# The resulting dtb file is named <driver>-<board>.dtb
#

BOARDS                       := imx8mp_armstone
DTS_EXTRACT(imx8mp_armstone) := --select hdmi --select lcdif3 --select hdmi_pavi --select backlight_ldb --select display_subsystem
DTS_PATH(imx8mp_armstone)    := arch/arm64/boot/dts/F+S/armstonemx8mp.dts

CUSTOM_TARGET_DEPS += $(addprefix $(INSTALL_DIR)/$(DRIVER)-,$(addsuffix .dtb,$(BOARDS)))

$(INSTALL_DIR)/%.dtb: %.dtb
	$(VERBOSE)cp -f $< $@

%.dtb: %.dts
	$(VERBOSE)dtc -Idts $< > $@

# dependencies of driver-specifc dts files from board's dts files
$(foreach B,$(BOARDS),$(eval $(DRIVER)-$B.dts: $(LX_SRC_DIR)/${DTS_PATH($B)}))

# dependencies of driver-specifc dts files from target-description files
$(foreach B,$(BOARDS),$(eval $(DRIVER)-$B.dts: $(MAKEFILE_LIST)))

dts_include/fsversion.h:
	$(VERBOSE)mkdir -p dts_include
	$(VERBOSE)echo '#define FS_LINUX_VERSION ""' > $@

$(DRIVER)-%.dts: dts_include/fsversion.h
	$(VERBOSE)$(CROSS_DEV_PREFIX)cpp -I$(LX_SRC_DIR)/include -Idts_include \
	          -x assembler-with-cpp -MMD -P $(LX_SRC_DIR)/${DTS_PATH($*)} |\
	          sed -s 's/aliases {/aliases\: aliases {/' | \
	          sed -s 's/interrupt-parent = <\&gpc>;/interrupt-parent = <\&gic>;/' | \
	          sed -s 's/display-subsystem {/display_subsystem: display-subsystem {/' | \
	    $(BASE_DIR)/../../tool/dts/extract ${DTS_EXTRACT($*)} - |\
	    grep -v "/omit-if-no-ref/" > $@

#
# Declare driver target and dtb files as build artifacts
#
BUILD_ARTIFACTS := $(TARGET) $(addprefix $(DRIVER)-,$(addsuffix .dtb,$(BOARDS)))
