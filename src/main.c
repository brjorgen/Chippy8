#include "../includes/chip8.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define DEBUG

#ifdef DEBUG
# include "./disassembler/chip8_disassemble.c"
#endif

void	(*chip8_cpu_exec_ins_fun[__CHIP8_INS_TOTAL])(t_chip8 *cpu, uint16_t u16_ins) = {
	[0x0]	= &chip8_cpu_exec_ins_fun__extend_00XX,
	[0x1]	= &chip8_cpu_exec_ins_jmp_nnn,
	[0x2]	= &chip8_cpu_exec_ins_call_nnn,
	[0x3]	= &chip8_cpu_exec_ins_skpe_vx_nnn,
	[0x4]	= &chip8_cpu_exec_ins_skpn_vx_nnn,
	[0x5]	= &chip8_cpu_exec_ins_skpe_vx_vy,
	[0x6]	= &chip8_cpu_exec_ins_ld_nnn_vx,
	[0x7]	= &chip8_cpu_exec_ins_add_vx_nnn,
	[0x8]	= &chip8_cpu_exec_ins_fun__extend_800X,
	[0x9]	= &chip8_cpu_exec_ins_sne,
	[0xa]	= &chip8_cpu_exec_ins_ld_nnn_i,
	[0xb]	= &chip8_cpu_exec_ins_jmp_v0_add_nnn,
	[0xc]	= &chip8_cpu_exec_ins_rnd,
	[0xd]	= &chip8_cpu_exec_ins_draw,
	[0xe]	= &chip8_cpu_exec_ins_skp_kp,
	[0xf]	= &chip8_cpu_exec_ins_unhandled,/* chip8_cpu_exec_ins_fun__extend_F0XX */
};

void	screen_clear(t_chip8 *cpu){
	(void)cpu;
	for (int yline = 0; yline < 32; yline++){
		for(int xline = 0; xline < 64; xline++){
				printf("  ");
		}
		printf("\n");
	}
}

void	screen_render(t_chip8 *cpu){
	for (int yline = 0; yline < 32; yline++){
		for(int xline = 0; xline < 64; xline++){
			if (cpu->mem[CHIP8_SECTOR_START_VID_MEM + (xline) + (yline * 64)]){
				printf("▤ ");
			}
			else {
				printf("  ");
			}
		}
		printf("\n");
	}
}

void	chip8_cpu_loop(t_chip8 *cpu){
	uint8_t		u8_opcode;
	uint16_t	u16_ins;

	while (cpu->pc < cpu->size + CHIP8_SECTOR_START_PROG){
		u16_ins = chip8_ins_get_ins(&cpu->mem[cpu->pc]);	// fetch

		u8_opcode = chip8_ins_get_opcode(u16_ins);		// decode

		#ifdef DEBUG
		printf("[%03x] [%04x] %s\n",
		       cpu->pc,
		       u16_ins,
		       chip8_get_mnem_str(u8_opcode, u16_ins));
		#endif

		chip8_cpu_exec_ins_fun[u8_opcode](cpu, u16_ins);	// execute
		if (cpu->drawn){
			screen_clear(cpu);
			screen_render(cpu);
			cpu->drawn = false;
		}
		cpu->pc += 2;
	}
}

int	main(int ac, char *av[]){
	if (ac == 2){
		t_chip8 cpu;

		chip8_cpu_setup(&cpu);
		printf("Initialized machine ✅\n");
		cpu.size = chip8_load_program(av[1], &cpu.mem);
		printf("Program Loaded ✅\nRunning program 😎 ... \n");
		chip8_cpu_loop(&cpu);
		free(cpu.mem);
		printf("Cleaned up ✅\nSee ya!👋\n");
	}
	else
		write(1, "usage: ./chip8_emulator [path_to_rom]\n", 39);
	return (0);
}
