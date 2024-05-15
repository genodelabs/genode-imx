$(call check_tool,aarch64-linux-gnu-gcc)

TARGET   := memtool.target
REQUIRES := arm_64

CUSTOM_TARGET_DEPS := memtool_build.phony

MT_DIR := $(call select_from_ports,memtool)/memtool
PWD    := $(shell pwd)

# filter for make output of kernel build system
BUILD_OUTPUT_FILTER = 2>&1 | sed "s/^/      [Memtool]  /"

Makefile:
	$(MSG_CONFIG)Memtool
	$(VERBOSE)cp -r $(MT_DIR)/* $(PWD)/
	$(VERBOSE)autoreconf -fi
	$(VERBOSE)./configure --host=x86_64-linux --build==aarch64-linux-gnu  CC=aarch64-linux-gnu-gcc CFLAGS="-static"

memtool_build.phony: Makefile
	$(MSG_BUILD)Memtool
	$(VERBOSE)$(MAKE)

