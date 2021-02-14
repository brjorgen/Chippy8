#include "../includes/chip8.h"

void	chip8_cpu_exec_ins_fun__extend_00XX(t_chip8 *cpu, uint8_t *u8_memptr){
	uint16_t rest;

	rest = (u8_memptr[1] & 0xFF);
	void (*__00XX_functions[0xff])(t_chip8 *cpu, uint8_t *u8_memptr) = {
		[0x00] = &chip8_cpu_exec_ins_unhandled,
		[0xe0] = &chip8_cpu_exec_ins_unhandled,
		[0xee] = &chip8_cpu_exec_ins_unhandled,
	};

	__00XX_functions[rest](cpu, u8_memptr);
}

void	chip8_cpu_exec_ins_fun__extend_800X(t_chip8 *cpu, uint8_t *u8_memptr){
	uint8_t rest;

	rest = (u8_memptr[1] & 0x0F);
	void (*__800X_functions[0x10])(t_chip8 *cpu, uint8_t *u8_memptr) = {
		[0x01] = &chip8_cpu_exec_ins_unhandled,
		[0x02] = &chip8_cpu_exec_ins_unhandled,
		[0x03] = &chip8_cpu_exec_ins_unhandled,
		[0x04] = &chip8_cpu_exec_ins_unhandled,
		[0x05] = &chip8_cpu_exec_ins_unhandled,
		[0x06] = &chip8_cpu_exec_ins_unhandled,
		[0x07] = &chip8_cpu_exec_ins_unhandled,
		[0x0e] = &chip8_cpu_exec_ins_unhandled,
	};

	__800X_functions[rest](cpu, u8_memptr);
}

void	chip8_cpu_exec_ins_fun__extend_900X(t_chip8 *cpu, uint8_t *u8_memptr){
	uint8_t rest;

//	rest = ((u8_memptr[0] & 0x0F) | (u8_memptr[1] & 0x0F));
	rest = (u8_memptr[1] & 0x0F);
	void (*__900X_functions[0x10])(t_chip8 *cpu, uint8_t *u8_memptr) = {
		[0x01] = &chip8_cpu_exec_ins_unhandled,
		[0x02] = &chip8_cpu_exec_ins_unhandled,
		[0x03] = &chip8_cpu_exec_ins_unhandled,
		[0x04] = &chip8_cpu_exec_ins_unhandled,
		[0x05] = &chip8_cpu_exec_ins_unhandled,
		[0x06] = &chip8_cpu_exec_ins_unhandled,
		[0x07] = &chip8_cpu_exec_ins_unhandled,
	};
 
	__900X_functions[rest](cpu, u8_memptr);
}

void	chip8_cpu_exec_ins_fun__extend_F0XX(t_chip8 *cpu, uint8_t *u8_memptr){
	uint8_t rest;

	rest = (u8_memptr[1] & 0x0F);
	void (*__F0XX_functions[0x66])(t_chip8 *cpu, uint8_t *u8_memptr) = {
		[0x07] = &chip8_cpu_exec_ins_unhandled,
		[0x0a] = &chip8_cpu_exec_ins_unhandled,
		[0x15] = &chip8_cpu_exec_ins_unhandled,
		[0x18] = &chip8_cpu_exec_ins_unhandled,
 		[0x1e] = &chip8_cpu_exec_ins_unhandled,
		[0x29] = &chip8_cpu_exec_ins_unhandled,
		[0x33] = &chip8_cpu_exec_ins_unhandled,
		[0x55] = &chip8_cpu_exec_ins_unhandled,
		[0x65] = &chip8_cpu_exec_ins_unhandled,
	};
 
	__F0XX_functions[rest](cpu, u8_memptr);
}
