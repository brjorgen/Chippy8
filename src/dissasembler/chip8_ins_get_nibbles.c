#include <stdint.h>

uint8_t	chip8_ins_get_scnd_nib(uint8_t *u8_memptr){
	return (u8_memptr[0] & 0x0F);
}

uint8_t	chip8_ins_get_thrd_nib(uint8_t *u8_memptr){
	return (u8_memptr[1] & 0xF0);
}

uint8_t	chip8_ins_get_hi2_nib(uint8_t *u8_memptr){
	return (u8_memptr[0] & 0xFF);
}

uint8_t	chip8_ins_get_lo2_nib(uint8_t *u8_memptr){
	return (u8_memptr[1] & 0xFF);
}

uint8_t	chip8_ins_get_opcode(uint8_t *u8_memptr){
	return (u8_memptr[0] >> 4); 	// return (u8_memptr[1] & 0xF);
}

uint16_t	chip8_ins_get_ins(uint8_t *u8_memptr){
	uint16_t ins = (u8_memptr[0] << 8 | u8_memptr[1]);
	return (ins);
}
