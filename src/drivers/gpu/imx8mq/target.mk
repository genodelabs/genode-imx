DRIVER   := imx8mq_gpu_drv
TARGET   := $(DRIVER)
REQUIRES := arm_v8a
LIBS     := base imx_linux_generated imx_lx_emul jitterentropy
INC_DIR  := $(PRG_DIR)
INC_DIR  += $(PRG_DIR)/include/lx_emul/shadow

SRC_CC   := main.cc
SRC_CC   += emul.cc
SRC_CC   += lx_emul/random.cc
SRC_CC   += lx_emul/shared_dma_buffer.cc

SRC_C    := dummies.c
SRC_C    += lx_emul.c
SRC_C    += lx_emul/shadow/drivers/base/power/runtime.c
SRC_C    += lx_emul/shadow/drivers/char/random.c
SRC_C    += lx_user.c
SRC_C    += $(notdir $(wildcard $(PRG_DIR)/generated_dummies.c))

CC_OPT_drivers/base/regmap/regmap   += -I$(LX_SRC_DIR)/drivers/base/regmap


# Driver-specific device-tree binary data
BOARDS                   := mnt_reform2 imx8q_evk
DTS_PATH(mnt_reform2)    := arch/arm64/boot/dts/freescale/imx8mq-mnt-reform2.dts
DTS_EXTRACT(mnt_reform2) := --select gpu --select pinctrl_i2c1
DTS_PATH(imx8q_evk)      := arch/arm64/boot/dts/freescale/imx8mq-evk.dts
DTS_EXTRACT(imx8q_evk)   := --select gpu --select pinctrl_i2c1
