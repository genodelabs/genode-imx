/*
 * \brief  Virtual Machine Monitor VM definition
 * \author Stefan Kalkowski
 * \author Martin Stein
 * \author Benjamin Lamowski
 * \date   2012-06-25
 */

/*
 * Copyright (C) 2012-2023 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

/* Genode includes */
#include <base/attached_rom_dataspace.h>

/* local includes */
#include <vm.h>
#include <mmu.h>

using namespace Vmm;


void Vm::_load_kernel(Vcpu_state &state)
{
	Attached_rom_dataspace kernel(_env, _kernel.string());
	memcpy((void*)(_ram.local() + _kernel_off),
	       kernel.local_addr<void>(), kernel.size());
	state.ip = _ram.base() + _kernel_off;
}


void Vm::_load_kernel_surroundings()
{
	/* load initrd */
	enum { INITRD_OFFSET = 0x1000000 };
	Attached_rom_dataspace initrd(_env, "initrd.gz");
	memcpy((void*)(_ram.local() + INITRD_OFFSET),
	       initrd.local_addr<void>(), initrd.size());

	/* load ATAGs */
	Atag tag((void*)(_ram.local() + ATAG_OFFSET));
	tag.setup_mem_tag(_ram.base(), _ram.size());
	tag.setup_cmdline_tag(_cmdline.string());
	tag.setup_initrd2_tag(_ram.base() + INITRD_OFFSET, initrd.size());
	if (_board.value) {
		tag.setup_rev_tag(_board.value); }
	tag.setup_end_tag();
}


Vm::Vm(Env                &env,
       Kernel_name  const &kernel,
       Command_line const &cmdline,
       addr_t              ram_base,
       size_t              ram_size,
       off_t               kernel_off,
       Machine_type        machine,
       Board_revision      board,
       Allocator          &alloc,
       Vcpu_handler_base  &handler)
:
	_env(env), _kernel(kernel), _cmdline(cmdline), _kernel_off(kernel_off),
	_machine(machine), _board(board), _ram(env, ram_base, ram_size),
	_vcpu(_vm, alloc, handler, _exit_config)
{ }

void Vm::start(Vcpu_state &state)
{
	bzero((void*)&state, sizeof(Vcpu_state));
	_load_kernel(state);
	_load_kernel_surroundings();
	state.cpsr          = 0x93; /* SVC mode and IRQs disabled */
	state.r0            = 0;
	state.r1            = _machine.value;
	state.r2            = _ram.base() + _board_info_offset();
	state.irq_injection = 0;
}


void Vm::inject_irq(unsigned irq)
{
	with_state([this,irq](Vcpu_state &state) {
		if (state.irq_injection) { throw Inject_irq_failed(); }
		state.irq_injection = irq;
		return true;
	});
}



void Vm::dump(Vcpu_state &state)
{
	char const *mod[] = { "und", "svc", "abt", "irq", "fiq" };
	char const *exc[] = { "invalid", "reset", "undefined", "smc",
	                      "pf_abort", "data_abort", "irq", "fiq" };

	auto log_adr_reg = [&] (char const *reg, addr_t val) {
		log("  ", reg, "      = ", Hex(val, Hex::PREFIX, Hex::PAD), " ",
		    Hex(va_to_pa(state, val), Hex::PREFIX, Hex::PAD)); };

	auto log_mod_reg = [&] (char const *reg, addr_t val, char const *mod) {
		log("  ", reg, "_", mod, "  = ", Hex(val, Hex::PREFIX, Hex::PAD), " ",
		    Hex(va_to_pa(state, val), Hex::PREFIX, Hex::PAD)); };

	log("Cpu state:");
	log("  Register     Virt       Phys");
	log("------------------------------------");
	log_adr_reg("r0   ", state.r0);
	log_adr_reg("r1   ", state.r1);
	log_adr_reg("r2   ", state.r2);
	log_adr_reg("r3   ", state.r3);
	log_adr_reg("r4   ", state.r4);
	log_adr_reg("r5   ", state.r5);
	log_adr_reg("r6   ", state.r6);
	log_adr_reg("r7   ", state.r7);
	log_adr_reg("r8   ", state.r8);
	log_adr_reg("r9   ", state.r9);
	log_adr_reg("r10  ", state.r10);
	log_adr_reg("r11  ", state.r11);
	log_adr_reg("r12  ", state.r12);
	log_adr_reg("sp   ", state.sp);
	log_adr_reg("lr   ", state.lr);
	log_adr_reg("ip   ", state.ip);
	log_adr_reg("cpsr ", state.cpsr);
	for (unsigned i = 0; i < Vcpu_state::Mode_state::MAX; i++) {
		log_mod_reg("sp   ", state.mode[i].sp,   mod[i]);
		log_mod_reg("lr   ", state.mode[i].lr,   mod[i]);
		log_mod_reg("spsr ", state.mode[i].spsr, mod[i]);
	}
	log("  ttbr0      = ", Hex(state.ttbr[0], Hex::PREFIX, Hex::PAD));
	log("  ttbr1      = ", Hex(state.ttbr[1], Hex::PREFIX, Hex::PAD));
	log("  ttbrc      = ", Hex(state.ttbrc  , Hex::PREFIX, Hex::PAD));
	log_adr_reg("dfar ",  state.dfar);
	log("  exception  = ", exc[state.cpu_exception]);
}


addr_t Vm::va_to_pa(Vcpu_state & state, addr_t va)
{
	try {
		Mmu mmu(state, _ram);
		return mmu.phys_addr(va);
	}
	catch(Ram::Invalid_addr) { }
	return 0;
}
