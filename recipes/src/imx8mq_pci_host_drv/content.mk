SRC_DIR = src/drivers/pci_host/imx8mq
include $(GENODE_DIR)/repos/base/recipes/src/content.inc

content: include/pci

include/pci:
	mkdir -p include
	cp -r $(GENODE_DIR)/repos/os/$@ include/
