content: drivers.config devices

devices:
	cp $(REP_DIR)/board/imx53_qsb/$@ $@

drivers.config:
	cp $(REP_DIR)/recipes/raw/drivers_nic-imx53_qsb/$@ $@
