#include "../../includes/chip8.h"
#include <stdio.h>
#include <stdlib.h>

size_t	chip8_load_program(char *filename,
			   uint8_t **source_buffer_addr){
	size_t		size;
	FILE		*file;

	file = fopen(filename, "r");
	fseek(file, 0, SEEK_END);
	size = ftell(file);
	rewind(file);
	*source_buffer_addr = (uint8_t *)malloc(sizeof(uint8_t)
						* size
						+ CHIP8_SECTOR_START_PROG);
	fread(*source_buffer_addr + CHIP8_SECTOR_START_PROG, size, 1, file);
	fclose(file);
	return (size);
}

void	chip8_cpu_setup(t_chip8 *chip8){
	chip8->mem = (uint8_t *)malloc(sizeof(uint8_t) * 4096);
	if (!chip8->mem)
		exit(EXIT_FAILURE);
	chip8->pc = CHIP8_SECTOR_START_PROG;
	chip8->sp = CHIP8_SECTOR_START_STACK;
	chip8->display = &chip8->mem[CHIP8_SECTOR_START_VID_MEM];
}
