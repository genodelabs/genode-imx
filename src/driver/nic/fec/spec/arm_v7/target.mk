REQUIRES := arm_v7a
SRC_C    += spec/arm_v7/dummies.c
SRC_C    += spec/arm_v7/lx_emul.c

# Driver-specific device-tree binary data
BOARDS                       := imx53_qsb imx6q_sabrelite imx7d_sabre
DTS_PATH(imx53_qsb)          := arch/arm/boot/dts/nxp/imx/imx53-qsb.dts
DTS_EXTRACT(imx53_qsb)       := --select fec
DTS_PATH(imx6q_sabrelite)    := arch/arm/boot/dts/nxp/imx/imx6q-sabrelite.dts
DTS_EXTRACT(imx6q_sabrelite) := --select fec
DTS_PATH(imx7d_sabre)        := arch/arm/boot/dts/nxp/imx/imx7d-sdb-reva.dts
DTS_EXTRACT(imx7d_sabre)     := --select fec1 --select fec2 --select i2c1

CC_OPT_arch/arm/lib/testsetbit   += -include asm/unified.h
CC_OPT_arch/arm/lib/testclearbit += -include asm/unified.h
CC_OPT_arch/arm/lib/clearbit     += -include asm/unified.h
CC_OPT_arch/arm/lib/setbit       += -include asm/unified.h
CC_OPT_arch/arm/lib/findbit      += -include asm/unified.h
CC_OPT_arch/arm/lib/csumpartial  += -include asm/unified.h
CC_OPT_arch/arm/lib/div64        += -include asm/unified.h

include $(REP_DIR)/src/driver/nic/fec/target.inc
