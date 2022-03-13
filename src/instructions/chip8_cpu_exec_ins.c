#include "../../includes/chip8.h"
#include <stdio.h>
#include <stdlib.h>

void	chip8_cpu_exec_ins_unhandled(t_chip8 *cpu, uint16_t u16_ins){
	(void)cpu;
	(void)u16_ins;
	write(1, "Instruction unandled!\n", 22);
	return ;
}

void	chip8_cpu_exec_ins_cls(t_chip8 *cpu, uint16_t u16_ins){
	(void)u16_ins;
	printf("Screen cleared!");

	int i = -1;
	while (++i < CHIP8_SECTOR_SIZE_VID_MEM - 1)
		cpu->display[i] = ' '; // lol wtf 
}

void	chip8_cpu_exec_ins_ret(t_chip8 *cpu, uint16_t u16_ins){ // this doesn't work at all
	(void)u16_ins;
	printf("wowie\n");
	cpu->pc = cpu->stack[cpu->sp]; // segv!
	printf("wowieeee\n");
	cpu->sp--;
}

void	chip8_cpu_exec_ins_call_nnn(t_chip8 *cpu, uint16_t u16_ins){
	uint16_t	addr;

	addr = chip8_ins_get_lo3_nib(u16_ins);
	printf(">> %x\n", addr);
	chip8_stack_push(cpu, addr); // segv
	printf("%x\n", addr);
	cpu->pc = addr;
}

void	chip8_cpu_exec_ins_NOP(t_chip8 *cpu, uint16_t u16_ins){
	(void)cpu;
	(void)u16_ins;
	return ;
}

void	chip8_cpu_exec_ins_jmp_nnn(t_chip8 *cpu, uint16_t u16_ins){ // done. works/
	uint16_t	addr;

	addr = chip8_ins_get_lo3_nib(u16_ins); // get lo3
	/* printf("jumping to %x\n", addr); */
	cpu->pc = addr - 2;
	/* printf("%x\n", cpu->pc); */
}

void	chip8_cpu_exec_ins_draw(t_chip8 *cpu, uint16_t u16_ins){ // done.	
	unsigned short x = cpu->registers.V[(u16_ins & 0x0F00) >> 8];
	unsigned short y = cpu->registers.V[(u16_ins & 0x00F0) >> 4];
	unsigned short height = u16_ins & 0x000F;
	unsigned short pixel;
 
	cpu->registers.V[0xF] = 0;
	for (int yline = 0; yline < height; yline++){
		pixel = cpu->mem[cpu->registers.I + yline];

		for(int xline = 0; xline < 8; xline++){
			if((pixel & (0x80 >> xline)) != 0){
				/* if(cpu->mem[CHIP8_SECTOR_START_VID_MEM + (x + xline + ((y + yline) * 64))] == 1) */
				/* 	cpu->registers.V[0xF] = 1; */
				cpu->mem[CHIP8_SECTOR_START_VID_MEM +
					 (x + xline + ((y + yline) * 64))] ^= 1;
			}
		}
		cpu->drawn = true;
	}
}

void	chip8_cpu_exec_ins_skp_kp(t_chip8 *cpu, uint16_t u16_ins){ // wip
	(void)cpu;
	(void)u16_ins;
	
	write(1, "kp not handled!\n", 16);
	return ;
}

void	chip8_cpu_exec_ins_ld_nnn_I(t_chip8 *cpu, uint16_t u16_ins){ // done. works/
	uint16_t	addr;

	addr = chip8_ins_get_lo3_nib(u16_ins); // get lo3
	cpu->registers.I = addr;
}

void	chip8_cpu_exec_ins_jmp_v0_add_nnn(t_chip8 *cpu, uint16_t u16_ins){ // done. works/
	uint16_t	addr;

	addr = chip8_ins_get_lo3_nib(u16_ins); // get lo3
	cpu->pc = cpu->registers.V[0] + addr;
}

void	chip8_cpu_exec_ins_skpe_vx_nnn(t_chip8 *cpu, uint16_t u16_ins){
	if (cpu->registers.V[chip8_ins_get_scnd_nib(u16_ins)] == chip8_ins_get_lo2_nib(u16_ins))
		cpu->pc+=2;
}

void	chip8_cpu_exec_ins_skpn_vx_nnn(t_chip8 *cpu, uint16_t u16_ins){
	if (cpu->registers.V[chip8_ins_get_scnd_nib(u16_ins)] != chip8_ins_get_lo2_nib(u16_ins))
		cpu->pc+=2;
}

void	chip8_cpu_exec_ins_skpe_vx_vy(t_chip8 *cpu, uint16_t u16_ins){
	if (cpu->registers.V[u16_ins & 0x0FF] == cpu->registers.V[chip8_ins_get_lo2_nib(u16_ins)])
		cpu->pc+=2;
}

void	chip8_cpu_exec_ins_ld_nnn_i(t_chip8 *cpu, uint16_t u16_ins){
	cpu->registers.I = chip8_ins_get_lo3_nib(u16_ins);
}

void	chip8_cpu_exec_ins_ld_nnn_vx(t_chip8 *cpu, uint16_t u16_ins){
	cpu->registers.V[chip8_ins_get_scnd_nib(u16_ins)] = chip8_ins_get_lo2_nib(u16_ins);
}

void	chip8_cpu_exec_ins_add_vx_nnn(t_chip8 *cpu, uint16_t u16_ins){
	cpu->registers.V[chip8_ins_get_scnd_nib(u16_ins)] += chip8_ins_get_lo2_nib(u16_ins);
}

void	chip8_cpu_exec_ins_ld_vx_vy(t_chip8 *cpu, uint16_t u16_ins){
	cpu->registers.V[chip8_ins_get_scnd_nib(u16_ins)] += cpu->registers.V[chip8_ins_get_lo2_nib(u16_ins)];
}

void	chip8_cpu_exec_ins_mov_vy_vx(t_chip8 *cpu, uint16_t u16_ins){
	cpu->registers.V[chip8_ins_get_scnd_nib(u16_ins)] = cpu->registers.V[chip8_ins_get_lo2_nib(u16_ins)];
}

void	chip8_cpu_exec_ins_or_vy_vx(t_chip8 *cpu, uint16_t u16_ins){
	cpu->registers.V[chip8_ins_get_scnd_nib(u16_ins)] |= cpu->registers.V[chip8_ins_get_lo2_nib(u16_ins)];
}

void	chip8_cpu_exec_ins_and_vy_vx(t_chip8 *cpu, uint16_t u16_ins){
	cpu->registers.V[chip8_ins_get_scnd_nib(u16_ins)] &= cpu->registers.V[chip8_ins_get_lo2_nib(u16_ins)];
}

void	chip8_cpu_exec_ins_xor_vy_vx(t_chip8 *cpu, uint16_t u16_ins){
	cpu->registers.V[chip8_ins_get_scnd_nib(u16_ins)] ^= cpu->registers.V[chip8_ins_get_lo2_nib(u16_ins)];
}

void	chip8_cpu_exec_ins_add_vy_vx(t_chip8 *cpu, uint16_t u16_ins){
	cpu->registers.V[chip8_ins_get_scnd_nib(u16_ins)] += cpu->registers.V[chip8_ins_get_lo2_nib(u16_ins)];
}

void	chip8_cpu_exec_ins_sub_vy_vx(t_chip8 *cpu, uint16_t u16_ins){
	cpu->registers.V[chip8_ins_get_scnd_nib(u16_ins)] -= cpu->registers.V[chip8_ins_get_lo2_nib(u16_ins)];
}

void	chip8_cpu_exec_ins_movlsb_vx_vy_shiftr1_vx(t_chip8 *cpu, uint16_t u16_ins){ // not sure about this one
	cpu->registers.V[chip8_ins_get_scnd_nib(u16_ins)] =
		(cpu->registers.V[chip8_ins_get_scnd_nib(u16_ins)] >> 1)
		| chip8_ins_get_lo_nib(cpu->registers.V[chip8_ins_get_lo2_nib(u16_ins)]) << 4;
}

void	chip8_cpu_exec_ins_ld_vx_dt(t_chip8 *cpu, uint16_t u16_ins){
	uint16_t reg;

	reg = chip8_ins_get_scnd_nib(u16_ins);
	cpu->registers.V[reg] = cpu->timers.delay;
}

void	chip8_cpu_exec_ins_ld_dt_vx(t_chip8 *cpu, uint16_t u16_ins){
	uint16_t reg;

	reg = chip8_ins_get_scnd_nib(u16_ins);
	cpu->registers.V[reg] = cpu->timers.delay;
}

void	chip8_cpu_exec_ins_ld_st_vx(t_chip8 *cpu, uint16_t u16_ins){
	uint16_t reg;

	reg = chip8_ins_get_scnd_nib(u16_ins);
	cpu->timers.sound = cpu->registers.V[reg];
}

void	chip8_cpu_exec_ins_ld_add_vx_I(t_chip8 *cpu, uint16_t u16_ins){
	uint16_t reg;

	reg = chip8_ins_get_scnd_nib(u16_ins);
	cpu->registers.I += cpu->registers.V[reg];
}

void	chip8_cpu_exec_ins_rnd(t_chip8 *cpu, uint16_t u16_ins){
	uint16_t u8_Vx_reg = chip8_ins_get_scnd_nib(u16_ins);
	cpu->registers.V[u8_Vx_reg] = rand() & chip8_ins_get_lo2_nib(u16_ins);
}

void	chip8_cpu_exec_ins_sne(t_chip8 *cpu, uint16_t u16_ins){
	uint16_t x = chip8_ins_get_scnd_nib(u16_ins);
	uint16_t y = chip8_ins_get_thrd_nib(u16_ins);

	if (cpu->registers.V[x] == cpu->registers.V[y])
		cpu->pc += 2;
}
