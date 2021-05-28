content: src/drivers/gpio/imx include/gpio LICENSE

src/drivers/gpio/imx:
	mkdir -p $@
	cp -r $(GENODE_DIR)/repos/os/$@/* $@/

include/gpio:
	mkdir -p include
	cp -r $(GENODE_DIR)/repos/os/include/gpio $@

LICENSE:
	cp $(GENODE_DIR)/LICENSE $@
