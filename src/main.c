#include "../includes/chip8.h"

void	chip8_cpu_exec_ins_unhandled(t_chip8 *cpu, uint8_t *u8_memptr){
	(void)cpu;
	(void)u8_memptr;
	write(1, "Instruction unandled!\n", 23);
}

// gotta implement this
void	(*chip8_cpu_exec_ins_fun[__CHIP8_INS_TOTAL])(t_chip8 *cpu, uint8_t *u8_memptr) = {
	[0x0]	= &chip8_cpu_exec_ins_fun__extend_00XX,
	[0x1]	= &chip8_cpu_exec_ins_jmp,
	[0x2]	= &chip8_cpu_exec_ins_unhandled,
	[0x3]	= &chip8_cpu_exec_ins_unhandled,
	[0x4]	= &chip8_cpu_exec_ins_unhandled,
	[0x5]	= &chip8_cpu_exec_ins_unhandled,
	[0x6]	= &chip8_cpu_exec_ins_unhandled,
	[0x7]	= &chip8_cpu_exec_ins_unhandled,
	[0x8]	= &chip8_cpu_exec_ins_fun__extend_800X,
	[0x9]	= &chip8_cpu_exec_ins_fun__extend_900X,
	[0xa]	= &chip8_cpu_exec_ins_unhandled,
	[0xb]	= &chip8_cpu_exec_ins_unhandled,
	[0xc]	= &chip8_cpu_exec_ins_unhandled,
	[0xd]	= &chip8_cpu_exec_ins_unhandled,
	[0xe]	= &chip8_cpu_exec_ins_unhandled,
	[0xf]	= &chip8_cpu_exec_ins_fun__extend_F0XX
};

void	chip8_cpu_loop(t_chip8 *cpu){
	uint8_t	*u8_memptr;
	uint8_t	u8_opcode;

	while (cpu->pc < cpu->size + CHIP8_SECTOR_START_PROG){
		u8_memptr = &cpu->mem[cpu->pc];			// fetch
		u8_opcode = chip8_ins_get_opcode(u8_memptr);	// decode
		chip8_cpu_exec_ins_fun[u8_opcode](cpu, u8_memptr);	// execute
		cpu->pc += 2;					// next
	}
}

int	main(int ac, char *av[]){
	if (ac == 2){
		t_chip8 cpu;

		write(1, "\n== chip8 CPU initializing...	   ==\n", 33);
		chip8_cpu_setup(&cpu);

		write(1, "\n== chip8 loading program...		   ==\n", 33);
		cpu.size = chip8_load_program(av[1], &cpu.mem);

		write(1, "\n== chip8 emulation starting. Have fun! ==\n", 45);
		chip8_cpu_loop(&cpu);

		write(1, "\n== chip8 emulation terminated. See ya! ==", 43);
	}
	else
		write(1, "usage: ./chip8_dissasemble [path_to_file]", 43);
	write(1, "\n", 1);
	return (0);
}
