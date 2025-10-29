PORT_DIR := $(call port_dir,$(GENODE_DIR)/repos/dde_linux/ports/linux-firmware)

content: ucode_files LICENSE.wifi imx8mp_qcacld2_wifi_firmware.tar


.PHONY: ucode_files
ucode_files:
	cp -R $(PORT_DIR)/firmware/qca9377 .
	cp -R $(PORT_DIR)/firmware/wlan .
	cp $(PORT_DIR)/firmware/regulatory.db .
	cp $(PORT_DIR)/firmware/regulatory.db.p7s .

LICENSE.wifi:
	for i in $(addprefix $(PORT_DIR)/firmware/,LICENSE.qca_firmware notice.txt); do \
	echo "$${i##*/}:" >> $@; \
	  cat $$i >> $@; \
	  echo >> $@; \
	done

include $(GENODE_DIR)/repos/base/recipes/content.inc

imx8mp_qcacld2_wifi_firmware.tar: ucode_files LICENSE.wifi
	$(TAR) --remove-files -cf $@ -C . qca9377/* wlan/* && rmdir qca9377 wlan
