/*
 * \brief  i.MX8 Pcie host controller driver
 * \author Stefan Kalkowski
 * \date   2021-11-16
 */

/*
 * Copyright (C) 2021-2022 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#include <base/component.h>
#include <base/log.h>
#include <gpio_session/connection.h>
#include <os/reporter.h>
#include <platform_session/device.h>
#include <timer_session/connection.h>
#include <util/xml_generator.h>

#include <pci/config.h>

using namespace Genode;


struct Pcie_controller : Platform::Device::Mmio
{
	enum {
		MEMORY_BASE              = 0,
		MEMORY_SIZE              = 0x7f00000,
		MEMORY_PER_DEVICE        = 0x100000,
		CONFIG_BASE              = MEMORY_BASE + MEMORY_SIZE,
		CONFIG_SIZE              = 0x80000,
		IO_BASE                  = CONFIG_BASE + CONFIG_SIZE,
		IO_SIZE                  = 0x10000,
		BUS_COUNT_PER_CONTROLLER = 16
	};

	enum Transaction_type {
		MEMORY_REQUEST        = 0,
		IO_REQUEST            = 2,
		CONFIG_TYPE_0_REQUEST = 4,
		CONFIG_TYPE_1_REQUEST = 5
	};

	struct Register_64bit : Genode::Register<64>
	{
		struct Lower : Bitfield<0,  32> {};
		struct Upper : Bitfield<32, 32> {};

		static inline uint32_t lower(access_t v) {
			return (uint32_t) Lower::get(v); }

		static inline uint32_t upper(access_t v) {
			return (uint32_t) Upper::get(v); }
	};

	struct Port_link_control : Register<0x710, 32>
	{
		struct Dll_link_enable : Bitfield<5,  1> {};
		struct Fast_link_mode  : Bitfield<7,  1> {};
		struct Link_capable    : Bitfield<16, 6> {};
	};

	struct Port_debug1 : Register<0x72c, 32>
	{
		struct Link_up          : Bitfield<4,  1> {};
		struct Link_in_training : Bitfield<29, 1> {};
	};

	struct Link_width_speed_control : Register<0x80c, 32>
	{
		struct Num_of_lanes        : Bitfield<8,  5> {};
		struct Direct_speed_change : Bitfield<17, 1> {};
	};

	struct Msi_control_address       : Register<0x820, 32> {};
	struct Msi_control_upper_address : Register<0x824, 32> {};
	struct Msi_control_enable        : Register<0x828, 32> {};
	struct Msi_control_mask          : Register<0x82c, 32> {};
	struct Msi_control_status        : Register<0x830, 32> {};

	struct Misc_control1 : Register<0x8bc, 32>
	{
		struct Dbi_ro_wr_enable : Bitfield<0, 1> {};
	};

	struct Atu : Genode::Mmio
	{
		struct Atu_region_control_1 : Register<0x0, 32>
		{
			struct Type     : Bitfield<0,  5> {};
			struct Tc       : Bitfield<5,  3> {};
			struct Td       : Bitfield<8,  1> {};
			struct Attr     : Bitfield<9,  2> {};
			struct At       : Bitfield<16, 2> {};
			struct Function : Bitfield<20, 3> {};
		};

		struct Atu_region_control_2 : Register<0x4, 32>
		{
			struct Shift_mode  : Bitfield<28, 1> {};
			struct Invert_mode : Bitfield<29, 1> {};
			struct Enable      : Bitfield<31, 1> {};
		};

		struct Atu_lower_base_addr   : Register<0x8,  32> {};
		struct Atu_upper_base_addr   : Register<0xc,  32> {};
		struct Atu_limit_addr        : Register<0x10, 32> {};
		struct Atu_lower_target_addr : Register<0x14, 32> {};
		struct Atu_upper_target_addr : Register<0x18, 32> {};

		Atu(addr_t const base) : Genode::Mmio(base) {}

		void configure_outbound(Transaction_type type,
		                        addr_t cpu_addr, size_t size,
		                        addr_t pci_addr)
		{
			typename Atu_region_control_1::access_t ctrl1 = 0;
			Atu_region_control_1::Type::set(ctrl1, type);
			write<Atu_region_control_1>(ctrl1);

			typename Atu_region_control_2::access_t ctrl2 = 0;
			Atu_region_control_2::Enable::set(ctrl2, 1);
			write<Atu_region_control_2>(ctrl2);

			write<Atu_lower_base_addr>(Register_64bit::lower(cpu_addr));
			write<Atu_upper_base_addr>(Register_64bit::upper(cpu_addr));
			write<Atu_limit_addr>(Register_64bit::lower(cpu_addr + size - 1));
			write<Atu_lower_target_addr>(Register_64bit::lower(pci_addr));
			write<Atu_upper_target_addr>(Register_64bit::upper(pci_addr));
		}

		void disable_outbound()
		{
			Atu_region_control_2::access_t ctrl2 = 0;
			Atu_region_control_2::Enable::set(ctrl2, 1);
			write<Atu_region_control_2>(ctrl2);
		}

		bool up() { return read<Atu_region_control_2::Enable>(); }
	} atu[4] { { Platform::Device::Mmio::base() + 0x300000 },
	           { Platform::Device::Mmio::base() + 0x300200 },
	           { Platform::Device::Mmio::base() + 0x300400 },
	           { Platform::Device::Mmio::base() + 0x300600 } };

	Pci::Config_type1 cfg;

	struct Atu_is_not_ready  {};
	struct Link_is_not_ready {};

	Timer::Connection & timer;

	bool link_up()
	{
		return read<Port_debug1::Link_up>() &&
		       !read<Port_debug1::Link_in_training>();
	}

	bool wait_for_link()
	{
		for (unsigned i = 0; i < 10; i++) {
			if (link_up())
				return true;
			timer.msleep(100);
		}
		return false;
	}

	bool wait_for_atu()
	{
		for (unsigned i = 0; i < 10; i++) {
			if (atu[0].up())
				return true;
			timer.msleep(10);
		}
		return true;
	}

	Pcie_controller(Timer::Connection           & timer,
	                Platform::Device            & device,
	                Platform::Device::Mmio::Index i,
	                Pci::bus_t                    bus,
	                addr_t                        io_base)
	: Mmio(device, i),
	  cfg(base()),
	  timer(timer)
	{
		using namespace Pci;

		cfg.scan();

		write<Misc_control1::Dbi_ro_wr_enable>(1);
		cfg.pci_e_cap->write<Config::Pci_express_capability::Link_control_2::Link_speed>(2);
		cfg.pci_e_cap->write<Config::Pci_express_capability::Link_capabilities::Max_link_speed>(2);
		write<Port_link_control::Fast_link_mode>(0);
		write<Port_link_control::Dll_link_enable>(1);
		write<Port_link_control::Link_capable>(1);
		write<Link_width_speed_control::Num_of_lanes>(1);

		cfg.bar0.write<Config::Base_address::Bar_32bit>(4);
		cfg.bar1.write<Config::Base_address::Bar_32bit>(0);
		cfg.write<Config::Irq_line>(Config::Irq_line::UNKNOWN);
		cfg.write<Config::Irq_pin>(Config::Irq_pin::INTA);

		Config_type1::Sec_lat_timer_bus::access_t b =
			read<Config_type1::Sec_lat_timer_bus>();
		Config_type1::Sec_lat_timer_bus::Primary_bus::set(b, bus);
		Config_type1::Sec_lat_timer_bus::Secondary_bus::set(b, bus + 1);
		Config_type1::Sec_lat_timer_bus::Sub_bus::set(b, bus + BUS_COUNT_PER_CONTROLLER);
		cfg.write<Config_type1::Sec_lat_timer_bus>(b);

		Config::Command::access_t cmd = 0;
		Config::Command::Io_space_enable::set(cmd, 1);
		Config::Command::Memory_space_enable::set(cmd, 1);
		Config::Command::Bus_master_enable::set(cmd, 1);
		Config::Command::Serror_enable::set(cmd, 1);
		cfg.write<Config::Command>(cmd);

		/* disable all outbound windows */
		for (unsigned i = 0; i < 4; i++)
			atu[i].disable_outbound();

		atu[1].configure_outbound(MEMORY_REQUEST, io_base + MEMORY_BASE,
		                          MEMORY_SIZE, io_base + MEMORY_BASE);
		atu[2].configure_outbound(IO_REQUEST, io_base + IO_BASE, IO_SIZE, 0);

		cfg.bar0.write<Config::Base_address::Bar_32bit>(0);

		/* we're a PCI bridge */
		enum Sub_class { PCI_BRIDGE = 0x4 };
		cfg.write<Config::Sub_class_code>(PCI_BRIDGE);
		cfg.write<Config::Base_class_code>(Config::Base_class_code::BRIDGE);
		write<Link_width_speed_control::Direct_speed_change>(1);
		write<Misc_control1::Dbi_ro_wr_enable>(0);

		/*
		 * Force Gen1 when starting the link. In case the link is
		 * started in Gen2 mode, there is a possibility the devices on the
		 * bus will not be detected at all.
		 */
		cfg.pci_e_cap->write<Config::Pci_express_capability::Link_capabilities::Max_link_speed>(1);

		if (!wait_for_link())
			throw Link_is_not_ready();

		cfg.pci_e_cap->write<Config::Pci_express_capability::Link_capabilities::Max_link_speed>(2);
		write<Link_width_speed_control::Direct_speed_change>(1);

		if (!wait_for_link())
			throw Link_is_not_ready();

		atu[0].configure_outbound(CONFIG_TYPE_0_REQUEST, io_base + CONFIG_BASE,
		                          CONFIG_SIZE, (1 << 24));
		if (!wait_for_atu())
			throw Atu_is_not_ready();

		cfg.bar1.write<Config::Base_address::Bar_32bit>(0);
		cfg.write<Config_type1::Expansion_rom_base_addr>(0);
		cfg.write<Config_type1::Io_base_limit>(0);
		cfg.write<Config_type1::Prefetchable_memory_base>(0);
		Config_type1::Bridge_control::access_t br_ctl = 0;
		Config_type1::Bridge_control::Serror::set(br_ctl, 1);
		cfg.write<Config_type1::Bridge_control>(br_ctl);
		cfg.power_cap->write<Config::Power_management_capability::Control_status::Pme_status>(1);
		cfg.clear_errors();
	}
};


struct Pci_device : Platform::Device::Mmio
{
	Pci::Config_type0 cfg;

	Pci_device(Platform::Device            & device,
	           Platform::Device::Mmio::Index i)
	: Platform::Device::Mmio(device, i),
	  cfg(base() + Pcie_controller::CONFIG_BASE) { }

};


struct Scanner
{
	using Device_name = Platform::Session::Device_name;

	struct Io_64bit_bus_address_not_supported {};
	struct Invalid_interrupt {};

	uint32_t _io_base(Xml_node & node)
	{
		addr_t   addr = ~0UL;
		unsigned idx  = 0;
		node.for_each_sub_node("io_mem", [&] (Xml_node xml) {
			if (idx++ == 1) addr = xml.attribute_value("phys_addr", ~0UL); });
		if (addr > 0xffffffff)
			throw Io_64bit_bus_address_not_supported();
		return (uint32_t) addr;
	}

	unsigned _irq(Xml_node & node)
	{
		unsigned irq = 0;
		unsigned idx = 0;
		node.for_each_sub_node("irq", [&] (Xml_node xml) {
			if (idx++ == 0) irq = xml.attribute_value("number", 0U); });
		if (irq < 32)
			throw Invalid_interrupt();
		return irq;
	}

	Xml_node         xml;
	Device_name      name { xml.attribute_value("name", Device_name()) };
	Platform::Device device;
	uint32_t         io_base { _io_base(xml) };
	unsigned         irq     { _irq(xml) };
	Pcie_controller  controller;
	Pci_device       pci_dev;

	Scanner(Pci::bus_t             bus,
	        Xml_node               xml,
	        Platform::Connection & platform,
	        Timer::Connection    & timer,
	        Xml_generator        & generator)
	:
		xml(xml),
		device(platform, name),
		controller(timer, device, { 0 }, bus, io_base),
		pci_dev(device, { 1 })
	{
		using namespace Pci;

		uint32_t dev_io_mem    = io_base + Pcie_controller::MEMORY_PER_DEVICE;
		uint32_t dev_cfg_space = io_base + Pcie_controller::CONFIG_BASE;
		Pci::Bdf dev_bdf({bus, 1, 0});

		pci_dev.cfg.scan();

		pci_dev.cfg.write<Config_type0::Command>(0);
		pci_dev.cfg.bar0.write<Config::Base_address::Bar_32bit>(4);
		pci_dev.cfg.bar1.write<Config::Base_address::Bar_32bit>(0);
		pci_dev.cfg.bar2.write<Config::Base_address::Bar_32bit>(0);
		pci_dev.cfg.bar3.write<Config::Base_address::Bar_32bit>(0);
		pci_dev.cfg.bar4.write<Config::Base_address::Bar_32bit>(0);
		pci_dev.cfg.bar5.write<Config::Base_address::Bar_32bit>(0);
		pci_dev.cfg.write<Config_type0::Expansion_rom_base_addr>(0);
		pci_dev.cfg.clear_errors();

		controller.cfg.bar0.write<Config::Base_address::Bar_32bit>(io_base);
		pci_dev.cfg.bar0.write<Config::Base_address::Bar_32bit>(dev_io_mem | 0x4);
		controller.cfg.write<Config_type1::Io_base_limit_upper>(0xffff);
		controller.cfg.write<Config_type1::Io_base_limit>(0xf0);
		controller.cfg.write<Config_type1::Io_base_limit_upper>(0);
		controller.cfg.write<Config_type1::Memory_base>((uint16_t)((dev_io_mem >> 16) & 0xffff));
		controller.cfg.write<Config_type1::Memory_limit>((uint16_t)((dev_io_mem >> 16) & 0xffff));
		controller.cfg.write<Config_type1::Prefetchable_memory_limit_upper>(0);
		controller.cfg.write<Config_type1::Prefetchable_memory_base>(0xfff0);
		controller.cfg.write<Config_type1::Prefetchable_memory_base_upper>(0);
		controller.cfg.write<Config_type1::Prefetchable_memory_limit_upper>(0);
		controller.cfg.write<Config_type1::Irq_line>((uint8_t)(irq - 32));

		controller.cfg.pci_e_cap->write<Config::Pci_express_capability::Root_control>(0);
		controller.cfg.pci_e_cap->write<Config::Pci_express_capability::Root_status>(0x10000);
		controller.cfg.pci_e_cap->write<Config::Pci_express_capability::Root_control>(0x8);
		controller.cfg.pci_e_cap->write<Config::Pci_express_capability::Link_status>(0x4000);
		controller.cfg.pci_e_cap->write<Config::Pci_express_capability::Link_control>(0x400);

		pci_dev.cfg.write<Config::Command>(0x2);
		pci_dev.cfg.write<Config::Command>(0x6);
		pci_dev.cfg.pci_e_cap->write<Config::Pci_express_capability::Slot_control>(0x201f);

		Config::Vendor::access_t vendor = pci_dev.cfg.read<Config::Vendor>();
		Config::Device::access_t device = pci_dev.cfg.read<Config::Device>();
		Config::Class_code_rev_id::Class_code::access_t dclass =
			pci_dev.cfg.read<Config::Class_code_rev_id::Class_code>();
		Config::Class_code_rev_id::Revision::access_t revision =
			pci_dev.cfg.read<Config::Class_code_rev_id::Revision>();
		Config_type0::Subsystem_vendor::access_t sub_vendor =
			pci_dev.cfg.read<Config_type0::Subsystem_vendor>();
		Config_type0::Subsystem_device::access_t sub_device =
			pci_dev.cfg.read<Config_type0::Subsystem_device>();

		generator.node("device", [&]
		{
			generator.attribute("name", Pci::Bdf::string(dev_bdf));
			generator.attribute("type", "pci");

			generator.node("pci-config", [&]
			{
				generator.attribute("address",       String<16>(Hex(dev_cfg_space)));
				generator.attribute("bus",           String<16>(Hex(dev_bdf.bus)));
				generator.attribute("device",        String<16>(Hex(dev_bdf.dev)));
				generator.attribute("function",      String<16>(Hex(dev_bdf.fn)));
				generator.attribute("vendor_id",     String<16>(Hex(vendor)));
				generator.attribute("device_id",     String<16>(Hex(device)));
				generator.attribute("class",         String<16>(Hex(dclass)));
				generator.attribute("revision",      String<16>(Hex(revision)));
				generator.attribute("sub_vendor_id", String<16>(Hex(sub_vendor)));
				generator.attribute("sub_device_id", String<16>(Hex(sub_device)));
				generator.attribute("bridge", "no");
			});

			generator.node("io_mem", [&]
			{
				generator.attribute("address", String<16>(Hex(dev_io_mem)));
				generator.attribute("size",
				              String<16>(Hex(Pcie_controller::MEMORY_PER_DEVICE)));
				generator.attribute("pci_bar", 0U);
			});

			generator.node("irq", [&]
			{
				generator.attribute("number", irq);
			});
		});
	}
};


struct Main
{
	Env & env;

	/* Dummy wait for GPIO settings being settled */
	Reconstructible<Gpio::Connection> gpio { env, 255 };

	Platform::Connection   platform { env };
	Timer::Connection      timer    { env };
	Expanding_reporter     reporter { env,
	                                  "devices",
	                                  "devices" };
	Constructible<Scanner> scanner {};

	Main(Env & env) : env(env)
	{
		gpio.destruct();

		Pci::bus_t bus = 0;

		reporter.generate([&] (Xml_generator & generator)
		{
			platform.with_xml([&] (Xml_node xml)
			{
				xml.for_each_sub_node("device", [&] (Xml_node xml)
				{
					scanner.construct(bus, xml, platform, timer, generator);
					bus += Pcie_controller::BUS_COUNT_PER_CONTROLLER;
					scanner.destruct();
				});
			});
		});
	}
};


void Component::construct(Env & env) {
	static Main main(env); }
