TARGET   = imx8mq_fb_drv
REQUIRES = arm_v8a
LIBS     = base blit
INC_DIR  = $(PRG_DIR)
SRC_CC   = i2c.cc
SRC_CC  += main.cc
SRC_CC  += reset.cc
SRC_C    = dummies.c
SRC_C   += fb.c
SRC_C   += i2c_imx.c
SRC_C   += $(notdir $(wildcard $(PRG_DIR)/generated_dummies.c))

CC_OPT_i2c_imx  = -DKBUILD_MODFILE='"i2c_imx"'
CC_OPT_i2c_imx += -DKBUILD_BASENAME='"i2c_imx"'
CC_OPT_i2c_imx += -DKBUILD_MODNAME='"i2c_imx"'


#
# Lx_emul + Lx_kit definitions
#

SRC_CC  += lx_emul/alloc.cc
SRC_CC  += lx_emul/clock.cc
SRC_CC  += lx_emul/debug.cc
SRC_CC  += lx_emul/init.cc
SRC_CC  += lx_emul/io_mem.cc
SRC_CC  += lx_emul/irq.cc
SRC_CC  += lx_emul/log.cc
SRC_CC  += lx_emul/task.cc
SRC_CC  += lx_emul/time.cc

SRC_C   += lx_emul/clocksource.c
SRC_C   += lx_emul/irqchip.c
SRC_C   += lx_emul/start.c
SRC_C   += lx_emul/shadow/arch/arm64/kernel/smp.c
SRC_C   += lx_emul/shadow/arch/arm64/mm/ioremap.c
SRC_C   += lx_emul/shadow/drivers/base/power/common.c
SRC_C   += lx_emul/shadow/drivers/base/power/main.c
SRC_C   += lx_emul/shadow/drivers/base/power/runtime.c
SRC_C   += lx_emul/shadow/drivers/clk/clk.c
SRC_C   += lx_emul/shadow/drivers/clk/clkdev.c
SRC_C   += lx_emul/shadow/fs/exec.c
SRC_C   += lx_emul/shadow/kernel/cpu.c
SRC_C   += lx_emul/shadow/kernel/dma/mapping.c
SRC_C   += lx_emul/shadow/kernel/exit.c
SRC_C   += lx_emul/shadow/kernel/fork.c
SRC_C   += lx_emul/shadow/kernel/irq/spurious.c
SRC_C   += lx_emul/shadow/kernel/locking/spinlock.c
SRC_C   += lx_emul/shadow/kernel/pid.c
SRC_C   += lx_emul/shadow/kernel/printk/printk.c
SRC_C   += lx_emul/shadow/kernel/rcu/srcutree.c
SRC_C   += lx_emul/shadow/kernel/rcu/tree.c
SRC_C   += lx_emul/shadow/kernel/sched/core.c
SRC_C   += lx_emul/shadow/kernel/smp.c
SRC_C   += lx_emul/shadow/kernel/softirq.c
SRC_C   += lx_emul/shadow/kernel/stop_machine.c
SRC_C   += lx_emul/shadow/lib/devres.c
SRC_C   += lx_emul/shadow/lib/smp_processor_id.c
SRC_C   += lx_emul/shadow/mm/memblock.c
SRC_C   += lx_emul/shadow/mm/percpu.c
SRC_C   += lx_emul/shadow/mm/slab_common.c
SRC_C   += lx_emul/shadow/mm/slub.c

SRC_CC  += lx_kit/console.cc
SRC_CC  += lx_kit/device.cc
SRC_CC  += lx_kit/env.cc
SRC_CC  += lx_kit/init.cc
SRC_CC  += lx_kit/memory.cc
SRC_CC  += lx_kit/scheduler.cc
SRC_CC  += lx_kit/task.cc
SRC_CC  += lx_kit/timeout.cc
SRC_S   += lx_kit/spec/arm_64/setjmp.S

INC_DIR += $(REP_DIR)/src/include
INC_DIR += $(REP_DIR)/src/include/spec/arm_64
INC_DIR += $(REP_DIR)/src/include/lx_emul/shadow
INC_DIR += $(PRG_DIR)/lx_generated

vpath % $(REP_DIR)/src/lib


#
# Linux kernel definitions
#

LX_CONTRIB_DIR := $(call select_from_ports,mnt_reform2_linux)/linux
LX_BUILD_DIR   := $(PRG_DIR)/lx_generated

INC_DIR += $(LX_CONTRIB_DIR)/arch/arm64/include
INC_DIR += $(LX_BUILD_DIR)/arch/arm64/include/generated
INC_DIR += $(LX_CONTRIB_DIR)/include
INC_DIR += $(LX_BUILD_DIR)/include
INC_DIR += $(LX_CONTRIB_DIR)/arch/arm64/include/uapi
INC_DIR += $(LX_BUILD_DIR)/arch/arm64/include/generated/uapi
INC_DIR += $(LX_CONTRIB_DIR)/include/uapi
INC_DIR += $(LX_BUILD_DIR)/include/generated/uapi
INC_DIR += $(LX_CONTRIB_DIR)/scripts/dtc/libfdt

CC_C_OPT += -std=gnu89 -include $(LX_CONTRIB_DIR)/include/linux/kconfig.h
CC_C_OPT += -include $(LX_CONTRIB_DIR)/include/linux/compiler_types.h
CC_C_OPT += -D__KERNEL__ -DCONFIG_CC_HAS_K_CONSTRAINT=1
CC_C_OPT += -DKASAN_SHADOW_SCALE_SHIFT=3
CC_C_OPT += -Wall -Wundef -Werror=strict-prototypes -Wno-trigraphs
CC_C_OPT += -Werror=implicit-function-declaration -Werror=implicit-int
CC_C_OPT += -Wno-format-security -Wno-psabi
CC_C_OPT += -Wno-frame-address -Wno-format-truncation -Wno-format-overflow
CC_C_OPT += -Wframe-larger-than=2048 -Wno-unused-but-set-variable -Wimplicit-fallthrough
CC_C_OPT += -Wno-unused-const-variable -Wdeclaration-after-statement -Wvla
CC_C_OPT += -Wno-pointer-sign -Wno-stringop-truncation -Wno-array-bounds -Wno-stringop-overflow
CC_C_OPT += -Wno-restrict -Wno-maybe-uninitialized -Werror=date-time
CC_C_OPT += -Werror=incompatible-pointer-types -Werror=designated-init
CC_C_OPT += -Wno-packed-not-aligned

INC_DIR += $(LX_CONTRIB_DIR)/drivers/base/regmap
INC_DIR += $(LX_BUILD_DIR)/lib

LX_SRC   = $(shell grep ".*\.c" $(PRG_DIR)/source.list)
SRC_S   += $(shell grep ".*\.S" $(PRG_DIR)/source.list)
SRC_C   += $(LX_SRC)
SRC_S   += $(LX_ASM:$(LX_CONTRIB_DIR)/%=%)

vpath %.c $(LX_CONTRIB_DIR)
vpath %.S $(LX_CONTRIB_DIR)

# Define per-compilation-unit CC_OPT defines needed by MODULE* macros in Linux
define CC_OPT_LX_RULES =
CC_OPT_$(1) = -DKBUILD_MODFILE='"$(1)"' -DKBUILD_BASENAME='"$(notdir $(1))"' -DKBUILD_MODNAME='"$(notdir $(1))"'
endef

$(foreach file,$(LX_SRC),$(eval $(call CC_OPT_LX_RULES,$(file:%.c=%))))

# Turn off some warnings
CC_OPT_drivers/gpu/drm/drm_plane_helper    += -Wno-uninitialized
CC_OPT_drivers/gpu/drm/imx/cdn-mhdp-imxdrv += -Wno-unused-variable
