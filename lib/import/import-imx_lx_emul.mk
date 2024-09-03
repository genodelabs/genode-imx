# check for installation of device-tree compiler
$(call check_tool,dtc)

LIBS    += imx_linux_generated

INC_DIR += $(PRG_DIR)

SRC_C   += dummies.c lx_emul.c
SRC_C   += $(notdir $(wildcard $(PRG_DIR)/generated_dummies.c))

ifeq ($(filter-out $(SPECS),arm_64),)
# lx_emul/initcall_order.h
INC_DIR += $(REP_DIR)/src/include/spec/arm_v8a
SRC_C   += lx_emul/shadow/arch/arm64/kernel/smp.c
SRC_C   += lx_emul/shadow/arch/arm64/mm/ioremap.c
endif

ifeq ($(filter-out $(SPECS),arm),)
# lx_emul/initcall_order.h
INC_DIR += $(REP_DIR)/src/include/spec/arm_v7a

# prevent unsupported instruction on Cortex-A8 in .S files
CC_OPT += -DGENODE_PREVENT_PLDW=1
endif

LX_SRC_DIR := $(call select_from_ports,linux-imx)/linux-imx
ifeq ($(wildcard $(LX_SRC_DIR)),)
LX_SRC_DIR := $(call select_from_repositories,linux-imx)
endif

LX_GEN_DIR := $(LIB_CACHE_DIR)/imx_linux_generated

include $(call select_from_repositories,lib/import/import-lx_emul_common.inc)

INC_DIR += $(LX_SRC_DIR)/scripts/dtc/libfdt

#
# Additional Lx_emul + Lx_kit definitions
#

SRC_CC  += lx_emul/clock.cc
SRC_CC  += lx_emul/io_mem.cc
SRC_CC  += lx_emul/io_port.cc
SRC_CC  += lx_emul/irq.cc
SRC_C   += lx_emul/shadow/drivers/clk/clk.c
SRC_C   += lx_emul/shadow/drivers/clk/clkdev.c
SRC_C   += lx_emul/shadow/kernel/dma/mapping.c
SRC_C   += lx_emul/shadow/kernel/irq/spurious.c
SRC_C   += lx_emul/shadow/kernel/rcu/srcutree.c
SRC_C   += lx_emul/shadow/lib/devres.c
SRC_C   += lx_emul/shadow/lib/smp_processor_id.c
SRC_C   += lx_emul/shadow/mm/memblock.c
SRC_C   += lx_emul/shadow/mm/page_alloc.c
SRC_C   += lx_emul/shadow/mm/slab_common.c
SRC_C   += lx_emul/shadow/mm/slub.c
SRC_CC  += lx_kit/device.cc
SRC_CC  += lx_kit/memory_dma.cc

#
# Generate driver-specific device-tree binary data
#
# The rules below use the tool/dts/extract tool to generate a device tree
# containing the driver parameters for a given board.
#
# The resulting dtb file is named <driver>-<board>.dtb
#

DTS_PATH(mnt_reform2)     := arch/arm64/boot/dts/freescale/imx8mq-mnt-reform2.dts
DTS_PATH(imx53_qsb)       := arch/arm/boot/dts/nxp/imx/imx53-qsb.dts
DTS_PATH(imx6q_sabrelite) := arch/arm/boot/dts/nxp/imx/imx6q-sabrelite.dts
DTS_PATH(imx7d_sabre)     := arch/arm/boot/dts/nxp/imx/imx7d-sdb.dts

CUSTOM_TARGET_DEPS += $(addprefix $(INSTALL_DIR)/$(DRIVER)-,$(addsuffix .dtb,$(BOARDS)))

$(INSTALL_DIR)/%.dtb: %.dtb
	$(VERBOSE)cp -f $< $@

%.dtb: %.dts
	$(VERBOSE)dtc -Idts $< > $@

# dependencies of driver-specifc dts files from board's dts files
$(foreach B,$(BOARDS),$(eval $(DRIVER)-$B.dts: $(LX_SRC_DIR)/${DTS_PATH($B)}))

# dependencies of driver-specifc dts files from target-description files
$(foreach B,$(BOARDS),$(eval $(DRIVER)-$B.dts: $(MAKEFILE_LIST)))

$(DRIVER)-%.dts:
	$(VERBOSE)$(CROSS_DEV_PREFIX)cpp -I$(LX_SRC_DIR)/include \
	          -x assembler-with-cpp -MMD -P $(LX_SRC_DIR)/${DTS_PATH($*)} |\
	          sed -s 's/aliases {/aliases\: aliases {/' | \
	          sed -s 's/intc\:/gic\:/' | \
	          sed -s 's/interrupt-parent = <\&intc>;/interrupt-parent = <\&gic>;/' | \
	          sed -s 's/interrupt-parent = <\&gpc>;/interrupt-parent = <\&gic>;/' | \
	          sed -s '/phy-reset-gpios =.*extended_io.*$$/d;' | \
	    $(BASE_DIR)/../../tool/dts/extract ${DTS_EXTRACT($*)} - |\
	    grep -v "/omit-if-no-ref/" > $@

#
# Declare driver target and dtb files as build artifacts
#
BUILD_ARTIFACTS := $(TARGET) $(addprefix $(DRIVER)-,$(addsuffix .dtb,$(BOARDS)))
