#include "../../includes/chip8.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

const char *chip8_dissasembler_mnem_strings[__CHIP8_INS_TOTAL] = {
	[0x0] = "(& 0x0) NO_OP, CLS, RET",
	[0x1] = "JMP	NNN",
	[0x2] = "CALL	NNN",
	[0x3] = "SKPE	VX, NN",
	[0x4] = "SKPN	VX, NN",
	[0x5] = "SKPEXY VX, VY",
	[0x6] = "MOV	NN, VX",
	[0x7] = "ADD	VX, NN",
	[0x8] = "(& 0x8) SUBN, SHL, etc ...",
	[0x9] = "(& 0x9) SKPN, SKPE, etc...",
	[0xa] = "LD	%02x, I",
	[0xb] = "JMP	%02x + %02x,",
	[0xc] = "RND	%02x, V%02x",
	[0xd] = "DRAW	X%02x, Y%02x, N%02x",
	[0xe] = "SKPK	VX",
	[0xf] = "(& 0xf) (LD DELAY, VR), etc.."
};

void	chip8_dissasembler_print_ins(uint8_t	*src,
				     int	pc){
	uint8_t	*instructionptr;
	uint16_t	ins;
	uint8_t	opcode;

	instructionptr = &src[pc];
	ins = chip8_ins_get_ins(instructionptr);
	opcode = chip8_ins_get_opcode(ins);
	printf("[%03x] [%04x] %02x %02x %s\n",
				pc,
				chip8_ins_get_ins(instructionptr),
				instructionptr[0],
				instructionptr[1],
				chip8_dissasembler_mnem_strings[opcode]);
}

void	chip8_dissasemble(char *filename){
	uint8_t	*source_buffer;
	unsigned	pc;
	size_t		size;

	pc = 0x200;
	size = chip8_load_program(filename, &source_buffer);
	while (pc < size + CHIP8_SECTOR_START_PROG){
		chip8_dissasembler_print_ins(source_buffer, pc);
		pc += 2;
	}
	free(source_buffer);
}

#ifndef DEBUG
int	main(int ac, char *av[]){
	if (ac == 2){
		chip8_dissasemble(av[1]);
	}
	else {
		printf("usage: ./chip8_disassembler [path_to_file]\n");
	}
	return (0);
}
#endif
