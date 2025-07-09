/*
 * \brief  Device interface of the i.MX PIO driver
 * \author Norman Feske
 * \author Stefan Kalkowski
 * \date   2021-04-14
 */

#ifndef _PIO_H_
#define _PIO_H_

/* Genode includes */
#include <platform_session/device.h>

/* local includes */
#include <types.h>

namespace Pio_driver { struct Pio; }


struct Pio_driver::Pio
{
	struct Io_bank
	{
		Platform::Device device;
		struct Regs : Platform::Device::Mmio<0x20>
		{
			struct Data     : Register_array<0x0,  32, 32, 1> {};
			struct Dir      : Register_array<0x4,  32, 32, 1> {};
			struct Pad_stat : Register_array<0x8,  32, 32, 1> {};
			struct Int_conf : Register_array<0xc,  32, 32, 2> {};
			struct Int_mask : Register_array<0x14, 32, 32, 1> {};
			struct Int_stat : Register_array<0x18, 32, 32, 1> {};
			struct Edge_sel : Register_array<0x1c, 32, 32, 1> {};

			using Platform::Device::Mmio<SIZE>::Mmio;
		};

		Regs                  regs { device, { 0 } };
		Platform::Device::Irq low  { device, { 0 } };
		Platform::Device::Irq high { device, { 1 } };

		void configure(Index index, Attr const &attr)
		{
			regs.write<Regs::Dir>(attr.function.value, index.value);
			regs.write<Regs::Int_conf>(attr.irq_trigger.config, index.value);
			regs.write<Regs::Edge_sel>(attr.irq_trigger.edges, index.value);
		}

		bool state(Index index) const
		{
			return regs.read<Regs::Pad_stat>(index.value);
		}

		void state(Index index, Pin::Level level)
		{
			if (level == Pin::Level::HIGH_IMPEDANCE) {
				regs.write<Regs::Dir>(Function::INPUT, index.value);
			} else {
				regs.write<Regs::Dir>(Function::OUTPUT, index.value);
				regs.write<Regs::Data>(level == Pin::Level::HIGH, index.value);
			}
		}

		void clear_irq_status(Index index)
		{
			regs.write<Regs::Int_stat>(1, index.value);
		}

		bool irq_pending(Index index) const
		{
			return regs.read<Regs::Int_stat>(index.value);
		}

		/**
		 * Enable/disable IRQ delivery to GIC
		 */
		void irq_enabled(Index index, bool enabled)
		{
			regs.write<Regs::Int_mask>(enabled, index.value);
		}

		Io_bank(Platform::Connection &plat, Platform::Device::Name name,
		        Signal_context_capability cap)
		:
			device(plat, name)
		{
			low.sigh(cap);
			high.sigh(cap);
		}
	};

	Constructible<Io_bank> _io_banks [Bank::NUM];

	Pio(Platform::Connection &platform, Signal_context_capability cap)
	{
		using Name = Platform::Device::Name;

		unsigned i = 0;
		platform.with_node([&] (Node const &node) {
			node.for_each_sub_node("device", [&] (Node const &node) {
				if (i >= Bank::NUM)
					return;
				Name name = node.attribute_value("name", Name());
				_io_banks[i++].construct(platform, name, cap);
			});
		});
	}

	void configure(Pin_id id, Attr const &attr)
	{
		_io_banks[id.bank.value]->configure(id.index, attr);
	}

	bool state(Pin_id id) const
	{
		return _io_banks[id.bank.value]->state(id.index);
	}

	void state(Pin_id id, Pin::Level level)
	{
		_io_banks[id.bank.value]->state(id.index, level);
	}

	void clear_irq_status(Pin_id id)
	{
		_io_banks[id.bank.value]->clear_irq_status(id.index);
	}

	void irq_enabled(Pin_id id, bool enabled)
	{
		_io_banks[id.bank.value]->irq_enabled(id.index, enabled);
	}

	bool irq_pending(Pin_id id) const
	{
		return _io_banks[id.bank.value]->irq_pending(id.index);
	}
};

#endif /* _PIO_H_ */
