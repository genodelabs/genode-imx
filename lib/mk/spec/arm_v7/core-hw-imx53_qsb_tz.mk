REP_INC_DIR += src/core/spec/arm_v7/trustzone

SRC_CC += kernel/vcpu_thread_on.cc
SRC_CC += spec/arm_v7/trustzone/kernel/vcpu.cc
SRC_CC += spec/arm_v7/trustzone/platform_services.cc
SRC_CC += spec/arm_v7/trustzone/vm_session_component.cc

SRC_S += spec/arm_v7/trustzone/exception_vector.s

# include less specific configuration
include $(call select_from_repositories,lib/mk/spec/arm_v7/core-hw-imx53_qsb.inc)
