/*
 * \brief  ST Microelectronics DMMAC Ethernet driver
 * \author Norman Feske
 * \author Stefan Kalkowski
 * \date   2024-05-28
 */

/*
 * Copyright (C) 2024 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#include <lx_user/init.h>
#include <lx_emul/nic.h>
#include <linux/rtnetlink.h>


void lx_user_init(void)
{
	lx_emul_nic_init();
}


void lx_user_handle_io(void)
{

	lx_emul_nic_handle_io();
}


/*
 * Called whenever the link state changes
 */
void rtmsg_ifinfo(int type, struct net_device * dev, unsigned int change, gfp_t flags,
                  u32 portid, const struct nlmsghdr *nlh)
{
	lx_emul_nic_handle_io();
}
