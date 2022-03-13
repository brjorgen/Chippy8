#include "../../includes/chip8.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define FONTSET_SIZE 16 * 5

const uint8_t fontset[FONTSET_SIZE] = {
	0xF0, 0x90, 0x90, 0x90, 0xF0,		// 0
	0x20, 0x60, 0x20, 0x20, 0x70,		// 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0,		// 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0,		// 3
	0x90, 0x90, 0xF0, 0x10, 0x10,		// 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0,		// 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0,		// 6
	0xF0, 0x10, 0x20, 0x40, 0x40,		// 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0,		// 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0,		// 9
	0xF0, 0x90, 0xF0, 0x90, 0x90,		// A
	0xE0, 0x90, 0xE0, 0x90, 0xE0,		// B
	0xF0, 0x80, 0x80, 0x80, 0xF0,		// C
	0xE0, 0x90, 0x90, 0x90, 0xE0,		// D
	0xF0, 0x80, 0xF0, 0x80, 0xF0,		// E
	0xF0, 0x80, 0xF0, 0x80, 0x80		// F
};

void	chip8_load_fontset(t_chip8 *ch8){
	unsigned int i = 0;

	for (i = 0; i < FONTSET_SIZE; i++) {
		ch8->mem[i] = fontset[i];
	}
	printf("fontset loaded @ 0 to %d\n", i);
}

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
	// allocate memory map
	chip8->mem = (uint8_t *)malloc(sizeof(uint8_t) * CHIP8_MEMSIZE);
	bzero(chip8->mem, sizeof(uint8_t) * CHIP8_MEMSIZE);

	// allocate & setup registers
	chip8->registers.V = (uint8_t *)malloc(sizeof(uint8_t) * 16);
	bzero(chip8->registers.V, sizeof(uint8_t) * 16);
	if (!chip8->mem || !chip8->registers.V)
		exit(EXIT_FAILURE);
	chip8->registers.I = 0;

	chip8_load_fontset(chip8);
	chip8->pc = CHIP8_SECTOR_START_PROG;
	chip8_stack_init(chip8);
	chip8->display = &chip8->mem[CHIP8_SECTOR_START_VID_MEM];
}
