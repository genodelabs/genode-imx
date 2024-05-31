content: src/driver/i2c LICENSE

src/driver/i2c:
	mkdir -p $@
	cp -r $(GENODE_DIR)/repos/os/$@/* $@/

LICENSE:
	cp $(GENODE_DIR)/LICENSE $@
