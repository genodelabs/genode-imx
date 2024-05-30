TARGET   = imx_gpio
REQUIRES = arm_v8
SRC_CC   = main.cc
LIBS     = base
INC_DIR += $(REP_DIR)/src/drivers/gpio/imx

vpath main.cc $(REP_DIR)/src/drivers/gpio/imx
