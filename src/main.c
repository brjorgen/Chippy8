#include "../includes/chip8.h"

void	chip8_cpu_exec_ins_unhandled(t_chip8 *cpu, uint8_t *u8_memptr){
	(void)cpu;
	(void)u8_memptr;
	write(1, "Instruction unandled!\n", 23);
}


// gotta implement this
void	(*chip8_cpu_exec_ins[__CHIP8_INS_TOTAL])(t_chip8 *cpu, uint8_t *u8_memptr) = {
	[0x0]	= &chip8_cpu_exec_00XX,
	[0x1]	= &chip8_cpu_exec_ins_jmp,
	[0x2]	= &chip8_cpu_exec_ins_unhandled,
	[0x3]	= &chip8_cpu_exec_ins_unhandled,
	[0x4]	= &chip8_cpu_exec_ins_unhandled,
	[0x5]	= &chip8_cpu_exec_ins_unhandled,
	[0x6]	= &chip8_cpu_exec_ins_unhandled,
	[0x7]	= &chip8_cpu_exec_ins_unhandled,
	[0x8]	= &chip8_cpu_exec_8NNX,
	[0x9]	= &chip8_cpu_exec_ins_unhandled,
	[0xa]	= &chip8_cpu_exec_ins_unhandled,
	[0xb]	= &chip8_cpu_exec_ins_unhandled,
	[0xc]	= &chip8_cpu_exec_ins_unhandled,
	[0xd]	= &chip8_cpu_exec_ins_unhandled,
	[0xe]	= &chip8_cpu_exec_ins_unhandled,
	[0xf]	= &chip8_cpu_exec_9NNX,
};

void	chip8_cpu_loop(t_chip8 *cpu){
	uint8_t	*u8_memptr;
	uint8_t	u8_opcode;

	while (cpu->pc < cpu->size + CHIP8_SECTOR_START_PROG){
		u8_memptr = &cpu->mem[cpu->pc];			// fetch
		u8_opcode = chip8_ins_get_opcode(u8_memptr);	// decode
		chip8_cpu_exec_ins[u8_opcode](cpu, u8_memptr);	// execute
		cpu->pc += 2;					// next
	}
}

int	main(int ac, char *av[]){
	if (ac == 2){
		t_chip8 cpu;

		chip8_cpu_setup(&cpu);
		cpu.size = chip8_load_program(av[1], &cpu.mem);
		chip8_cpu_loop(&cpu);
		write(1, "== chip8 emulation terminated. See ya! ==\n", 33);
	}
	return (0);
}
