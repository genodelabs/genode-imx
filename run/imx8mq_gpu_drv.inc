assert_spec arm_v8a

create_boot_directory

set imports { }

lappend imports [depot_user]/src/[base_src]
lappend imports [depot_user]/src/init
lappend imports [depot_user]/pkg/drivers_managed-[board]
lappend imports [depot_user]/src/nitpicker
lappend imports [depot_user]/src/report_rom
lappend imports [depot_user]/src/arm_driver_manager
lappend imports [depot_user]/raw/glmark2
lappend imports [depot_user]/pkg/fonts_fs

import_from_depot $imports

set build_components {
	drivers/gpu/imx8mq
	lib/mesa/softpipe
	lib/mesa/etnaviv

	app/glmark2
	test/mesa_demo/gears
}

build $build_components

append config {
<config prio_levels="2" verbose="yes">
	<parent-provides>
		<service name="CPU"/>
		<service name="IRQ"/>
		<service name="IO_MEM"/>
		<service name="IO_PORT"/>
		<service name="LOG"/>
		<service name="PD"/>
		<service name="RM"/>
		<service name="ROM"/>
		<service name="TRACE"/>
	</parent-provides>
	<default caps="100"/>
	<default-route>
		<any-service> <parent/> <any-child/> </any-service>
	</default-route>

	<affinity-space width="4" height="1"/>

	<start name="timer">
		<resource name="RAM" quantum="1M"/>
		<provides><service name="Timer"/></provides>
	</start>

	<start name="report_rom">
		<resource name="RAM" quantum="1M"/>
		<provides> <service name="Report"/> <service name="ROM"/> </provides>
		<config verbose="no"/>
		<route>
			<any-service> <parent/> </any-service>
		</route>
	</start>

	<start name="drivers" caps="2500" managing_system="yes">
		<resource name="RAM" quantum="128M"/>
		<binary name="init"/>
		<provides> <service name="Platform"/> </provides>
		<route>
			<service name="ROM" label="config"> <parent label="drivers.config"/> </service>
			<service name="Timer">   <child name="timer"/> </service>
			<service name="Capture"> <child name="nitpicker"/> </service>
			<service name="Event">   <child name="nitpicker"/> </service>
			<service name="Report">  <child name="report_rom"/> </service>
			<any-service> <parent/> </any-service>
		</route>
	</start>

	<start name="nitpicker" caps="200">
		<resource name="RAM" quantum="2M"/>
		<provides>
			<service name="Gui"/> <service name="Capture"/> <service name="Event"/>
		</provides>
		<config verbose="yes">
			<capture/> <event/>
			<domain name="pointer" layer="1" xpos="1100" ypos="0" content="client" label="no" origin="pointer" />
			<domain name="default" layer="3" content="client" label="no" focus="click" hover="always" />
			<domain name="glmark2" layer="3" xpos="0" ypos="0" content="client" label="no" focus="click" hover="always" />
			<domain name="gears"   layer="3" xpos="800" ypos="300" content="client" label="no" focus="click" hover="always" />
			<domain name="menu_view" layer="2" xpos="10" ypos="540" content="client" label="no" focus="click" hover="always" />
			<policy label_prefix="pointer" domain="pointer"/>
			<policy label_prefix="glmark2" domain="glmark2"/>
			<policy label_prefix="gears"   domain="gears"/>
			<policy label_prefix="menu_view" domain="menu_view"/>
			<default-policy                domain="default"/>
		</config>
		<route><any-service><parent/><any-child/></any-service></route>
	</start>
	<start name="pointer">
		<resource name="RAM" quantum="1M"/>
	</start>

<!--
	<start name="gears" caps="500">
		<affinity xpos="2" width="1"/>
		<binary name="gears"/>
		<resource name="RAM" quantum="160M"/>
		<config ld_verbose="true">
			<libc stdout="/dev/log" stderr="/dev/log" rtc="/dev/rtc" />
			<vfs>
				<dir name="dev">
					<log/> <inline name="rtc">2000-01-01 00:00</inline>
				</dir>
			</vfs>
			<env key="GALLIUM_HUD" value="fps,draw-calls"/>
			<env key="USE_GPU_SESSION" value="yes"/>
		</config>
		<route>
			<service name="Gui"> <child name="nitpicker"/> </service>
			<service name="ROM" label="mesa_gpu_drv.lib.so">
				<parent label="mesa_gpu-etnaviv.lib.so"/>
			</service>
			<any-service> <parent/> <any-child/> </any-service>
		</route>
	</start>
-->

	<start name="glmark2" caps="500">
		<affinity xpos="1" width="1"/>
		<resource name="RAM" quantum="160M"/>
		<config ld_verbose="yes">
			<vfs>
				<dir name="dev">
					<log/>
				</dir>
				<dir name="data">
					<tar name="glmark2_assets.tar"/>
				</dir>
			</vfs>
			<libc stdout="/dev/log" stderr="/dev/log"/>
			<arg value="glmark2"/>
			<arg value="-b"/>
			<arg value=":duration=2.0"/>
			<arg value="-s"/>
			<arg value="800x600"/>
			<env key="GALLIUM_HUD" value="fps,draw-calls"/>
			<env key="USE_GPU_SESSION" value="yes"/>
		</config>
		<route>
			<service name="Gui"> <child name="nitpicker"/> </service>
			<service name="ROM" label="mesa_gpu_drv.lib.so">
				<parent label="mesa_gpu-etnaviv.lib.so"/>
			</service>
			<service name="ROM" label="libEGL.so">
				<parent label="mesa.lib.so"/>
			</service>
			<service name="ROM" label="libGLESv2.so">
				<parent label="mesa.lib.so"/>
			</service>
			<any-service> <parent/> <any-child/> </any-service>
		</route>
	</start>

	<start name="imx8mq_gpu_drv" caps="500">
		<resource name="RAM" quantum="128M"/>
		<provides>
			<service name="Drm"/>
			<service name="Gpu"/>
		</provides>
		<config ld_verbose="yes"/>
		<route>
			<service name="ROM" label="dtb">
				<parent label="} [imx8mq_gpu_dtb_file] {"/>
			</service>
			<service name="Timer"> <child name="timer"/> </service>
			<service name="Gui"> <child name="nitpicker"/> </service>
			<service name="Platform"> <child name="drivers" label="runtime -> gpu"/> </service>
			<any-service> <parent/> </any-service>
		</route>
	</start>

</config>}

install_config $config

if {![file exists bin/usb_policy]} {
	exec echo '<empty/>' > bin/usb_policy
}
if {![file exists bin/numlock]} {
	exec echo '<empty/>' > bin/numlock
}

append boot_modules {
	libc.lib.so vfs.lib.so libm.lib.so
	egl.lib.so mesa.lib.so stdcxx.lib.so
	expat.lib.so glapi.lib.so zlib.lib.so

	imx8mq_gpu_drv

	mesa_gpu-etnaviv.lib.so libdrm.lib.so

	glmark2 jpeg.lib.so libpng.lib.so
	gears

	usb_policy numlock
}

lappend boot_modules [imx8mq_gpu_dtb_file]

build_boot_image $boot_modules

run_genode_until {.* child "glmark2" exited with exit value 0.*} 120
