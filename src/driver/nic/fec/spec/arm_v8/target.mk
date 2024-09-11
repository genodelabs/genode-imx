REQUIRES := arm_v8a
SRC_C    += spec/arm_v8/dummies.c
SRC_C    += lx_emul/shadow/drivers/base/power/runtime.c
SRC_C    += gpio.c

CC_OPT_gpio   = -DKBUILD_MODFILE='"gpio"'
CC_OPT_gpio  += -DKBUILD_BASENAME='"gpio"'
CC_OPT_gpio  += -DKBUILD_MODNAME='"gpio"'

# Driver-specific device-tree binary data
BOARDS                       := mnt_reform2 imx8q_evk imx8mp_iot_gate
DTS_PATH(mnt_reform2)        := arch/arm64/boot/dts/freescale/imx8mq-mnt-reform2.dts
DTS_EXTRACT(mnt_reform2)     := --select fec1
DTS_PATH(imx8q_evk)          := arch/arm64/boot/dts/freescale/imx8mq-evk.dts
DTS_EXTRACT(imx8q_evk)       := --select fec1
DTS_PATH(imx8mp_iot_gate)    := arch/arm64/boot/dts/compulab/iot-gate-imx8plus.dts
DTS_EXTRACT(imx8mp_iot_gate) := --select fec

include $(REP_DIR)/src/driver/nic/fec/target.inc
