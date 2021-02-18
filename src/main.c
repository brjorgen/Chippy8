#include "../includes/chip8.h"
#include <unistd.h>
#include <stdlib.h>

// gotta implement this
void	(*chip8_cpu_exec_ins_fun[__CHIP8_INS_TOTAL])(t_chip8 *cpu, uint16_t u16_ins) = {
	[0x0]	= &chip8_cpu_exec_ins_fun__extend_00XX,
	[0x1]	= &chip8_cpu_exec_ins_jmp_nnn,
	[0x2]	= &chip8_cpu_exec_ins_call_nnn, // call
	[0x3]	= &chip8_cpu_exec_ins_skpe_vx_nnn,
	[0x4]	= &chip8_cpu_exec_ins_skpn_vx_nnn,
	[0x5]	= &chip8_cpu_exec_ins_skpe_vx_vy,
	[0x6]	= &chip8_cpu_exec_ins_ld_nnn_vx,
	[0x7]	= &chip8_cpu_exec_ins_add_vx_nnn,
	[0x8]	= &chip8_cpu_exec_ins_fun__extend_800X,
	[0x9]	= &chip8_cpu_exec_ins_fun__extend_900X,
	[0xa]	= &chip8_cpu_exec_ins_ld_nnn_i,
	[0xb]	= &chip8_cpu_exec_ins_jmp_v0_add_nnn,
	[0xc]	= &chip8_cpu_exec_ins_unhandled,
	[0xd]	= &chip8_cpu_exec_ins_draw,
	[0xe]	= &chip8_cpu_exec_ins_skp_kp,
	[0xf]	= &chip8_cpu_exec_ins_fun__extend_F0XX
};

#include <stdio.h>

void	chip8_cpu_loop(t_chip8 *cpu){
	uint8_t		u8_opcode;
	uint16_t	u16_ins;

	while (cpu->pc < cpu->size + CHIP8_SECTOR_START_PROG){
//		printf("[%d] ", cpu->mem[cpu->pc]);
		u16_ins = chip8_ins_get_ins(&cpu->mem[cpu->pc]);	// fetch & decode
		u8_opcode = chip8_ins_get_opcode(u16_ins);		// get opcode
		chip8_cpu_exec_ins_fun[u8_opcode](cpu, u16_ins);	// execute
		cpu->pc += 2;						// next
	}
}

int	main(int ac, char *av[]){
	if (ac == 2){
		t_chip8 cpu;

		chip8_cpu_setup(&cpu);
		cpu.size = chip8_load_program(av[1], &cpu.mem);
		chip8_cpu_loop(&cpu);
		free(cpu.mem);
	}
	else
		write(1, "usage: ./chip8_emu.bin [path_to_file]", 37);
	write(1, "\n", 1);
	return (0);
}
