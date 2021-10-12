content: drivers.config event_filter.config en_us.chargen \
         special.chargen numlock_remap.config gpu_drv.config

drivers.config numlock_remap.config event_filter.config:
	cp $(REP_DIR)/recipes/raw/drivers_managed-mnt_reform2/$@ $@

en_us.chargen special.chargen:
	cp $(GENODE_DIR)/repos/os/src/server/event_filter/$@ $@

gpu_drv.config:
	echo "<config/>" > $@
