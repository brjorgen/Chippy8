#include <stdint.h>

uint8_t	chip8_ins_get_lo_3(uint8_t u8_memptr) {
	return((u8_memptr << 2));
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
