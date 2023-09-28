/*
 * \brief  Global power controller for i.MX8
 * \author Stefan Kalkowski
 * \date   2020-06-12
 */

/*
 * Copyright (C) 2020 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#pragma once

#include <base/env.h>
#include <util/string.h>

#include <power.h>

struct Gpc
{
	struct Domain : Driver::Power
	{
		enum {
			SIP_SERVICE_FUNC = 0xc2000000,
			GPC_PM_DOMAIN    = 0x3,
			ON               = 1,
			OFF              = 0
		};

		struct Control: Genode::Rpc_client<Genode::Pd_session::System_control>
		{
			explicit Control(Genode::Capability<Genode::Pd_session::System_control> cap)
			: Genode::Rpc_client<Genode::Pd_session::System_control>(cap) { }

			Genode::Pd_session::Managing_system_state system_control(Genode::Pd_session::Managing_system_state const &state) override
			{
				return call<Rpc_system_control>(state);
			}
		} control;

		unsigned long id;

		Domain(Driver::Powers     & powers,
		       Genode::Pd_session & pd,
		       Driver::Power::Name  name,
		       unsigned long        fn_id)
		:
			Power(powers, name),
			control(pd.system_control_cap(Genode::Affinity::Location())),
			id(fn_id) {}

		void _on() override
		{
			Genode::Pd_session::Managing_system_state state;
			state.r[0] = SIP_SERVICE_FUNC;
			state.r[1] = GPC_PM_DOMAIN;
			state.r[2] = id;
			state.r[3] = ON;

			state = control.system_control(state);

			if (state.r[0] != 0)
				Genode::error("Cannot enable power domain ", name);
		}

		void _off() override
		{
			Genode::Pd_session::Managing_system_state state;
			state.r[0] = SIP_SERVICE_FUNC;
			state.r[1] = GPC_PM_DOMAIN;
			state.r[2] = id;
			state.r[3] = OFF;

			state = control.system_control(state);

			if (state.r[0] != 0)
				Genode::error("Cannot disable power domain ", name);
		}
	};

	Genode::Env    & env;
	Driver::Powers & powers;

	Domain mipi      { powers, env.pd(), "mipi",      0 };
	Domain pcie_1    { powers, env.pd(), "pcie_1",    1 };
	Domain usb_otg_1 { powers, env.pd(), "usb_otg_1", 2 };
	Domain usb_otg_2 { powers, env.pd(), "usb_otg_2", 3 };
	Domain gpu       { powers, env.pd(), "gpu",       4 };
	Domain vpu       { powers, env.pd(), "vpu",       5 };
	Domain hdmi      { powers, env.pd(), "hdmi",      6 };
	Domain disp      { powers, env.pd(), "disp",      7 };
	Domain csi_1     { powers, env.pd(), "csi_1",     8 };
	Domain csi_2     { powers, env.pd(), "csi_2",     9 };
	Domain pcie_2    { powers, env.pd(), "pcie_2",   10 };

	Gpc(Genode::Env & env, Driver::Powers & powers)
	: env(env), powers(powers)
	{
		/* FIXME: turn off all power domains */
	};
};
