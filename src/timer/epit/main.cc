/*
 * \brief  Time source for i.MX6 (EPIT2)
 * \author Norman Feske
 * \author Alexander Boettcher
 * \date   2024-06-26
 */

/*
 * Copyright (C) 2024 Genode Labs GmbH
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


class Timer::Device : private Mmio<0x14>
{
	private:

		enum {
			TICKS_PER_US = 66,
		};

		struct Cr : Register<0x0, 32>
		{
			struct En      : Bitfield<0, 1>  { };
			struct En_mod  : Bitfield<1, 1>  { enum { RELOAD = 1 }; };
			struct Oci_en  : Bitfield<2, 1>  { };
			struct Swr     : Bitfield<16, 1> { };
			struct Clk_src : Bitfield<24, 2> { enum { HIGH_FREQ_REF_CLK = 2 }; };

			static access_t prepare_one_shot()
			{
				access_t cr = 0;
				En_mod::set(cr, En_mod::RELOAD);
				Oci_en::set(cr, 1);
				Clk_src::set(cr, Clk_src::HIGH_FREQ_REF_CLK);
				return cr;
			}
		};

		struct Sr   : Register<0x4,  32> { struct Ocif : Bitfield<0, 1> { }; };
		struct Cmpr : Register<0xc,  32> { };
		struct Cnt  : Register<0x10, 32> { enum { MAX = ~0U }; };

		enum {
			EPIT_MAX_USEC = unsigned(Cnt::MAX) / TICKS_PER_US
		};

		/* Epit counter */
		struct Counter { unsigned value; };

	public:

		enum {
			EPIT_2_IRQ       = 89,
			EPIT_2_MMIO_BASE = 0x020d4000,
			EPIT_2_MMIO_SIZE = 0x00004000
		};

		struct Wakeup_dispatcher : Interface
		{
			virtual void dispatch_device_wakeup() = 0;
		};

		struct Deadline : Clock { };

		static constexpr Deadline infinite_deadline { uint64_t(-1) };

	private:

		Env &_env;

		Irq_connection _timer_irq { _env, unsigned(EPIT_2_IRQ) };

		uint64_t _max_timeout_us { EPIT_MAX_USEC };

		Wakeup_dispatcher &_dispatcher;

		Signal_handler<Device> _handler { _env.ep(), *this, &Device::_handle_timeout };

		uint64_t _curr_time_us      { };
		Counter  _last_read         { Cnt::MAX };

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

			return { .value = min(unsigned(rel_us * TICKS_PER_US), unsigned(Cnt::MAX)) };
		}

		void _handle_timeout()
		{
			_dispatcher.dispatch_device_wakeup();
		}

		void _set_counter(Counter const &cnt)
		{
			_timer_irq.ack_irq();

			/* disable timer */
			write<Cr::En>(0);

			/* clear interrupt and install timeout */
			write<Sr::Ocif>(1);
			write<Cr>(Cr::prepare_one_shot());
			write<Cmpr>(Cnt::MAX - cnt.value);

			/* start timer */
			write<Cr::En>(1);
		}

		void _advance_current_time()
		{
			auto const epit = Counter(read<Cnt>());

			if (_last_read.value < epit.value)
				warning("counter wrapped - not expected/supported");

			auto const diff = _last_read.value >= epit.value
			                ? Counter(_last_read.value - epit.value)
			                : Counter(0);

			_curr_time_us  += _convert_counter_diff_to_us(diff);

			_last_read = epit;
		}

	public:

		Device(Env &env, Attached_io_mem_dataspace &mmio_ds, Wakeup_dispatcher &dispatcher)
		:
			Mmio({ mmio_ds.local_addr<char>(), EPIT_2_MMIO_SIZE }),
			_env(env), _dispatcher(dispatcher)
		{
			_timer_irq.sigh(_handler);

			while (read<Cr::Swr>()) { }

			_handle_timeout();
		}

		Clock now()
		{
			_advance_current_time();

			return Clock { .us = _curr_time_us };
		}

		void update_deadline(Deadline const deadline)
		{
			uint64_t const now_us = now().us;
			uint64_t const rel_us = (deadline.us > now_us)
			                      ? min(_max_timeout_us, deadline.us - now_us)
			                      : 1;

			auto const epit_cnt = _convert_relative_us_to_counter(rel_us);

			_last_read.value = Cnt::MAX;

			_set_counter(epit_cnt);
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
	                  Diag      const &diag,
	                  Alarms          &alarms,
	                  Device          &device)
	:
		Session_object(env.ep(), resources, label, diag),
		_alarms(alarms), _device(device)
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

		Session_component *_create_session(const char *args) override
		{
			return new (md_alloc())
				Session_component(_env,
				                  session_resources_from_args(args),
				                  session_label_from_args(args),
				                  session_diag_from_args(args),
				                  _alarms, _device);
		}

		void _upgrade_session(Session_component *s, const char *args) override
		{
			s->upgrade(ram_quota_from_args(args));
			s->upgrade(cap_quota_from_args(args));
		}

		void _destroy_session(Session_component *session) override
		{
			Genode::destroy(md_alloc(), session);
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

	Attached_io_mem_dataspace _mmio { _env, Device::EPIT_2_MMIO_BASE,
	                                        Device::EPIT_2_MMIO_SIZE };

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
