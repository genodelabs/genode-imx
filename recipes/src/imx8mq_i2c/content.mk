content: src/driver/i2c LICENSE

src/driver/i2c:
	mkdir -p $@
	cp -r $(REP_DIR)/$@/* $@/

LICENSE:
	cp $(GENODE_DIR)/LICENSE $@
