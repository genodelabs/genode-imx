REQUIRES = hw

REP_INC_DIR += src/bootstrap/board/mnt_pocket

SRC_CC  += bootstrap/board/mnt_pocket/platform.cc
SRC_CC  += bootstrap/spec/arm/gicv3.cc
SRC_CC  += bootstrap/spec/arm_64/cortex_a53_mmu.cc

vpath bootstrap/% $(REP_DIR)/src

include $(call select_from_repositories,lib/mk/spec/arm_v8/bootstrap-hw.inc)
