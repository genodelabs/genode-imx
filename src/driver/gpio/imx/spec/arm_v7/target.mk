TARGET   = imx_gpio
REQUIRES = arm_v7
SRC_CC   = main.cc
LIBS     = base
INC_DIR += $(REP_DIR)/src/driver/gpio/imx

vpath main.cc $(REP_DIR)/src/driver/gpio/imx
