content: drivers.config devices

devices:
	cp $(REP_DIR)/board/imx7d_sabre/$@ $@

drivers.config:
	cp $(REP_DIR)/recipes/raw/drivers_nic-imx7d_sabre/$@ $@
