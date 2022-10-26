DRIVER := gpu/imx8mq

MIRROR_FROM_OS_DIR := include/gpu/info_etnaviv.h

content: $(MIRROR_FROM_OS_DIR)

$(MIRROR_FROM_OS_DIR):
	mkdir -p $(dir $@)
	cp $(GENODE_DIR)/repos/os/$@ $@


include $(REP_DIR)/recipes/src/linux_mnt_reform2_drv_content.inc
