#include "../../includes/chip8.h"
#include <stdbool.h>
#include <strings.h>
#include <stdlib.h>

void			chip8_stack_init(t_chip8 *chip8){
	chip8->sp = CHIP8_SECTOR_START_STACK;
	bzero(chip8->stack, sizeof(uint16_t) * CHIP8_STACK_SIZE);
}

void		        chip8_stack_push(t_chip8 *chip8, uint16_t addr){
	chip8->sp++;
	chip8->stack[chip8->sp] = addr;
}

uint16_t		chip8_stack_pop(t_chip8	*chip8){
	chip8->sp--;
	return (chip8->stack[chip8->sp + 1]);
}

uint16_t		chip_stack_peek(t_chip8	*chip8){
	return (chip8->stack[chip8->sp]);
}

bool			chip_stack_empty(t_chip8 *chip8){
	return (chip8->sp == 0);
}
