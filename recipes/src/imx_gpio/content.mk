content: src/driver/gpio/imx include/gpio LICENSE

src/driver/gpio/imx:
	$(mirror_from_rep_dir)

include/gpio:
	mkdir -p include
	cp -r $(GENODE_DIR)/repos/os/include/gpio $@

LICENSE:
	cp $(GENODE_DIR)/LICENSE $@
