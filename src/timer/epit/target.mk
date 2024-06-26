TARGET   = imx6_timer
REQUIRES = arm_v7
SRC_CC  += main.cc
LIBS    += base

REP_INC_DIR += src/include

vpath main.cc $(dir $(call select_from_repositories,src/timer/epit/main.cc))
