content: src/drivers/i2c LICENSE

src/drivers/i2c:
	mkdir -p $@
	cp -r $(GENODE_DIR)/repos/os/$@/* $@/

LICENSE:
	cp $(GENODE_DIR)/LICENSE $@
