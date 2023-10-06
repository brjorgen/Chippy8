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
	printf("returning from subroutine 0x%03x to 0x%03x\n", chip8_ins_get_ins(&cpu->mem[cpu->pc]), chip8_stack_peek(cpu));
	cpu->pc = chip8_stack_pop(cpu);
	printf("... -> set pc to stack_popp'ed value 0x%03x\n", cpu->pc);
}

void	chip8_cpu_exec_ins_call_nnn(t_chip8 *cpu, uint16_t u16_ins){
	uint16_t	addr;

	addr = chip8_ins_get_lo3_nib(u16_ins);

#ifdef DEBUG	
	printf(">>> 0x%03x called from 0x%03x [ ins id: 0x%x ]\n", addr, cpu->mem[cpu->pc], cpu->pc);
#endif

	chip8_stack_push(cpu, cpu->mem[cpu->pc]);
	cpu->pc = addr;
	printf("... set pc to 0x%03x\n", addr);
}

void	chip8_cpu_exec_ins_NOP(t_chip8 *cpu, uint16_t u16_ins){
	(void)cpu;
	(void)u16_ins;
	return ;
}

void	chip8_cpu_exec_ins_jmp_nnn(t_chip8 *cpu, uint16_t u16_ins){ // done. works
	uint16_t	addr;

	addr = chip8_ins_get_lo3_nib(u16_ins); // get lo3
	cpu->pc = addr;
	#ifdef DEBUG
	printf("jumping to %x\n", addr);
	#endif

}

void	chip8_cpu_exec_ins_draw(t_chip8 *cpu, uint16_t u16_ins){
	uint8_t x = (u16_ins & 0x0F00) >> 8;
	uint8_t y = (u16_ins & 0x00F0) >> 4;
	uint8_t n = u16_ins & 0x000F;
	uint8_t pixel_row;

	cpu->registers.V[0xF] = 0;

	#ifdef DEBUG
	printf(">>> (%d, %d, %d)\n", x, y, n);
	printf("cpu->registers.V[x, y] = %d, %d\n", cpu->registers.V[x], cpu->registers.V[y]);
	#endif

	for (int yline = 0; yline < n; yline++){
		pixel_row = cpu->mem[cpu->registers.I + yline];

		for(int xline = 0; xline < 8; xline++){
			if(pixel_row & (0x80 >> xline)){
				int i = CHIP8_SECTOR_START_VID_MEM + ((cpu->registers.V[x] + xline) + ((cpu->registers.V[y] + yline) * CHIP8_VID_MEM_WIDTH));
				if(cpu->mem[i] != 0)
					cpu->registers.V[0xF] = 1;
				else
					cpu->registers.V[0xF] = 0;
				cpu->mem[i] ^= 1;
			}
		}
	}
	cpu->drawn = true;
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
	#ifdef DEBUG
	printf("addr: %d\n", addr);
	#endif
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
