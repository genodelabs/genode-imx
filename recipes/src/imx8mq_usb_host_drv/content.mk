DRIVER := usb_host/imx8mq

MIRROR_FROM_OS_DIR := src/lib/genode_c_api/usb.cc

content: $(MIRROR_FROM_OS_DIR)

$(MIRROR_FROM_OS_DIR):
	mkdir -p $(dir $@)
	cp -r $(GENODE_DIR)/repos/os/$@ $@

include $(REP_DIR)/recipes/src/linux_mnt_reform2_drv_content.inc
