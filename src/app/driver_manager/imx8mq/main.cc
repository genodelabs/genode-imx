/*
 * \brief  Driver manager (stripped down version without PC-related stuff)
 * \author Norman Feske
 * \author Stefan Kalkowski
 * \date   2017-06-13
 */

/*
 * Copyright (C) 2017 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

/* Genode includes */
#include <base/component.h>
#include <base/registry.h>
#include <base/attached_rom_dataspace.h>
#include <os/reporter.h>
#include <block_session/block_session.h>
#include <rm_session/rm_session.h>
#include <timer_session/timer_session.h>
#include <log_session/log_session.h>
#include <platform_session/platform_session.h>

namespace Driver_manager {
	using namespace Genode;
	struct Main;
	struct Block_devices_generator;
	struct Device_driver;
	struct Sd_card_driver;
	struct Nvme_driver;

	struct Priority { int      value; };
	struct Version  { unsigned value; };
}


struct Driver_manager::Block_devices_generator : Interface
{
	virtual void generate_block_devices() = 0;
};


class Driver_manager::Device_driver : Noncopyable
{
	public:

		typedef String<64>  Name;
		typedef String<100> Binary;
		typedef String<32>  Service;

	protected:

		static void _gen_common_start_node_content(Xml_generator &xml,
		                                           Name    const &name,
		                                           Binary  const &binary,
		                                           Ram_quota      ram,
		                                           Cap_quota      caps,
		                                           Priority       priority,
		                                           Version        version)
		{
			xml.attribute("name", name);
			xml.attribute("caps", String<64>(caps));
			xml.attribute("priority", priority.value);
			xml.attribute("version", version.value);
			xml.node("binary", [&] () { xml.attribute("name", binary); });
			xml.node("resource", [&] () {
				xml.attribute("name", "RAM");
				xml.attribute("quantum", String<64>(ram));
			});
		}

		template <typename SESSION>
		static void _gen_provides_node(Xml_generator &xml)
		{
			xml.node("provides", [&] () {
				xml.node("service", [&] () {
					xml.attribute("name", SESSION::service_name()); }); });
		}

		static void _gen_config_route(Xml_generator &xml, char const *config_name)
		{
			xml.node("service", [&] () {
				xml.attribute("name", Rom_session::service_name());
				xml.attribute("label", "config");
				xml.node("parent", [&] () {
					xml.attribute("label", config_name); });
			});
		}

		static void _gen_default_parent_route(Xml_generator &xml)
		{
			xml.node("any-service", [&] () {
				xml.node("parent", [&] () { }); });
		}

		template <typename SESSION>
		static void _gen_forwarded_service(Xml_generator &xml,
		                                   Device_driver::Name const &name)
		{
			xml.node("service", [&] () {
				xml.attribute("name", SESSION::service_name());
				xml.node("default-policy", [&] () {
					xml.node("child", [&] () {
						xml.attribute("name", name);
					});
				});
			});
		};

		virtual ~Device_driver() { }

	public:

		virtual void generate_start_node(Xml_generator &xml) const = 0;
};


struct Driver_manager::Sd_card_driver : Device_driver
{
	Attached_rom_dataspace & _sd_cards;

	Sd_card_driver(Attached_rom_dataspace & ds) : _sd_cards(ds) {}

	void generate_start_node(Xml_generator &xml) const override
	{
		xml.node("start", [&] () {
			_gen_common_start_node_content(xml, "sd_card", "imx8mq_sd_card",
			                               Ram_quota{16*1024*1024}, Cap_quota{300},
			                               Priority{0}, Version{0});
			_gen_provides_node<Block::Session>(xml);
			xml.node("config", [&] () {
				xml.attribute("report", "yes");
				_sd_cards.xml().for_each_sub_node([&] (Xml_node sd_card) {
					typedef String<80> Label;
					Label const label = sd_card.attribute_value("label", Label());
					xml.node("policy", [&] () {
						xml.attribute("label_suffix", label);
						xml.attribute("device",       label);
					});
				});
			});
			xml.node("route", [&] () {
				xml.node("service", [&] () {
					xml.attribute("name", "Report");
					xml.node("parent", [&] () { xml.attribute("label", "sd_cards"); });
				});
				_gen_default_parent_route(xml);
			});
		});
	}

	typedef String<32> Default_label;

	void gen_service_forwarding_policy(Xml_generator &xml) const
	{
		_sd_cards.xml().for_each_sub_node([&] (Xml_node sd_card) {
			typedef String<80> Label;
			Label const label = sd_card.attribute_value("label", Label());
			xml.node("policy", [&] () {
				xml.attribute("label_suffix", label);
				xml.node("child", [&] () { xml.attribute("name", "sd_card"); });
			});
		});
	}
};


struct Driver_manager::Nvme_driver : Device_driver
{
	void generate_start_node(Xml_generator &xml) const override
	{
		xml.node("start", [&] () {
			_gen_common_start_node_content(xml, "nvme", "nvme",
			                               Ram_quota{8*1024*1024}, Cap_quota{100},
			                               Priority{-1}, Version{0});
			_gen_provides_node<Block::Session>(xml);
			xml.node("config", [&] () {
				xml.node("report", [&] () { xml.attribute("namespaces", "yes"); });
				xml.node("policy", [&] () {
					xml.attribute("label_suffix", String<64>("nvme-0"));
					xml.attribute("namespace", 1);
					xml.attribute("writeable", "yes");
				});
			});
			xml.node("route", [&] () {
				xml.node("service", [&] () {
					xml.attribute("name", "Report");
					xml.node("parent", [&] () { xml.attribute("label", "nvme_ns"); });
				});
				_gen_default_parent_route(xml);
			});
		});
	}

	typedef String<32> Default_label;

	void gen_service_forwarding_policy(Xml_generator &xml) const
	{
		xml.node("policy", [&] () {
			xml.attribute("label_suffix", String<64>("nvme-0"));
			xml.node("child", [&] () {
				xml.attribute("name", "nvme"); });
		});
	}
};


struct Driver_manager::Main : private Block_devices_generator
{
	Env &_env;

	Attached_rom_dataspace _usb_devices   { _env, "usb_devices"   };
	Attached_rom_dataspace _usb_policy    { _env, "usb_policy"    };
	Attached_rom_dataspace _pci_devices   { _env, "pci_devices"   };
	Attached_rom_dataspace _nvme_ns       { _env, "nvme_ns"       };
	Attached_rom_dataspace _sd_cards      { _env, "sd_cards"      };

	Reporter _init_config   { _env, "config", "init.config" };
	Reporter _usb_config    { _env, "config", "usb.config" };
	Reporter _block_devices { _env, "block_devices" };

	Sd_card_driver             _sd_card_driver { _sd_cards };
	Constructible<Nvme_driver> _nvme_driver { };

	void _handle_usb_devices_update();
	void _handle_pci_devices_update();
	void _handle_nvme_ns_update();
	void _handle_sd_cards_update();

	Signal_handler<Main> _usb_update_handler {
		_env.ep(), *this, &Main::_handle_usb_devices_update };
	Signal_handler<Main> _pci_devices_update_handler {
		_env.ep(), *this, &Main::_handle_pci_devices_update };
	Signal_handler<Main> _nvme_ns_update_handler {
		_env.ep(), *this, &Main::_handle_nvme_ns_update };
	Signal_handler<Main> _sd_cards_update_handler {
		_env.ep(), *this, &Main::_handle_sd_cards_update };

	static void _gen_parent_service_xml(Xml_generator &xml, char const *name)
	{
		xml.node("service", [&] () { xml.attribute("name", name); });
	};

	void _generate_init_config    (Reporter &) const;
	void _generate_usb_config (Reporter &, Xml_node, Xml_node) const;
	void _generate_block_devices  (Reporter &) const;

	/**
	 * Block_devices_generator interface
	 */
	void generate_block_devices() override { _generate_block_devices(_block_devices); }


	Main(Env &env) : _env(env)
	{
		_init_config.enabled(true);
		_usb_config.enabled(true);
		_block_devices.enabled(true);

		_usb_devices.sigh(_usb_update_handler);
		_usb_policy.sigh(_usb_update_handler);
		_pci_devices.sigh(_pci_devices_update_handler);
		_nvme_ns.sigh(_nvme_ns_update_handler);
		_sd_cards.sigh(_sd_cards_update_handler);

		_generate_init_config(_init_config);

		_handle_usb_devices_update();
		_handle_pci_devices_update();
		_handle_nvme_ns_update();
		_handle_sd_cards_update();
	}
};


void Driver_manager::Main::_handle_nvme_ns_update()
{
	_nvme_ns.update();

	/* update service forwarding rules */
	_generate_init_config(_init_config);

	_generate_block_devices(_block_devices);
}


void Driver_manager::Main::_handle_sd_cards_update()
{
	_sd_cards.update();

	/* update service forwarding rules */
	_generate_init_config(_init_config);

	_generate_block_devices(_block_devices);
}


void Driver_manager::Main::_handle_usb_devices_update()
{
	_usb_devices.update();
	_usb_policy.update();

	_generate_usb_config(_usb_config, _usb_devices.xml(), _usb_policy.xml());
}


void Driver_manager::Main::_generate_usb_config(Reporter &usb_config,
                                                Xml_node devices,
                                                Xml_node policy) const
{
	Reporter::Result const result = usb_config.generate([&] (Xml_generator &xml) {

		xml.node("report", [&] () { xml.attribute("devices", true); });

		/* incorporate user-managed policy */
		policy.with_raw_content([&] (char const *start, size_t length) {
			xml.append(start, length); });

		/* usb hid drv gets all hid devices */
		xml.node("policy", [&] () {
			xml.attribute("label_prefix", "usb_hid");
			xml.attribute("class", "0x3");
		});

		devices.for_each_sub_node("device", [&] (Xml_node device) {

			typedef String<64> Label;
			typedef String<32> Id;

			Label const label      = device.attribute_value("label", Label());
			Id    const vendor_id  = device.attribute_value("vendor_id",  Id());
			Id    const product_id = device.attribute_value("product_id", Id());

			/*
			 * Limit USB sessions to storage and vendor specific in order to avoid
			 * conflicts with the USB driver's built-in HID drivers.
			 */
			unsigned long const class_code = device.attribute_value("class", 0UL);

			enum { USB_CLASS_MASS_STORAGE = 8, USB_CLASS_VENDOR_SPECIFIC = 0xff };

			bool const expose_as_usb_raw = (class_code == USB_CLASS_MASS_STORAGE) ||
			                               (class_code == USB_CLASS_VENDOR_SPECIFIC);
			if (!expose_as_usb_raw)
				return;

			xml.node("policy", [&] () {
				xml.attribute("label_suffix", label);
				xml.attribute("vendor_id",  vendor_id);
				xml.attribute("product_id", product_id);

				/* annotate policy to make storage devices easy to spot */
				if (class_code == USB_CLASS_MASS_STORAGE)
					xml.attribute("class", "storage");
			});
		});
	});

	if (result == Buffer_error::EXCEEDED)
		warning("config report exceeds maximum size");
}


void Driver_manager::Main::_handle_pci_devices_update()
{
	_pci_devices.update();

	/* decide not before the first valid pci report is available */
	if (!_pci_devices.valid())
		return;

	bool has_nvme = false;

	_pci_devices.xml().for_each_sub_node([&] (Xml_node device) {
		device.with_optional_sub_node("pci-config", [&] (Xml_node pci) {

			uint16_t const class_code = (uint16_t)(pci.attribute_value("class", 0U) >> 8);

			enum {
				CLASS_NVME = 0x108U,
			};

			if (class_code == CLASS_NVME)
				has_nvme = true;
		});
	});

	if (!_nvme_driver.constructed() && has_nvme) {
		_nvme_driver.construct();
		_generate_init_config(_init_config);
	}
}


void Driver_manager::Main::_generate_init_config(Reporter &init_config) const
{
	Reporter::Result const result = init_config.generate([&] (Xml_generator &xml) {

		xml.attribute("verbose", false);
		xml.attribute("prio_levels", 2);

		xml.node("report", [&] () {
			xml.attribute("child_ram", true);
			xml.attribute("delay_ms", 2500);
		});

		xml.node("heartbeat", [&] () { xml.attribute("rate_ms", 2500); });

		xml.node("parent-provides", [&] () {
			_gen_parent_service_xml(xml, Rom_session::service_name());
			_gen_parent_service_xml(xml, Cpu_session::service_name());
			_gen_parent_service_xml(xml, Pd_session::service_name());
			_gen_parent_service_xml(xml, Rm_session::service_name());
			_gen_parent_service_xml(xml, Log_session::service_name());
			_gen_parent_service_xml(xml, Timer::Session::service_name());
			_gen_parent_service_xml(xml, Platform::Session::service_name());
			_gen_parent_service_xml(xml, Report::Session::service_name());
		});

		_sd_card_driver.generate_start_node(xml);

		if (_nvme_driver.constructed())
			_nvme_driver->generate_start_node(xml);

		/* block-service forwarding rules */
		bool const nvme = _nvme_driver.constructed() &&
		                  _nvme_ns.xml().has_sub_node("namespace");

		xml.node("service", [&] () {
			xml.attribute("name", Block::Session::service_name());
				_sd_card_driver.gen_service_forwarding_policy(xml);
				if (nvme) _nvme_driver->gen_service_forwarding_policy(xml);
		});
	});

	if (result == Buffer_error::EXCEEDED)
		warning("init config report exceeds maximum size");
}


void Driver_manager::Main::_generate_block_devices(Reporter &block_devices) const
{
	Reporter::Result const result = block_devices.generate([&] (Xml_generator &xml) {

		_sd_cards.xml().for_each_sub_node([&] (Xml_node sd_card) {

			xml.node("device", [&] () {

				unsigned long const
					block_count = sd_card.attribute_value("block_count", 0UL),
					block_size  = sd_card.attribute_value("block_size",  0UL);

				typedef String<80> Label;
				Label const label = sd_card.attribute_value("label", Label());

				xml.attribute("label",       label);
				xml.attribute("block_count", block_count);
				xml.attribute("block_size",  block_size);
			});
		});

		/* for now just report the first name space */
		Xml_node const &nvme_ctrl = _nvme_ns.xml();
		nvme_ctrl.with_optional_sub_node("namespace", [&] (Xml_node const &nvme_ns) {

			xml.node("device", [&] () {

				unsigned long const
					block_count = nvme_ns.attribute_value("block_count", 0UL),
					block_size  = nvme_ns.attribute_value("block_size",  0UL);

				typedef String<40+1> Model;
				Model const model = nvme_ctrl.attribute_value("model", Model());
				typedef String<20+1> Serial;
				Serial const serial = nvme_ctrl.attribute_value("serial", Serial());

				xml.attribute("label",       String<16>("nvme-0"));
				xml.attribute("block_count", block_count);
				xml.attribute("block_size",  block_size);
				xml.attribute("model",       model);
				xml.attribute("serial",      serial);
			});
		});
	});

	if (result == Buffer_error::EXCEEDED)
		warning("init config report exceeds maximum size");
}


void Component::construct(Genode::Env &env) { static Driver_manager::Main main(env); }
