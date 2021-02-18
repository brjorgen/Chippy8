#include <stdint.h>

uint16_t	chip8_ins_get_ins(uint8_t *u8_memptr){
	uint16_t ins = (u8_memptr[0] << 8 | u8_memptr[1]);
	return (ins);
}

uint16_t	chip8_ins_get_scnd_nib(uint16_t u16_ins){
	return (u16_ins & 0x0F00);
}

uint16_t	chip8_ins_get_thrd_nib(uint16_t u16_ins){
	return (u16_ins & 0x00F0);
}

uint16_t	chip8_ins_get_hi2_nib(uint16_t u16_ins){
	return (u16_ins & 0xFF00);
}

uint16_t	chip8_ins_get_mid2_nibs(uint16_t u16_ins){
	return (u16_ins & 0x0FF0);
}

uint16_t	chip8_ins_get_lo2_nib(uint16_t u16_ins){
	return (u16_ins & 0x00FF);
}

uint16_t	chip8_ins_get_lo_nib(uint16_t u16_ins){
	return (u16_ins & 0x000F);
}

uint16_t	chip8_ins_get_lo3_nib(uint16_t u16_ins){
	return (u16_ins & 0x0FFF);
}

uint16_t	chip8_ins_get_opcode(uint16_t u16_ins){
	return (u16_ins >> 12);
}

/* uint16_t	chip8_ins_get_opcode(uint16_t u16_ins){ */
/* 	return (((u16_ins >> 8) & 0xF0) >> 4); */
/* } */
