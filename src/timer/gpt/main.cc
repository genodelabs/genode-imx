/*
 * \brief  Time source for i.MX8 GPT 1
 * \author Alexander Boettcher
 * \author Norman Feske
 * \date   2025-11-15
 */

/*
 * Copyright (C) 2025 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

/* Genode includes */
#include <base/attached_io_mem_dataspace.h>
#include <base/component.h>
#include <base/heap.h>
#include <base/session_object.h>
#include <irq_session/connection.h>
#include <root/component.h>
#include <timer_session/timer_session.h>
#include <util/mmio.h>

/* base-internal includes */
#include <base/internal/alarm_registry.h>

namespace Timer {

	using namespace Genode;

	struct Clock;
	struct Device;
	struct Alarm;
	struct Root;
	struct Session_component;
	struct Main;

	using Alarms = Alarm_registry<Alarm, Clock>;
}


struct Timer::Clock
{
	uint64_t us;

	static constexpr uint64_t MASK = uint64_t(-1);

	uint64_t value() const { return us; }

	void print(Output &out) const { Genode::print(out, us/1000); }
};


class Timer::Device : private Mmio<0x28>
{
	private:

		/* see Device constructor */
		enum { TICKS_PER_US = 24 / 2 };

		struct Cr : Register<0x0, 32>
		{
			struct En      : Bitfield< 0, 1> { };
			struct En_mod  : Bitfield< 1, 1> { };
			struct Clksrc  : Bitfield< 6, 3> { enum { CLK_24MHZ = 0b101 }; };
			struct Frr     : Bitfield< 9, 1> { };
			struct En_24M  : Bitfield<10, 1> { };
			struct Swr     : Bitfield<15, 1> { };
		};

		struct Pr : Register<0x04, 32> {
			struct Prescaler    : Bitfield< 0, 12> { };
			struct Prescaler24M : Bitfield<12,  5> { };
		};

		struct Sr : Register<0x08, 32> { };

		struct Ir : Register<0x0c, 32> { struct Of1ie : Bitfield< 0, 1> { }; };

		struct Ocr1 : Register<0x10, 32> { };

		struct Cnt  : Register<0x24, 32> { enum { MAX = ~0U }; };

		enum {
			GPT_MAX_USEC = unsigned(Cnt::MAX) / TICKS_PER_US
		};

		/* GPT counter */
		struct Counter { unsigned value; };

	public:

		enum {
			GPT_1_IRQ       = 32 + 55,
			GPT_1_MMIO_BASE = 0x302d0000,
			GPT_1_MMIO_SIZE = 0x00010000
		};

		struct Wakeup_dispatcher : Interface
		{
			virtual void dispatch_device_wakeup() = 0;
		};

		struct Deadline : Clock { };

		static constexpr Deadline infinite_deadline { uint64_t(-1) };

	private:

		Env &_env;

		Irq_connection _timer_irq { _env, unsigned(GPT_1_IRQ) };

		Wakeup_dispatcher &_dispatcher;

		Signal_handler<Device> _handler { _env.ep(), *this, &Device::_handle_timeout };

		uint64_t _curr_time_us { };
		Counter  _last_read    { };

		uint64_t _convert_counter_diff_to_us(Counter const &diff)
		{
			/* round up to 1us in case of rest */
			auto const mod = diff.value % TICKS_PER_US;
			return diff.value / TICKS_PER_US + (mod ? 1 : 0);
		}

		Counter _convert_relative_us_to_counter(uint64_t rel_us)
		{
			if (rel_us * TICKS_PER_US > Cnt::MAX)
				warning("unexpected overflow");

			uint64_t value = min(rel_us * TICKS_PER_US, uint64_t(Cnt::MAX));

			if (value + _last_read.value > Cnt::MAX)
				value = (value + _last_read.value) % (uint64_t(Cnt::MAX) + 1);
			else
				value += _last_read.value;

			return { unsigned(value) };
		}

		void _handle_timeout()
		{
			/* ack irq on device */
			write<Sr>(1);

			_dispatcher.dispatch_device_wakeup();

			/* ack irq on kernel */
			_timer_irq.ack_irq();
		}

		void _advance_current_time()
		{
			auto const gpt  = Counter(read<Cnt>());
			auto const diff = _last_read.value <= gpt.value
			                ? Counter(gpt.value - _last_read.value)
			                : Counter(_last_read.value - gpt.value);

			_curr_time_us += _convert_counter_diff_to_us(diff);

			_last_read = gpt;
		}

	public:

		Device(Env &env, Attached_io_mem_dataspace &mmio_ds, Wakeup_dispatcher &dispatcher)
		:
			Mmio({ mmio_ds.local_addr<char>(), GPT_1_MMIO_SIZE }),
			_env(env), _dispatcher(dispatcher)
		{
			write<Cr::En>(0);

			/* Prescaler24M divider 1 seems not to work, so we use 12 MHz */
			write<Cr::En_24M      >(1);
			write<Cr::Clksrc      >(Cr::Clksrc::CLK_24MHZ);
			write<Pr::Prescaler24M>(1); /* divider 2, 24 / 2 == 12 MHz */
			write<Pr::Prescaler   >(0); /* divider 1 */
			write<Ir::Of1ie       >(1); /* enable IRQ for comparator 1 */
			write<Cr::En_mod      >(1); /* reset counters on next Cr::En */

			write<Cr::En>(1);

			while (read<Cr::Swr>()) { }

			_timer_irq.sigh(_handler);

			_handle_timeout();
		}

		Clock now()
		{
			_advance_current_time();

			return Clock { .us = _curr_time_us };
		}

		void update_deadline(Deadline const abs)
		{
			uint64_t const now_us = now().us;
			uint64_t const rel_us = (abs.us > now_us)
			                      ? min(uint64_t(GPT_MAX_USEC), abs.us - now_us)
			                      : 1;

			auto const gpt_cnt = _convert_relative_us_to_counter(rel_us);

			/* set new compare counter */
			write<Ocr1>(gpt_cnt.value);
		}
};


struct Timer::Alarm : Alarms::Element
{
	Session_component &session;

	Alarm(Alarms &alarms, Session_component &session, Clock time)
	:
		Alarms::Element(alarms, *this, time), session(session)
	{ }

	void print(Output &out) const;
};


static Timer::Device::Deadline next_deadline(Timer::Alarms &alarms)
{
	using namespace Timer;

	return alarms.soonest(Clock { 0 }).convert<Device::Deadline>(
		[&] (Clock soonest) -> Device::Deadline {

			/* scan alarms for a cluster nearby the soonest */
			uint64_t const MAX_DELAY_US = 250;
			Device::Deadline result { soonest.us };
			alarms.for_each_in_range(soonest, Clock { soonest.us + MAX_DELAY_US },
			[&] (Alarm const &alarm) {
				result.us = max(result.us, alarm.time.us); });

			return result;
		},
		[&] (Alarms::None) { return Device::infinite_deadline; });
}


struct Timer::Session_component : Session_object<Timer::Session, Session_component>
{
	Alarms &_alarms;
	Device &_device;

	Signal_context_capability _sigh { };

	Clock const _creation_time = _device.now();

	uint64_t _local_now_us() const { return _device.now().us - _creation_time.us; }

	struct Period { uint64_t us; };

	Constructible<Period> _period { };
	Constructible<Alarm>  _alarm  { };

	Session_component(Env             &env,
	                  Resources const &resources,
	                  Label     const &label,
	                  Alarms          &alarms,
	                  Device          &device)
	:
		Session_object(env.ep(), resources, label), _alarms(alarms), _device(device)
	{ }

	/**
	 * Called by Device::Wakeup_dispatcher
	 */
	void handle_wakeup()
	{
		if (_sigh.valid())
			Signal_transmitter(_sigh).submit();

		if (_period.constructed()) {
			Clock const next = _alarm.constructed()
			                 ? Clock { _alarm->time.us  + _period->us }
			                 : Clock { _device.now().us + _period->us };

			_alarm.construct(_alarms, *this, next);

		} else /* response of 'trigger_once' */ {
			_alarm.destruct();
		}
	}

	/******************************
	 ** Timer::Session interface **
	 ******************************/

	void trigger_once(uint64_t rel_us) override
	{
		_period.destruct();
		_alarm.destruct();

		Clock const now = _device.now();

		rel_us = max(rel_us, 250u);
		_alarm.construct(_alarms, *this, Clock { now.us + rel_us });

		_device.update_deadline(next_deadline(_alarms));
	}

	void trigger_periodic(uint64_t period_us) override
	{
		_period.destruct();
		_alarm.destruct();

		if (period_us) {
			period_us = max(period_us, 1000u);
			_period.construct(period_us);
			handle_wakeup();
		}

		_device.update_deadline(next_deadline(_alarms));
	}

	void sigh(Signal_context_capability sigh) override { _sigh = sigh; }

	uint64_t elapsed_ms() const override { return _local_now_us()/1000; }
	uint64_t elapsed_us() const override { return _local_now_us(); }

	void msleep(uint64_t) override { }
	void usleep(uint64_t) override { }
};


struct Timer::Root : public Root_component<Session_component>
{
	private:

		Env    &_env;
		Alarms &_alarms;
		Device &_device;

	protected:

		Create_result _create_session(const char *args) override
		{
			return *new (md_alloc())
				Session_component(_env,
				                  session_resources_from_args(args),
				                  session_label_from_args(args),
				                  _alarms, _device);
		}

		void _upgrade_session(Session_component &s, const char *args) override
		{
			s.upgrade(ram_quota_from_args(args));
			s.upgrade(cap_quota_from_args(args));
		}

		void _destroy_session(Session_component &s) override
		{
			Genode::destroy(md_alloc(), &s);
		}

	public:

		Root(Env &env, Allocator &md_alloc, Alarms &alarms, Device &device)
		:
			Root_component<Session_component>(&env.ep().rpc_ep(), &md_alloc),
			_env(env), _alarms(alarms), _device(device)
		{ }
};


void Timer::Alarm::print(Output &out) const { Genode::print(out, session.label()); }


struct Timer::Main : Device::Wakeup_dispatcher
{
	Env &_env;

	Attached_io_mem_dataspace _mmio { _env, Device::GPT_1_MMIO_BASE,
	                                        Device::GPT_1_MMIO_SIZE };

	Device _device { _env, _mmio, *this };

	Alarms _alarms { };

	Sliced_heap _sliced_heap { _env.ram(), _env.rm() };

	Root _root { _env, _sliced_heap, _alarms, _device };

	/**
	 * Device::Wakeup_dispatcher
	 */
	void dispatch_device_wakeup() override
	{
		Clock const now = _device.now();

		/* handle and remove pending alarms */
		while (_alarms.with_any_in_range({ 0 }, now, [&] (Alarm &alarm) {
			alarm.session.handle_wakeup(); }));

		/* schedule next wakeup */
		_device.update_deadline(next_deadline(_alarms));
	}

	Main(Genode::Env &env) : _env(env)
	{
		_env.parent().announce(_env.ep().manage(_root));
	}
};


void Component::construct(Genode::Env &env) { static Timer::Main inst(env); }
