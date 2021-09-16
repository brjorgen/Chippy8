#include "../../includes/chip8.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define FONTSET_SIZE 85

const unsigned char fontset[FONTSET_SIZE] = {
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
	int i;
	for (i = 0; i < FONTSET_SIZE; i++) {
		ch8->mem[i] = fontset[i];
	}
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
	chip8->mem = (uint8_t *)malloc(sizeof(uint8_t) * 4096);
	chip8->registers.V = (uint8_t *)malloc(sizeof(uint8_t) * 16);
	if (!chip8->mem || !chip8->registers.V)
		exit(EXIT_FAILURE);
	bzero(chip8->mem, sizeof(uint8_t) * 4096);
	bzero(chip8->registers.V, sizeof(uint8_t) * 16);
	chip8_load_fontset(chip8);
	chip8->registers.I = 0;
	chip8->pc = CHIP8_SECTOR_START_PROG;
	chip8->sp = CHIP8_SECTOR_START_STACK;
	chip8->display = &chip8->mem[CHIP8_SECTOR_START_VID_MEM];
}
