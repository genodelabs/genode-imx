SRC_C += lx_emul/shadow/arch/arm64/kernel/smp.c
SRC_C += lx_emul/shadow/arch/arm64/mm/ioremap.c
SRC_S += lx_kit/spec/arm_64/setjmp.S

LX_BUILD_DIR := $(REP_DIR)/src/include/mnt_reform2_linux/spec/arm_v8/lx_generated

include $(REP_DIR)/src/drivers/linux_mnt_reform2_drv_target.inc

vpath % $(REP_DIR)/src/lib/mnt_reform2_linux/spec/arm_v8

INC_DIR += $(REP_DIR)/src/include/mnt_reform2_linux/spec/arm_v8
INC_DIR += $(DDE_LINUX_DIR)/src/include
INC_DIR += $(DDE_LINUX_DIR)/src/include/spec/arm_64
INC_DIR += $(DDE_LINUX_DIR)/src/include/lx_emul/shadow/arch/arm64/include
INC_DIR += $(DDE_LINUX_DIR)/src/include/lx_emul/shadow/include

INC_DIR += $(LX_CONTRIB_DIR)/arch/arm64/include
INC_DIR += $(LX_BUILD_DIR)/arch/arm64/include/generated
INC_DIR += $(LX_CONTRIB_DIR)/include
INC_DIR += $(LX_BUILD_DIR)/include
INC_DIR += $(LX_CONTRIB_DIR)/arch/arm64/include/uapi
INC_DIR += $(LX_BUILD_DIR)/arch/arm64/include/generated/uapi
INC_DIR += $(LX_CONTRIB_DIR)/include/uapi
INC_DIR += $(LX_BUILD_DIR)/include/generated/uapi
INC_DIR += $(LX_CONTRIB_DIR)/scripts/dtc/libfdt

INC_DIR += $(LX_BUILD_DIR)/lib

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
