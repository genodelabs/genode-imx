TARGET  := imx8mq_gpu_drv
REQUIRES = arm_v8a
LIBS     = base
INC_DIR := $(PRG_DIR)
INC_DIR += $(PRG_DIR)/include/lx_emul/shadow
SRC_CC  := main.cc
SRC_CC  += emul.cc
SRC_CC  += time.cc
SRC_C   := dummies.c
SRC_C   += lx_emul.c
SRC_C   += $(notdir $(wildcard $(PRG_DIR)/generated_dummies.c))

# Driver-specific device-tree binary data
BOARDS                   := mnt_reform2 imx8q_evk
DTS_PATH(mnt_reform2)    := arch/arm64/boot/dts/freescale/imx8mq-mnt-reform2.dts
DTS_EXTRACT(mnt_reform2) := --select gpu --select pinctrl_i2c1
DTS_PATH(imx8q_evk)      := arch/arm64/boot/dts/freescale/imx8mq-evk.dts
DTS_EXTRACT(imx8q_evk)   := --select gpu --select pinctrl_i2c1

include $(REP_DIR)/src/drivers/linux_mnt_reform2_drv_target.inc
