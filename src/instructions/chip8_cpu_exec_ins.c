#include "../../includes/chip8.h"
#include <stdio.h>

void	chip8_cpu_exec_ins_unhandled(t_chip8 *cpu,
				     uint8_t *u8_memptr){
	(void)cpu;
	(void)u8_memptr;
	write(1, "Instruction unandled!\n", 22);
	return ;
}

/* void	chip8_cpu_exec_ins_call(t_chip8 *cpu, uint8_t *u8_memptr){ */
/* } */

/* void	chip8_cpu_exec_ins_cls(t_chip8 *cpu, uint8_t *u8_memptr){ */
/* } */

/* void	chip8_cpu_exec_ins_ret(t_chip8 *cpu, uint8_t *u8_memptr){ */
/* 	(void)u8_memptr; */
/* 	cpu->pc = cpu->stack[cpu->sp]; */
/* 	cpu->sp--; */
/* } */

void	chip8_cpu_exec_ins_jmp_nnn(t_chip8 *cpu, uint8_t *u8_memptr){
	uint16_t	instruction;
	uint8_t		addr;

	instruction = chip8_ins_get_ins(u8_memptr);
	addr = chip8_ins_get_lo3_nib(instruction); // get lo3
	cpu->pc = addr;
}

void	chip8_cpu_exec_ins_skpe_vx_nnn(t_chip8 *cpu, uint8_t *u8_memptr){
	uint16_t ins;

	ins = chip8_ins_get_ins(u8_memptr);
	if (cpu->registers.V[chip8_ins_get_scnd_nib(u8_memptr)] == chip8_ins_get_lo3_nib(ins)){
		cpu->pc+=2;
	}
}

void	chip8_cpu_exec_ins_skpn_vx_nnn(t_chip8 *cpu, uint8_t *u8_memptr){
	uint16_t ins;

	ins = chip8_ins_get_ins(u8_memptr);
	if (cpu->registers.V[chip8_ins_get_scnd_nib(u8_memptr)] != chip8_ins_get_lo3_nib(ins)){
		cpu->pc+=2;
	}
}

void	chip8_cpu_exec_ins_skpe_vx_vy(t_chip8 *cpu, uint8_t *u8_memptr){
	uint16_t ins;

	ins = chip8_ins_get_ins(u8_memptr);
	if (cpu->registers.V[ins & 0x0FF] == chip8_ins_get_lo3_nib(ins & 0x00FF)){
		cpu->pc+=2;
	}
}

void	chip8_cpu_exec_ins_ld_nnn_i(t_chip8 *cpu, uint8_t *u8_memptr){
	uint16_t ins;

	ins = chip8_ins_get_ins(u8_memptr);
	cpu->registers.I = chip8_ins_get_lo3_nib(ins);
}

void	chip8_cpu_exec_ins_NOP(t_chip8 *cpu, uint8_t *u8_memptr){
	(void)cpu;
	(void)u8_memptr;
	return ;
}

void	chip8_cpu_exec_ins_ld_nnn_vx(t_chip8 *cpu, uint8_t *u8_memptr){
	uint16_t ins;

	ins = chip8_ins_get_ins(u8_memptr);
	cpu->registers.V[chip8_ins_get_scnd_nib(u8_memptr)] = chip8_ins_get_lo3_nib(ins);
}

void	chip8_cpu_exec_ins_add_vx_nnn(t_chip8 *cpu, uint8_t *u8_memptr){
	uint16_t ins;

	ins = chip8_ins_get_ins(u8_memptr);
	cpu->registers.V[chip8_ins_get_scnd_nib(u8_memptr)] += chip8_ins_get_lo3_nib(ins);
}

void	chip8_cpu_exec_ins_ld_vx_vy(t_chip8 *cpu, uint8_t *u8_memptr){
	uint16_t ins;

	ins = chip8_ins_get_ins(u8_memptr);
	cpu->registers.V[chip8_ins_get_scnd_nib(u8_memptr)] += cpu->registers.V[chip8_ins_get_lo2_nib(ins)];
}

void	chip8_cpu_exec_ins_mov_vy_vx(t_chip8 *cpu, uint8_t *u8_memptr){
	uint16_t ins;

	ins = chip8_ins_get_ins(u8_memptr);
	cpu->registers.V[chip8_ins_get_scnd_nib(u8_memptr)] = cpu->registers.V[chip8_ins_get_lo2_nib(ins)];
}

void	chip8_cpu_exec_ins_or_vy_vx(t_chip8 *cpu, uint8_t *u8_memptr){
	uint16_t ins;

	ins = chip8_ins_get_ins(u8_memptr);
	cpu->registers.V[chip8_ins_get_scnd_nib(u8_memptr)] |= cpu->registers.V[chip8_ins_get_lo2_nib(ins)];
}

void	chip8_cpu_exec_ins_and_vy_vx(t_chip8 *cpu, uint8_t *u8_memptr){
	uint16_t ins;

	ins = chip8_ins_get_ins(u8_memptr);
	cpu->registers.V[chip8_ins_get_scnd_nib(u8_memptr)] |= cpu->registers.V[chip8_ins_get_lo2_nib(ins)];
}


void	chip8_cpu_exec_ins_xor_vy_vx(t_chip8 *cpu, uint8_t *u8_memptr){
	uint16_t ins;

	ins = chip8_ins_get_ins(u8_memptr);
	cpu->registers.V[chip8_ins_get_scnd_nib(u8_memptr)] ^= cpu->registers.V[chip8_ins_get_lo2_nib(ins)];
}


void	chip8_cpu_exec_ins_add_vy_vx(t_chip8 *cpu, uint8_t *u8_memptr){
	uint16_t ins;

	ins = chip8_ins_get_ins(u8_memptr);
	cpu->registers.V[chip8_ins_get_scnd_nib(u8_memptr)] += cpu->registers.V[chip8_ins_get_lo2_nib(ins)];
}

void	chip8_cpu_exec_ins_sub_vy_vx(t_chip8 *cpu, uint8_t *u8_memptr){
	uint16_t ins;

	ins = chip8_ins_get_ins(u8_memptr);
	cpu->registers.V[chip8_ins_get_scnd_nib(u8_memptr)] -= cpu->registers.V[chip8_ins_get_lo2_nib(ins)];
}

void	chip8_cpu_exec_ins_movlsb_vx_vy_shiftr1_vx(t_chip8 *cpu, uint8_t *u8_memptr){
	uint16_t ins;

	ins = chip8_ins_get_ins(u8_memptr);
	cpu->registers.V[chip8_ins_get_scnd_nib(u8_memptr)] -= cpu->registers.V[chip8_ins_get_lo2_nib(ins)];
}
