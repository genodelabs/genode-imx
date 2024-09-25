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

	/* names are from imx8mp reference manual */
	Domain hsiomix         { powers, env.pd(), "hsiomix",          0 };
	Domain pcie_phy        { powers, env.pd(), "pcie_phy",         1 };
	Domain usb1_phy        { powers, env.pd(), "usb1_phy",         2 };
	Domain usb2_phy        { powers, env.pd(), "usb2_phy",         3 };
	Domain mlmix           { powers, env.pd(), "mlmix",            4 };
	Domain audiomix        { powers, env.pd(), "audiomix",         5 };
	Domain gpumix          { powers, env.pd(), "gpumix",           6 };
	Domain gpu_2d          { powers, env.pd(), "gpu_2d",           7 };
	Domain gpu_3d          { powers, env.pd(), "gpu_3d",           8 };
	Domain vpumix          { powers, env.pd(), "vpumix",           9 };
	Domain vpu_g1          { powers, env.pd(), "vpu_g1",          10 };
	Domain vpu_g2          { powers, env.pd(), "vpu_g2",          11 };
	Domain vpu_h1          { powers, env.pd(), "vpu_h1",          12 };
	Domain mediamix        { powers, env.pd(), "mediamix",        13 };
	Domain mediamix_ispdwp { powers, env.pd(), "mediamix_ispdwp", 14 };
	Domain mipi_phy1       { powers, env.pd(), "mipi_phy1",       15 };
	Domain mipi_phy2       { powers, env.pd(), "mipi_phy2",       16 };
	Domain hdmimix         { powers, env.pd(), "hdmimix",         17 };
	Domain hdmi_phy        { powers, env.pd(), "hdmi_phy",        18 };
	Domain ddrmix          { powers, env.pd(), "ddrmix",          19 };

	Gpc(Genode::Env & env, Driver::Powers & powers)
	: env(env), powers(powers) { };
};
