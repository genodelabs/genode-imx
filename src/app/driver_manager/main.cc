/*
 * \brief  Driver manager (stripped down for USB policy handling only)
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

namespace Driver_manager {
	using namespace Genode;
	struct Main;
}


struct Driver_manager::Main
{
	Env &_env;

	Attached_rom_dataspace _usb_devices   { _env, "usb_devices"   };
	Attached_rom_dataspace _usb_policy    { _env, "usb_policy"    };

	Reporter _usb_drv_config { _env, "config", "usb_drv.config" };

	void _handle_usb_devices_update();

	Signal_handler<Main> _usb_update_handler {
		_env.ep(), *this, &Main::_handle_usb_devices_update };

	void _generate_usb_drv_config (Reporter &, Xml_node, Xml_node) const;

	Main(Env &env) : _env(env)
	{
		_usb_drv_config.enabled(true);
		_usb_devices.sigh(_usb_update_handler);
		_usb_policy.sigh(_usb_update_handler);
		_handle_usb_devices_update();
	}
};


void Driver_manager::Main::_handle_usb_devices_update()
{
	_usb_devices.update();
	_usb_policy.update();

	_generate_usb_drv_config(_usb_drv_config, _usb_devices.xml(), _usb_policy.xml());
}


void Driver_manager::Main::_generate_usb_drv_config(Reporter &usb_drv_config,
                                                    Xml_node devices,
                                                    Xml_node policy) const
{
	Reporter::Xml_generator xml(usb_drv_config, [&] () {

		xml.node("report", [&] () { xml.attribute("devices", true); });

		/* incorporate user-managed policy */
		policy.with_raw_content([&] (char const *start, size_t length) {
			xml.append(start, length); });

		/* usb hid drv gets all hid devices */
		xml.node("policy", [&] () {
			xml.attribute("label_prefix", "usb_hid_drv");
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
}


void Component::construct(Genode::Env &env) { static Driver_manager::Main main(env); }
