REP_INC_DIR += src/core/board/mnt_pocket

# include less specific configuration
include $(call select_from_repositories,lib/mk/spec/arm_v8/core-hw-imx8.inc)
