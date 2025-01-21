/*
 * \brief  i.MX8 framebuffer driver Linux port
 * \author Stefan Kalkowski
 * \date   2021-03-08
 */

/*
 * Copyright (C) 2021 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#include <base/attached_rom_dataspace.h>
#include <base/component.h>
#include <timer_session/connection.h>
#include <capture_session/connection.h>
#include <os/pixel_rgb888.h>
#include <util/reconstructible.h>
#include <lx_emul/fb.h>
#include <lx_emul/init.h>
#include <lx_kit/env.h>
#include <lx_kit/init.h>

namespace Framebuffer {
	using namespace Genode;
	struct Driver;
}


struct Framebuffer::Driver
{
	Env                  & env;
	Timer::Connection      timer   { env };
	Attached_rom_dataspace dtb_rom { env, "dtb" };

	class Fb
	{
		private:

			Capture::Connection         _capture;
			Capture::Area const         _size;
			Capture::Connection::Screen _captured_screen;
			void                      * _base;
			bool                        _ccw; /* blit 90 deg counterclockwise */

			/*
			 * Noncopyable
			 */
			Fb(const Fb&);
			Fb & operator=(const Fb&);

			struct Pixel_access
			{
				Capture::Area const _size;
				Capture::Pixel     *_addr;

				Pixel_access(Capture::Area const size,
				             Capture::Pixel *addr)
				: _size(size), _addr(addr) { }

				Capture::Pixel *at(int x, int y)
				{
					return _addr + y * _size.w + x;
				}

				Capture::Pixel *at_ccw(int x, int y)
				{
					return _addr + (_size.w - x - 1) * _size.h + y;
				}
			};

			void _blit_ccw(Surface<Capture::Pixel> &surface,
			               Texture<Capture::Pixel> const &texture)
			{
				using Rect = Capture::Rect;
				Rect const clipped = Rect::intersect(Rect({0, 0}, texture.size()),
				                                     surface.clip());

				if (!clipped.valid())
					return;

				Pixel_access src { _size, const_cast<Capture::Pixel *>(texture.pixel()) };
				Pixel_access dst { _size, surface.addr()  };

				Capture::Pixel *spx = src.at(clipped.x1(), clipped.y1());
				Capture::Pixel *dpx = dst.at_ccw(clipped.x1(), clipped.y1());

				/*
				 * BIG time optimization necessary, at least avoid any expansive
				 * operation (like mul/div etc.) for now
				 */
				size_t w = 0;

				/* col and row refer to src, they have inverted meaning at dst */
				for (unsigned row = 0; row < clipped.h(); row++, w += _size.w) {
					size_t h = 0;
					for (unsigned col = 0; col < clipped.w(); col++, h += _size.h)
						(dpx - h + row)->pixel = (spx + w + col)->pixel;
				}
			}

			void _apply_to_surface_ccw(Surface<Capture::Pixel> &surface)
			{
				using Pixel = Capture::Pixel;
				using Affected_rects = Capture::Session::Affected_rects;

				Affected_rects const affected = _capture.capture_at(Capture::Point(0, 0));

				_captured_screen.with_texture([&] (Texture<Pixel> const &texture) {

					affected.for_each_rect([&] (Capture::Rect const rect) {

						surface.clip(rect);

						_blit_ccw(surface, texture);
					});
				});
			}

		public:

			void paint()
			{
				using Pixel = Capture::Pixel;
				Surface<Pixel> surface((Pixel*)_base, _size);

				if (_ccw)
					_apply_to_surface_ccw(surface);
				else
					_captured_screen.apply_to_surface(surface);
			}


			Fb(Env & env, void * base, unsigned xres, unsigned yres, bool ccw)
			:
				_capture(env),
				_size{ ccw ? yres : xres, ccw ? xres : yres },
				_captured_screen(_capture, env.rm(), { .px     = _size,
				                                       .mm     = { },
				                                       .rotate = { },
				                                       .flip   = { } }),
				_base(base),
				_ccw(ccw) {}
	};

	enum { MAX_SCREENS = 2 };
	Constructible<Fb> fb[MAX_SCREENS] {};

	void handle_timer()
	{
		for (unsigned i = 0; i < MAX_SCREENS; i++)
			if (fb[i].constructed()) fb[i]->paint();
	}

	Signal_handler<Driver> timer_handler { env.ep(), *this,
	                                       &Driver::handle_timer };

	Signal_handler<Driver> _signal_handler {
		env.ep(), *this, &Driver::_handle_signal };

	void _handle_signal()
	{
		Lx_kit::env().scheduler.execute();
	}

	Driver(Env & env) : env(env)
	{
		Lx_kit::initialize(env, _signal_handler);
		env.exec_static_constructors();
	}

	void start()
	{
		log("--- i.MX 8MQ framebuffer driver started ---");

		lx_emul_start_kernel(dtb_rom.local_addr<void>());

		timer.sigh(timer_handler);
		timer.trigger_periodic(20*1000);
	}
};


static Framebuffer::Driver & driver(Genode::Env & env)
{
	static Framebuffer::Driver driver(env);
	return driver;
}


/**
 * Can be called already as side-effect of `lx_emul_start_kernel`,
 * that's why the Driver object needs to be constructed already here.
 */
extern "C" void lx_emul_framebuffer_ready(void * base, unsigned long,
                                          unsigned xres, unsigned yres)
{
	for (unsigned i = 0; i < Framebuffer::Driver::MAX_SCREENS; i++) {
		Genode::Env & env = Lx_kit::env().env;

		if (driver(env).fb[i].constructed())
			continue;

		/* rotate */
		bool ccw = false;

		/* check for MNT Pocket Reform in device tree */
		if (lx_emul_machine_is_compatible("mntre,pocket-reform")) ccw = true;

		driver(env).fb[i].construct(env, base, xres, yres, ccw);

		Genode::log("--- i.MX 8MQ framebuffer driver screen ", i, " initialized ---");
		return;
	}
}


void Component::construct(Genode::Env &env)
{
	driver(env).start();
}
