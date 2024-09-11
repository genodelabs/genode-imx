/*
 * \brief  Dummy definitions of Linux Kernel functions - handled manually
 * \author Stefan Kalkowski
 * \date   2022-10-17
 */

/*
 * Copyright (C) 2022 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#include <lx_emul.h>

unsigned long __must_check __arch_copy_from_user(void *to, const void __user *from, unsigned long n);
unsigned long __must_check __arch_copy_from_user(void *to, const void __user *from, unsigned long n)
{
	lx_emul_trace_and_stop(__func__);
}


unsigned long __must_check __arch_copy_to_user(void __user *to, const void *from, unsigned long n);
unsigned long __must_check __arch_copy_to_user(void __user *to, const void *from, unsigned long n)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pm_runtime.h>

void pm_runtime_release_supplier(struct device_link * link)
{
	lx_emul_trace(__func__);
}


#include <linux/pm_domain.h>

int dev_pm_domain_attach(struct device * dev,bool power_on)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/pm_domain.h>

void dev_pm_domain_detach(struct device * dev,bool power_off)
{
	lx_emul_trace(__func__);
}


#include <linux/posix-timers.h>

void __init posix_cputimers_init_work(void)
{
    lx_emul_trace(__func__);
}


#include <linux/pinctrl/consumer.h>

int pinctrl_pm_select_default_state(struct device * dev)
{
	lx_emul_trace(__func__);
	return  0;
}


#include <linux/pinctrl/consumer.h>

int pinctrl_pm_select_sleep_state(struct device * dev)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/pci.h>

unsigned long pci_address_to_pio(phys_addr_t addr)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/pm_runtime.h>

void __pm_runtime_use_autosuspend(struct device * dev,bool use)
{
	lx_emul_trace(__func__);
}


#include <linux/pm_runtime.h>

int __pm_runtime_set_status(struct device * dev,unsigned int status)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/pm_runtime.h>

int __pm_runtime_suspend(struct device * dev,int rpmflags)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/pm_runtime.h>

void __pm_runtime_disable(struct device * dev,bool check_resume)
{
	lx_emul_trace(__func__);
}


#include <linux/pm_runtime.h>

void pm_runtime_enable(struct device * dev)
{
	lx_emul_trace(__func__);
}


#include <linux/pm_runtime.h>

void pm_runtime_set_autosuspend_delay(struct device * dev,int delay)
{
	lx_emul_trace(__func__);
}


#include <linux/regulator/consumer.h>

int devm_regulator_get_enable_optional(struct device * dev,const char * id)
{
	lx_emul_trace(__func__);
	return 0;
}


