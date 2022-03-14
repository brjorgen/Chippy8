#include "../../includes/chip8.h"
#include <stdbool.h>
#include <strings.h>
#include <stdlib.h>

void		chip8_stack_init(t_chip8 *cpu){
	cpu->sp = CHIP8_SECTOR_START_STACK;
	bzero(cpu->stack, sizeof(uint16_t) * CHIP8_STACK_SIZE);
}

void	        chip8_stack_push(t_chip8 *cpu, uint16_t addr){
	cpu->sp++;
	cpu->stack[cpu->sp] = addr;
}

uint16_t	chip8_stack_pop(t_chip8	*cpu){
	cpu->sp--;
	return (cpu->stack[cpu->sp + 1]);
}

uint16_t	chip8_stack_peek(t_chip8 *cpu){
	return (cpu->stack[cpu->sp]);
}

bool		chip8_stack_empty(t_chip8 *cpu){
	return (cpu->sp == 0);
}
