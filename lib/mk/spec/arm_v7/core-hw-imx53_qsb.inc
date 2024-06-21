REP_INC_DIR += src/core/board/imx53_qsb

SRC_CC += spec/arm/imx_epit.cc
SRC_CC += spec/arm/imx_tzic.cc

include $(call select_from_repositories,lib/mk/spec/arm_v7/core-hw-imx53.inc)

vpath %.cc $(REP_DIR)/src/core