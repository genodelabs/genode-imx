REQUIRES = hw

REP_INC_DIR += src/bootstrap/board/imx53_qsb

SRC_CC  += bootstrap/spec/arm/cortex_a8_mmu.cc
SRC_CC  += bootstrap/spec/arm/cpu.cc
SRC_CC  += bootstrap/spec/arm/imx_tzic.cc

vpath %.cc $(REP_DIR)/src

include $(call select_from_repositories,lib/mk/spec/arm_v7/bootstrap-hw.inc)
