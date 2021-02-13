#include "../../includes/chip8.h"
#include <stdio.h>

const char *chip8_dissasembler_mnem_strings[__CHIP8_INS_TOTAL] = {
	[0x0] = "(& 0x0) NO_OP, CLS, RET",
	[0x1] = "JMP	NNN",
	[0x2] = "CALL	NNN",
	[0x3] = "SKPE	VX, NN",
	[0x4] = "SKPN	VX, NN",
	[0x5] = "SKPEXY VX, VY",
	[0x6] = "MOV	NN, VX",
	[0x7] = "ADD	VX, NN",
	[0x8/*001*/] = "(& 0x8) SUBN, SHL, etc etc)",
	/* [0x8002] = "SUBN	V%02xx, V%02xy", */
	/* [0x8003] = "SUBN	V%02xx, V%02xy", */
	/* [0x8004] = "SUBN	V%02xx, V%02xy", */
	/* [0x8005] = "SUBN	V%02xx, V%02xy", */
	/* [0x8006] = "SUBN	V%02xx, V%02xy", */
	/* [0x8007] = "SUBN	V%02xx, V%02xy", */
	/* [0x8008] = "SUBN	V%02xx, V%02xy", */
	/* [0x8006] = "SUBN	V%02xx, V%02xy", */
	/* [0x8007] = "SUBN	V%02xx, V%02xy", //yes */
	/* [0x800E] = "SHL	V%02xx, V%02xy", //yes */
//	[0x9] = "SNE	V%02xx, V%02xy",
	[0x9] = "(& 0x9) SKPN, SKPE, etc...",
	[0xa] = "LD	%02x, I",
	[0xb] = "JMP	%02x + %02x,",
	[0xc] = "RND	%02x, V%02x",
	[0xd] = "DRAW	X%02x, Y%02x, N%02x",
	[0xe] = "SKPK	VX",
	[0xf] = "(& 0xf) (LD DELAY, VR), etc.."
};

uint8_t	chip8_ins_get_lo_3(uint8_t u8_memptr) {
	return(u8_memptr & 0x0FFFF);
}

uint8_t chip8_ins_get_lo_2(uint8_t u8_memptr) {
	return (u8_memptr & 0x00FF);
}

uint8_t chip8_ins_get_lo(uint8_t u8_memptr){
	return (u8_memptr & 0x000F);
}

uint8_t	chip8_ins_get_opcode(uint8_t u8_memptr){
	return (u8_memptr & 0xF0);
}

uint8_t	(*chip8_dissasembler_mnem_args[__CHIP8_INS_TOTAL])(uint8_t instructionptr) = {
	[0x0]	= &chip8_ins_get_lo_3,
	[0x1]	= &chip8_ins_get_lo_3,
	[0x2]	= &chip8_ins_get_lo_3,
	[0x3]	= &chip8_ins_get_lo_3,
	[0x4]	= &chip8_ins_get_lo_3,
	[0x5]	= &chip8_ins_get_lo_3,
	[0x6]	= &chip8_ins_get_lo_3,
	[0x7]	= &chip8_ins_get_lo_3,
	[0x8]	= &chip8_ins_get_lo_3,
	[0x9]	= &chip8_ins_get_lo_3,
	[0xa]	= &chip8_ins_get_lo_3,
	[0xb]	= &chip8_ins_get_lo_3,
	[0xc]	= &chip8_ins_get_lo_3,
	[0xd]	= &chip8_ins_get_lo_3,
	[0xe]	= &chip8_ins_get_lo_3,
	[0xf]   = &chip8_ins_get_lo_3,
};

void	chip8_dissasembler_print_ins(uint8_t *src, int pc){
	uint8_t	*instructionptr;
//	uint8_t	instruction;
	uint8_t	opcode;

	instructionptr = &src[pc];
//	instruction =  chip8_ins_get_opcode(instructionptr[0]);
	opcode = CHIP8_GET_OPCODE(instructionptr);
	printf("[%03x] %02x %02x %s \n",
				pc,
				instructionptr[0],
				instructionptr[1],
				chip8_dissasembler_mnem_strings[opcode]
				 /* , chip8_dissasembler_mnem_args[opcode](instruction) */);
}

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 255

void	chip8_dissasemble(char *filename){
	uint8_t	*source_buffer;
	unsigned	pc;
	FILE		*file;

	file = fopen(filename, "r");
	fseek(file, 0, SEEK_END);
	unsigned size = ftell(file);
	rewind(file);
	source_buffer = (uint8_t *)malloc(sizeof(uint8_t) * size);
	fread(source_buffer + CHIP8_SECTOR_START_PROG, size, 1, file);
	fclose(file);
	pc = 0;
	while (pc < size){
		chip8_dissasembler_print_ins(&source_buffer[pc], pc);
		pc++;
	}
	free(source_buffer);
}

int	main(int ac, char *av[]){
	if (ac == 2)
		chip8_dissasemble(av[1]);
	else
		printf("usage: ./chip8_dissasemble [path_to_file]\n");
	return (0);
}
