REQUIRES = arm_v8a
SRC_C    = spec/arm_v8/dummies.c

# Driver-specific device-tree binary data
BOARDS                   := mnt_reform2 imx8q_evk
DTS_PATH(mnt_reform2)    := arch/arm64/boot/dts/freescale/imx8mq-mnt-reform2.dts
DTS_EXTRACT(mnt_reform2) := --select fec1
DTS_PATH(imx8q_evk)      := arch/arm64/boot/dts/freescale/imx8mq-evk.dts
DTS_EXTRACT(imx8q_evk)   := --select fec1

include $(REP_DIR)/src/driver/nic/fec/target.inc
include $(REP_DIR)/src/driver/linux_mnt_reform2_drv_target_arm_v8.inc
