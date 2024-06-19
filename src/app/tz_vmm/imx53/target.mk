TARGET   = imx53_qsb_tz_vmm
REQUIRES = hw arm_v7a
LIBS    += base
INC_DIR += $(PRG_DIR)
SRC_CC  += serial_driver.cc block_driver.cc vm.cc main.cc

CC_CXX_WARN_STRICT =
