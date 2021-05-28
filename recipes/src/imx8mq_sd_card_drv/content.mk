content: src/drivers/sd_card LICENSE

src/drivers/sd_card:
	mkdir -p $@
	cp -r $(GENODE_DIR)/repos/os/$@/imx  $@/
	cp -r $(GENODE_DIR)/repos/os/$@/imx6 $@/
	cp -r $(GENODE_DIR)/repos/os/$@/imx8 $@/
	cp    $(GENODE_DIR)/repos/os/$@/*.*  $@/

LICENSE:
	cp $(GENODE_DIR)/LICENSE $@
