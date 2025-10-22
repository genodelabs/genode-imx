/*
 * \brief   Platform implementations specific for base-hw and MNT Pocket
 * \author  Stefan Kalkowski
 * \date    2024-08-21
 */

/*
 * Copyright (C) 2024 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#include <platform.h>

enum Soc_imx8mp {
	I2C_0_BASE      = 0x30a20000,
	CCM_ANALOG_BASE = 0x30360000,
	CCM_BASE        = 0x30380000,
};


class I2c : Genode::Mmio<0x12>
{
	private:

		struct Address : public Register<0x0, 16>
		{
			struct Addr : Bitfield<1,7> {};
		};

		struct Freq_divider : public Register<0x4, 16> {};

		struct Control : public Register<0x8, 16>
		{
			struct Repeat_start        : Bitfield<2,1> {};
			struct Tx_ack_enable       : Bitfield<3,1> {};
			struct Tx_rx_select        : Bitfield<4,1> {};
			struct Master_slave_select : Bitfield<5,1> {};
			struct Irq_enable          : Bitfield<6,1> {};
			struct Enable              : Bitfield<7,1> {};
		};

		struct Status : public Register<0xc, 16>
		{
			struct Rcv_ack             : Bitfield<0,1> {};
			struct Irq                 : Bitfield<1,1> {};
			struct Slave_rw            : Bitfield<2,1> {};
			struct Arbitration_lost    : Bitfield<4,1> {};
			struct Busy                : Bitfield<5,1> {};
			struct Addressed_as_slave  : Bitfield<6,1> {};
			struct Data_transfer       : Bitfield<7,1> {};
		};

		struct Data : public Register<0x10, 16> { };


		class No_ack : Genode::Exception {};

		void _busy() { while (!read<Status::Busy>()); }

		void _start()
		{
			write<Freq_divider>(0x2a);
			write<Status>(0);
			write<Control>(Control::Enable::bits(1));

			while (!read<Control::Enable>()) { ; }

			write<Control::Master_slave_select>(1);

			_busy();

			write<Control>(Control::Tx_rx_select::bits(1)        |
			               Control::Tx_ack_enable::bits(1)       |
			               Control::Irq_enable::bits(1)          |
			               Control::Master_slave_select::bits(1) |
			               Control::Enable::bits(1));
		}

		void _stop()
		{
			write<Control>(0);
		}

		void _write(Genode::uint8_t value)
		{
			write<Data>(value);

			while (!read<Status::Irq>());

			write<Status::Irq>(0);

			if (read<Status::Rcv_ack>()) throw No_ack();
		}

	public:

		I2c() : Genode::Mmio<SIZE>({(char*)I2C_0_BASE, SIZE})
		{
			write<Control>(0);
			write<Status>(0);
		}

		void send(Genode::uint8_t addr, const Genode::uint8_t *buf,
		          Genode::size_t num)
		{
			while (true) {
				try {
					_start();

					_write(addr << 1);
					for (Genode::size_t i = 0; i < num; i++)
						_write(buf[i]);
					_stop();
					return;
				} catch(No_ack) { }
				 _stop();
			}
		}


		void recv(Genode::uint8_t addr, Genode::uint8_t *buf,
		          Genode::size_t num)
		{
			while (true) {
				try {
					_start();

					_write((Genode::uint8_t)(addr << 1 | 1));

					write<Control::Tx_rx_select>(0);
					if (num > 1)
						write<Control::Tx_ack_enable>(0);
					read<Data>(); /* dummy read */

					for (Genode::size_t i = 0; i < num; i++) {

						while (!read<Status::Irq>());

						write<Status::Irq>(0);

						if (i == num-1) {
							write<Control::Tx_rx_select>(0);
							write<Control::Master_slave_select>(0);
							while (read<Status::Busy>()) ;
						} else if (i == num-2) {
							write<Control::Tx_ack_enable>(1);
						}

						buf[i] = (Genode::uint8_t)read<Data>();
					}

					_stop();
					return;
				} catch(No_ack) {
					Genode::log("no ack");
					 _stop();
				}
			}
		}
};


struct Arm_pll : Genode::Mmio<0xc>
{
	struct Gen_ctrl   : Register<0x0, 32> {
		struct Bypass : Bitfield<4, 1> {};
		struct Reset  : Bitfield<9, 1> {
			enum State { RESET = 0, NO_RESET = 1 };
		};
		struct Lock_sel    : Bitfield<29, 1> {};
		struct Lock_status : Bitfield<31, 1> {};
	};

	struct Fdiv_ctl0: Register<0x4, 32> {
		struct Post_div : Bitfield<0, 3> {};
		struct Pre_div  : Bitfield<4, 6> {};
		struct Main_div : Bitfield<12, 10> {};
	};

	void wait_for_lock()
	{
		unsigned count = 0;
		while(!read<Gen_ctrl::Lock_status>())
		{
			if (count++ < 1024)
				continue;
			Genode::error(" PLL did not achieved lock.");
			return;
		}
	}

	Arm_pll() : Mmio({(char*)(CCM_ANALOG_BASE+0x84), SIZE})
	{
		write<Gen_ctrl::Lock_sel>(1);
		write<Gen_ctrl::Reset>(Gen_ctrl::Reset::RESET);
		write<Gen_ctrl::Bypass>(1);
		Fdiv_ctl0::access_t v = read<Fdiv_ctl0>();
		Fdiv_ctl0::Pre_div::set(v, 3);
		Fdiv_ctl0::Main_div::set(v, 255);
		Fdiv_ctl0::Post_div::set(v, 0);
		write<Fdiv_ctl0>(v);
		for (unsigned i = 0; i < 1000; i++) ;
		write<Gen_ctrl::Reset>(Gen_ctrl::Reset::NO_RESET);
		wait_for_lock();
		write<Gen_ctrl::Bypass>(0);
	}
};


template <unsigned long OFF>
struct Root_clk : Genode::Mmio<4>
{
	struct Reg : Register<0x0, 32>
	{
		struct Selector : Bitfield<24,3> {};
	};

	Root_clk() : Mmio({(char*)(CCM_BASE+OFF), SIZE}) {}

	void select(Genode::uint32_t v)
	{
		/*
		 * few clock muxer on 8m need to be written twice,
		 * have a look at:
		 * https://www.uwsg.indiana.edu/hypermail/linux/kernel/2003.1/05579.html
		 * for an explanation
		 */
		write<typename Reg::Selector>(v);
		write<typename Reg::Selector>(v);
	}
};


Bootstrap::Platform::Board::Board()
:
	early_ram_regions(Memory_region { ::Board::RAM_0_BASE, ::Board::RAM_0_SIZE }),
	late_ram_regions(Memory_region { ::Board::RAM_1_BASE, ::Board::RAM_1_SIZE }),
	core_mmio(Memory_region { ::Board::UART_BASE, ::Board::UART_SIZE },
	          Memory_region { ::Board::Cpu_mmio::IRQ_CONTROLLER_DISTR_BASE,
	                          ::Board::Cpu_mmio::IRQ_CONTROLLER_DISTR_SIZE },
	          Memory_region { ::Board::Cpu_mmio::IRQ_CONTROLLER_REDIST_BASE,
	                          ::Board::Cpu_mmio::IRQ_CONTROLLER_REDIST_SIZE })
{
	/*
	 * First, increase voltage to 1V via power-management IC
	 * PCA9450 (rev. c) from NXP
	 * (https://www.nxp.com/docs/en/data-sheet/PCA9450.pdf)
	 */
	enum Pca9450 {
		I2C_PMIC_ADDR  = 0x25, /* address of PMIC on I2C bus */
		BUCK2_SEL_REG  = 0x14, /* BUCK regulator 2 is used for CPUs */
		BUCK2_DVS0_VAL = 0x20, /* according to voltage table == 1V */
	};

	I2c i2c {};
	Genode::uint8_t buf[10];
	buf[0] = BUCK2_SEL_REG;  /* first written value is the address */
	buf[1] = BUCK2_DVS0_VAL; /* then write the value */
	i2c.send(I2C_PMIC_ADDR, buf, 2);

	/*
	 * After voltage is settled, switch ref-clock of CPU
	 * to system PLL1 (800 MHz), adapt the ARM PLL to 1.8 GHz,
	 * and switch the CPU ref-clock to it
	 */
	enum {
		A53_ROOT_SYS1_PLL     = 0b100,
		A53_ROOT_SEL_A53_ROOT = 0,
		A53_ROOT_SEL_ARM_PLL  = 1
	};

	Root_clk<0x8000> a53_root;
	Root_clk<0x9880> a53_root_sel;
	a53_root.select(A53_ROOT_SYS1_PLL);
	a53_root_sel.select(A53_ROOT_SEL_A53_ROOT);
	Arm_pll pll {};
	a53_root_sel.select(A53_ROOT_SEL_ARM_PLL);
}


void Board::Cpu::wake_up_all_cpus(void * ip)
{
	enum Function_id { CPU_ON = 0xC4000003 };

	unsigned long result = 0;
	for (unsigned i = 1; i < NR_OF_CPUS; i++) {
		asm volatile("mov x0, %1  \n"
		             "mov x1, %2  \n"
		             "mov x2, %3  \n"
		             "mov x3, %2  \n"
		             "smc #0      \n"
		             "mov %0, x0  \n"
		             : "=r" (result) : "r" (CPU_ON), "r" (i), "r" (ip)
		                      : "x0", "x1", "x2", "x3", "x4", "x5", "x6", "x7",
		                        "x8", "x9", "x10", "x11", "x12", "x13", "x14");
	}
}
