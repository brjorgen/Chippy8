#include "../../includes/chip8.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

# ifndef DEBUG
bool	in_array(int a, int *b, size_t s){
	size_t i = 0;
	while (i < s){
		if (a == b[i])
			return (true);
		i++;
	}
	return (false);
}
# endif

char *chip8_dissasembler_mnem_strings[__CHIP8_INS_TOTAL] = {
	[0x1] = "JMP	NNN",
	[0x2] = "CALL	NNN",
	[0x3] = "SKPE	VX, NN",
	[0x4] = "SKPN	VX, NN",
	[0x5] = "SKPEXY VX, VY",
	[0x6] = "MOV	NN, VX",
	[0x7] = "ADD	VX, NN",
	[0x9] = "SNE	VX, NN",
	[0xa] = "LD	%02x, I",
	[0xb] = "JMP	%02x + %02x,",
	[0xc] = "RND	%02x, V%02x",
	[0xd] = "DRAW	X%02x, Y%02x, N%02x",
	[0xe] = "SKPK	VX",
	[0xf] = "(& 0xf) (LD DELAY, VR), etc.."
};

char	*chip8_get_mnem_str(uint8_t u8_opcode, uint16_t u16_ins){
	int subgroups[2] = {0x0, 0x8};

	if (in_array(u8_opcode, &subgroups[0], 3)){
		switch (u8_opcode){
		case 0x0: {
			uint16_t rest;
			rest = chip8_ins_get_lo2_nib(u16_ins);

			char	*__00XX_strings[0xee + 1] = {
				[CHIP8_INS_NOP] = "NO OP",
				[CHIP8_INS_CLS] = "CLS",
				[CHIP8_INS_RET] = "RET",
			};

			if (in_array(rest, (int [3]){0x00, 0xe0, 0xee}, 3)){
				return (__00XX_strings[rest]);
			}
			else {
				return("JMP NNN");
			}
		}
		case 0x8: {
			uint16_t rest;
			rest = chip8_ins_get_lo_nib(u16_ins);

			uint16_t flag = (u8_opcode * 0x1000) | rest;

			char *__800N_strings[CHIP8_INS_MOV_MSB_VX_VY_SHIFTL1_VX + 1] = {
				[CHIP8_INS_MOV_VY_VX] = "MOV VY VX",
				[CHIP8_INS_OR_VX_VY]  = "OR VX VY",
				[CHIP8_INS_AND_VX_VY] = "AND VX VY",
				[CHIP8_INS_XOR_VX_VY] = "XOR VX VY",
				[CHIP8_INS_ADD_VX_VY] = "ADD VX VY",
				[CHIP8_INS_MOV_LSB_VX_VY_SHIFTR1_VX] = "MOV LSB VX VY SHIFT-R1 VX",
				[CHIP8_INS_MOV_SUB_VY_VX_VX] = "MOV SUB VY VX VX",
				[CHIP8_INS_MOV_MSB_VX_VY_SHIFTL1_VX] = "MOV MSB VX VY SHIFT-L1 VX"
			};
			return (__800N_strings[flag]);
		};
		default:
			printf("Bullshit instruction : [%x]!\n", u16_ins);
		}
	}
	else {
		return (chip8_dissasembler_mnem_strings[u8_opcode]);
	}
	return (NULL);
}

void	chip8_dissasembler_print_ins(uint8_t	*src,
				     int	pc){
	uint8_t	*instructionptr;
	uint16_t	ins;
	uint8_t	opcode;

	instructionptr = &src[pc];
	ins = chip8_ins_get_ins(instructionptr);
	opcode = chip8_ins_get_opcode(ins);
	printf("[%03x] [%04x] (%02x - %02x)\t> %s\n",
				pc,
				chip8_ins_get_ins(instructionptr),
				instructionptr[0],
				instructionptr[1],
	       chip8_get_mnem_str(opcode, ins));
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
