/*
 * \brief  Freescale's TrustZone aware interrupt controller
 * \author Stefan Kalkowski
 * \date   2012-10-24
 */

/*
 * Copyright (C) 2012-2017 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _SRC__LIB__HW__SPEC__ARM__IMX_TZIC_H_
#define _SRC__LIB__HW__SPEC__ARM__IMX_TZIC_H_

#include <hw/spec/arm/cpu.h>
#include <util/mmio.h>

namespace Hw {

	/**
	 * The TrustZone-ware interrupt controller from Freescale is used
	 * on uni-processor platforms only, therefore there is no difference
	 * in between global and local controller. Anyway, the local interface
	 * is the one actively used by the kernel code, so we fill that with
	 * the actual functionality, and leave the global controller as a
	 * simple class used to get the overall interrupt count only.
	 */
	struct Global_interrupt_controller
	{
		static constexpr unsigned NR_OF_IRQ = 109;

		/* no suspend/resume on this platform */
		void resume() {}
	};

	class Local_interrupt_controller;
}


class Hw::Local_interrupt_controller : public Genode::Mmio<0xf04>
{
	protected:

		static constexpr unsigned NR_OF_IRQ =
			Global_interrupt_controller::NR_OF_IRQ;

		/**
		 * Software Interrupt Trigger Register
		 */
		struct Swint : Register<0xf00, 32> {
			struct Intid  : Bitfield<0,10> { }; };

		/**
		 * Interrupt control register
		 */
		struct Intctrl : Register<0, 32>
		{
			struct Enable    : Bitfield<0,1>  { };
			struct Nsen      : Bitfield<16,1> { };
			struct Nsen_mask : Bitfield<31,1> { };
		};

		/**
		 * Priority mask register
		 */
		struct Priomask : Register<0xc, 32> {
			struct Mask : Bitfield<0,8> { }; };

		/**
		 * Interrupt security registers
		 */
		struct Intsec : Register_array<0x80, 32, NR_OF_IRQ, 1> {
			struct Nonsecure : Bitfield<0, 1> { }; };

		/**
		 * Interrupt set enable registers
		 */
		struct Enset : Register_array<0x100, 32, NR_OF_IRQ, 1, true> {
			struct Set_enable : Bitfield<0, 1> { }; };

		/**
		 * Interrupt clear enable registers
		 */
		struct Enclear : Register_array<0x180, 32, NR_OF_IRQ, 1, true> {
			struct Clear_enable : Bitfield<0, 1> { }; };

		/**
		 * Interrupt priority level registers
		 */
		struct Priority  : Register_array<0x400, 32, NR_OF_IRQ, 8> { };

		/**
		 * Highest interrupt pending registers
		 */
		struct Hipndr  : Register_array<0xd80, 32, NR_OF_IRQ, 1, true> {
			struct Pending : Bitfield<0, 1> { }; };

		/**
		 * Validate request number 'i'
		 */
		bool _valid(unsigned const i) const { return i < NR_OF_IRQ; }

	public:

		enum { IPI = 0xffff };

		Local_interrupt_controller(Global_interrupt_controller&);

		/**
		 * Receive a pending request number 'i'
		 */
		bool take_request(unsigned & i)
		{
			for (unsigned j = 0; j < NR_OF_IRQ; j++) {
				if (!read<Hipndr::Pending>(j)) { continue; }
				i = j;
				return true;
			}
			return false;
		}

		void finish_request() { }

		void irq_mode(unsigned, unsigned, unsigned) { }

		/**
		 * Unmask interrupt 'i'
		 */
		void unmask(unsigned const i, Hw::Arm_cpu::Id) {
			if (_valid(i)) { write<Enset::Set_enable>(1, i); } }

		/**
		 * Mask interrupt 'i'
		 */
		void mask(unsigned const i) {
			if (_valid(i)) { write<Enclear::Clear_enable>(1, i); } }

		/*
		 * Trigger interrupt 'i' from software if possible
		 */
		void trigger(unsigned const i) {
			write<Swint>(Swint::Intid::bits(i)); }

		bool secure(unsigned i) {
			return !read<Intsec::Nonsecure>(i); }

		static constexpr bool fast_interrupts() { return true; }
};

#endif /* _SRC__LIB__HW__SPEC__ARM__IMX_TZIC_H_ */
