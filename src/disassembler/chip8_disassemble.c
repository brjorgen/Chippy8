#include "../../includes/chip8.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

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
	[0x1] = "JMP	%d", 		// nnn
	[0x2] = "CALL	%d", 		// nnn
	[0x3] = "SKPE	V%d, %d",	// vx, nn
	[0x4] = "SKPN	V%d, %d",
	[0x5] = "SKPEXY V%d, V%d", 	/* [0x5] = "SKPEXY VX, VY", */
	[0x6] = "MOV	%d, V%d", // 	[0x6] = "MOV	NN, VX",
	[0x7] = "ADD	V%d, %d", // 	[0x7] = "ADD	VX, NN",
	[0x9] = "SNE	V%d, %d", // 	[0x9] = "SNE	VX, NN",
	[0xa] = "LD	%d, I", // 	[0xa] = "LD	%02x, I",
	[0xb] = "JMP	%d + %d,", // 	[0xb] = "JMP	%02x + %02x,",
	[0xc] = "RND	%d, V%d", // 	[0xc] = "RND	%02x, V%02x",
	[0xd] = "DRAW	X%d, Y%d, N%d", // 	[0xd] = "DRAW	X%02x, Y%02x, N%02x",
	[0xe] = "SKPK	V%d", // 	[0xe] = "SKPK	VX",
	[0xf] = "(& 0xf) (LD DELAY, VR), etc.." // 	[0xf] = "(& 0xf) (LD DELAY, VR), etc.."
};

char	*__00XX_strings[0xee + 1] = {
	[CHIP8_INS_NOP] = "NO OP",
	[CHIP8_INS_CLS] = "CLS",
	[CHIP8_INS_RET] = "RET",
};

char *__800N_strings[CHIP8_INS_MOV_MSB_VX_VY_SHIFTL1_VX + 1] = {
	[CHIP8_INS_MOV_VY_VX] = "MOV V%d V%d", // 	[CHIP8_INS_MOV_VY_VX] = "MOV VY VX",
	[CHIP8_INS_OR_VX_VY]  = "OR  V%d V%d", // 	[CHIP8_INS_OR_VX_VY]  = "OR VX VY",
	[CHIP8_INS_AND_VX_VY] = "AND V%d V%d", // 	[CHIP8_INS_AND_VX_VY] = "AND VX VY",
	[CHIP8_INS_XOR_VX_VY] = "XOR V%d V%d", // 	[CHIP8_INS_XOR_VX_VY] = "XOR VX VY",
	[CHIP8_INS_ADD_VX_VY] = "ADD V%d V%d", // 	[CHIP8_INS_ADD_VX_VY] = "ADD VX VY",
	[CHIP8_INS_MOV_LSB_VX_VY_SHIFTR1_VX] = "SETYSHRX V%d V%d", // 	[CHIP8_INS_MOV_LSB_VX_VY_SHIFTR1_VX] = "MOV LSB VX VY SHIFT-R1 VX",
	[CHIP8_INS_MOV_SUB_VY_VX_VX] = "MOVSUB VY VX VX", // 	[CHIP8_INS_MOV_SUB_VY_VX_VX] = "MOV SUB VY VX VX",
	[CHIP8_INS_MOV_MSB_VX_VY_SHIFTL1_VX] = "SETYSHLX V%d V%d" // 	[CHIP8_INS_MOV_MSB_VX_VY_SHIFTL1_VX] = "MOV MSB VX VY SHIFT-L1 VX"
};

char	*chip8_get_mnem_str(uint8_t u8_opcode, uint16_t u16_ins){
	int subgroups[2] = {0x0, 0x8}; // 'cause there are multiple instructions with these higher bits
	static char buff[80] = {0};
	memset(buff, 0, 80);
	if (in_array(u8_opcode, &subgroups[0], 3)){
		if (u8_opcode == 0x0) {
			uint16_t rest;

			rest = chip8_ins_get_lo2_nib(u16_ins);
			if (in_array(rest, (int [3]){0x00, 0xe0, 0xee}, 3)){
				return (__00XX_strings[rest]);
			}
			else {
				return("CALL NNN");
			}
		}
	}
	else {
		char *fmt_string = chip8_dissasembler_mnem_strings[u8_opcode];

		switch (u8_opcode){
		case	CHIP8_INS_JMP:
		case 	CHIP8_INS_CALL:
			snprintf(buff, 80, fmt_string, chip8_ins_get_lo3_nib(u16_ins));
			break;

		case 	CHIP8_INS_SKIP_EQ_VX_NN:
		case 	CHIP8_INS_SKIP_NEQ_VX_NN:
		case 	CHIP8_INS_ADD_VX_NN:
			snprintf(buff, 80, fmt_string,
				 chip8_ins_get_scnd_nib(u16_ins),
				 u16_ins & 0xFFu);
			break;
 
		case    CHIP8_INS_SKIP_NEQ_VX_VY:
		case 	CHIP8_INS_SKIP_EQ_VX_VY:
			snprintf(buff, 80, fmt_string,
				 chip8_ins_get_scnd_nib(u16_ins),
				 chip8_ins_get_hi_nib(u16_ins & 0xF000u));
			break;

		case 	CHIP8_INS_MOV_NN_VX:
			snprintf(buff, 80, fmt_string,
				 u16_ins & 0xFFu,
				 chip8_ins_get_scnd_nib(u16_ins));
			break;

		case 0x8: {
			uint16_t rest;
			uint16_t flag;

			rest = chip8_ins_get_lo_nib(u16_ins);
			flag = (u8_opcode * 0x1000) | rest;
			fmt_string = __800N_strings[flag];

			/* vx first */
			if ((u16_ins & 0x00FF) != 0x00)
				snprintf(buff, 80, fmt_string,
					 chip8_ins_get_scnd_nib(u16_ins),
					 chip8_ins_get_thrd_nib(u16_ins));
			else
				snprintf(buff, 80, fmt_string,
					 chip8_ins_get_thrd_nib(u16_ins),
					 chip8_ins_get_scnd_nib(u16_ins));
		}
			break;
		case	CHIP8_INS_SET_MOV_NNN_I:
		case 	CHIP8_INS_JMP_ADD_NNN_V0:
		case	CHIP8_INS_MOV_RAND_AND_NN_VX:
			snprintf(buff, 80, fmt_string,
				 chip8_ins_get_lo3_nib(u16_ins),
				 chip8_ins_get_scnd_nib(u16_ins));
			break;

		case CHIP8_INS_DRAW_XY:
			snprintf(buff, 80, fmt_string,
				 chip8_ins_get_scnd_nib(u16_ins),
				 chip8_ins_get_thrd_nib(u16_ins),
				 chip8_ins_get_lo_nib(u16_ins));
			break;
		case CHIP8_INS_SKPK_VX:
			break;

		case 	0xF:{
			strcpy(buff, chip8_dissasembler_mnem_strings[0x0f]);
			/* switch (chip8_ins_get_lo3_nib(u16_ins)){ */
			/* case	CHIP8_INS_LD_DELAY_TIMER_VR & 0x0FFF: // 0xf007 */
			/* 	break;				      // 0xf00a */
			/* case	CHIP8_INS_WAKP_LD_VR & 0x0FFF:	      // 0xf015 */
			/* 	break; */
			/* case 	CHIP8_INS_TIMER_SET_DELAY_VR & 0x0FFF: */
			/* 	break; */
			/* case 	CHIP8_INS_TIMER_SET_SOUND_VR & 0x0FFF: */
			/* 	break; */
			/* case 	CHIP8_INS_ADD_I_VR & 0x0FFF: */
			/* 	break; */
			/* case CHIP8_INS_SET_I_FNT_VR  & 0x0FFF: */
			/* 	break; */
			/* case CHIP8_INS_LD_B_VR  & 0x0FFF: */
			/* 	break; */
			/* case CHIP8_INS_LD_I_VR  & 0x0FFF: */
			/* 	break; */
			/* case CHIP8_INS_LD_VR_I  & 0x0FFF: */
			/* 	break; */
			}
			break;
		}
	}
	return (&buff[0]);
}

void	chip8_dissasembler_print_ins(uint8_t	*src,
				     int	pc){
	uint8_t		*instructionptr;
	uint16_t	ins;
	uint8_t		opcode;

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
	uint8_t		*source_buffer;
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
