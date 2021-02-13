#include "../../includes/chip8.h"
#include <stdlib.h>

void	chip8_setup(t_chip8 *chip8){
//	chip8->src
	chip8->mem = (uint8_t *)malloc(4096);
	chip8->pc = CHIP8_SECTOR_START_PROG;
	chip8->sp = CHIP8_SECTOR_START_STACK;
	chip8->display = &chip8->mem[0xF00];
}
