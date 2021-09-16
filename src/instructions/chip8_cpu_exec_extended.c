#include "../../includes/chip8.h"

#include <assert.h>

bool	in_array(int a, int *b, size_t s){
	size_t i = 0;
	while (i < s){
		if (a == b[i])
			return (true);
		i++;
	}
	return (false);
}

void	chip8_cpu_exec_ins_fun__extend_00XX(t_chip8 *cpu, uint16_t u16_ins){
	uint16_t rest;

	rest = chip8_ins_get_lo2_nib(u16_ins);
	void (*__00XX_functions[0xff + 1])(t_chip8 *cpu, uint16_t u16_ins) = {
		[0x00] = &chip8_cpu_exec_ins_NOP,
		[0xe0] = &chip8_cpu_exec_ins_cls,
		[0xee] = &chip8_cpu_exec_ins_ret,
	};

	if (in_array(rest, (int [3]){0x00, 0xe0, 0xee}, 3)){
		__00XX_functions[rest](cpu, u16_ins);
	}
	else {
		chip8_cpu_exec_ins_jmp_nnn(cpu, u16_ins);
	}
}

void	chip8_cpu_exec_ins_fun__extend_800X(t_chip8 *cpu, uint16_t u16_ins){
	uint16_t rest;

	rest = chip8_ins_get_lo_nib(u16_ins);
	void (*__800X_functions[0x10])(t_chip8 *cpu, uint16_t u8_memptr) = {
		[0x00] = &chip8_cpu_exec_ins_mov_vy_vx,
		[0x01] = &chip8_cpu_exec_ins_unhandled,
		[0x02] = &chip8_cpu_exec_ins_unhandled,
		[0x03] = &chip8_cpu_exec_ins_unhandled,
		[0x04] = &chip8_cpu_exec_ins_unhandled,
		[0x05] = &chip8_cpu_exec_ins_unhandled,
		[0x06] = &chip8_cpu_exec_ins_unhandled,
		[0x07] = &chip8_cpu_exec_ins_unhandled,
		[0x0e] = &chip8_cpu_exec_ins_unhandled,
	};

	__800X_functions[rest](cpu, u16_ins);
}

void	chip8_cpu_exec_ins_fun__extend_900X(t_chip8 *cpu, uint16_t u16_ins){
	uint8_t rest;

	rest = chip8_ins_get_lo_nib(u16_ins);
	void (*__900X_functions[0x10])(t_chip8 *cpu, uint16_t u16_ins) = {
		[0x01] = &chip8_cpu_exec_ins_unhandled,
		[0x02] = &chip8_cpu_exec_ins_unhandled,
		[0x03] = &chip8_cpu_exec_ins_unhandled,
		[0x04] = &chip8_cpu_exec_ins_unhandled,
		[0x05] = &chip8_cpu_exec_ins_unhandled,
		[0x06] = &chip8_cpu_exec_ins_unhandled,
		[0x07] = &chip8_cpu_exec_ins_unhandled,
	};

	__900X_functions[rest](cpu, u16_ins);
}

void	chip8_cpu_exec_ins_fun__extend_EXKK(t_chip8 *cpu, uint16_t u16_ins){
	uint8_t rest;

	rest = chip8_ins_get_lo2_nib(u16_ins);
	void (*__EXKK_functions[0xa2])(t_chip8 *cpu, uint16_t u16_ins) = {
		[0x9e] = &chip8_cpu_exec_ins_unhandled,
		[0xa1] = &chip8_cpu_exec_ins_unhandled,
	};

	__EXKK_functions[rest](cpu, u16_ins);
}

void	chip8_cpu_exec_ins_fun__extend_F0XX(t_chip8 *cpu, uint16_t u16_ins){
	uint8_t rest;

	rest = chip8_ins_get_lo2_nib(u16_ins);
	void (*__F0XX_functions[0xFF + 1])(t_chip8 *cpu, uint16_t u16_ins) = {
	  [0x00] = &chip8_cpu_exec_ins_unhandled,
	  [07] = &chip8_cpu_exec_ins_ld_vx_dt,
		[0x0a] = &chip8_cpu_exec_ins_unhandled, // keyboard shit
		[15] = &chip8_cpu_exec_ins_ld_dt_vx,
		[18] = &chip8_cpu_exec_ins_ld_st_vx,
 		[0x1e] = &chip8_cpu_exec_ins_ld_add_vx_I,
		[29] = &chip8_cpu_exec_ins_unhandled,
		[33] = &chip8_cpu_exec_ins_unhandled,
		[55] = &chip8_cpu_exec_ins_unhandled,
		[65] = &chip8_cpu_exec_ins_unhandled,
		[0xFF] = &chip8_cpu_exec_ins_unhandled,
	};

	__F0XX_functions[rest](cpu, u16_ins);
}
