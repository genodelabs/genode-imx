/**
 * \brief  Globally available Lx_kit environment, needed in the C-ish lx_emul
 * \author Stefan Kalkowski
 * \date   2021-04-14
 */

/*
 * Copyright (C) 2021 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#pragma once

#include <base/env.h>
#include <base/heap.h>
#include <irq_session/client.h>
#include <io_mem_session/client.h>
#include <platform_session/device.h>
#include <util/list.h>
#include <util/xml_node.h>

namespace Lx_kit {
	using namespace Genode;

	class Device;
	class Device_list;
}

struct clk {
	unsigned long rate;
};

class Lx_kit::Device : List<Device>::Element
{
	public:

		const char * compatible();
		const char * name();

		void   enable();
		clk *  clock(const char * name);
		clk *  clock(unsigned idx);
		bool   io_mem(addr_t phys_addr, size_t size);
		void * io_mem_local_addr(addr_t phys_addr, size_t size);
		void   irq_unmask(unsigned irq);
		void   irq_mask(unsigned irq);
		void   irq_ack(unsigned irq);

	private:

		friend class Device_list;
		friend class List<Device>;

		using Name = String<64>;
		using Type = Platform::Device::Type;

		struct Io_mem : List<Io_mem>::Element
		{
			using Index = Platform::Device::Mmio::Index;

			Index  idx;
			addr_t addr;
			size_t size;

			Constructible<Platform::Device::Mmio> io_mem {};

			bool match(addr_t addr, size_t size);

			Io_mem(unsigned idx, addr_t addr, size_t size)
			: idx{idx}, addr(addr), size(size) {}
		};

		struct Irq_handler
		{
			private:

				Irq_handler(Irq_handler const &);
				Irq_handler &operator = (Irq_handler const &);

				Platform::Device::Irq          _irq;
				Io_signal_handler<Irq_handler> _handler;
				unsigned                       _number;

				void _handle();

			public:

				Irq_handler(Platform::Device & dev,
				            Platform::Device::Irq::Index idx,
				            unsigned number);

				void ack() { _irq.ack(); }
		};

		struct Irq : List<Irq>::Element
		{
			using Index = Platform::Device::Irq::Index;

			Index    idx;
			unsigned number;

			Constructible<Irq_handler> handler {};

			Irq(unsigned idx, unsigned number)
			: idx{idx}, number(number) {}
		};

		struct Clock : List<Clock>::Element
		{
			unsigned   idx;
			Name const name;
			clk        lx_clock;

			Clock(unsigned idx, Name const name)
			: idx(idx), name(name), lx_clock{0} {}
		};

		Device(Platform::Connection & plat,
		       Xml_node             & xml,
		       Heap                 & heap);

		Platform::Connection          & _platform;
		Name                      const _name;
		Type                      const _type;
		List<Io_mem>                    _io_mems {};
		List<Irq>                       _irqs    {};
		List<Clock>                     _clocks  {};
		Constructible<Platform::Device> _pdev    {};

		template <typename FN>
		void _for_each_io_mem(FN const & fn) {
			for (Io_mem * i = _io_mems.first(); i; i = i->next()) { fn(*i); } }

		template <typename FN>
		void _for_each_irq(FN const & fn) {
			for (Irq * i = _irqs.first(); i; i = i->next()) { fn(*i); } }

		template <typename FN>
		void _for_each_clock(FN const & fn) {
			for (Clock * c = _clocks.first(); c; c = c->next()) { fn(*c); } }
};


class Lx_kit::Device_list : List<Device>
{
	public:

		template <typename FN>
		void for_each(FN const & fn) {
			for (Device * d = first(); d; d = d->next()) { fn(*d); } }

		Device_list(Heap & heap, Platform::Connection & platform);

	private:

		Platform::Connection & _platform;
};