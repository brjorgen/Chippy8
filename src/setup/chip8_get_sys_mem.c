#include <stdlib.h>
#include <string.h>
#define SYS_MEM 4096

unsigned char	*chip8_setup_sys_mem(void){
	unsigned char *sys_mem;

	sys_mem = (unsigned char *)malloc(sizeof(unsigned char) * SYS_MEM);
	bzero(sys_mem, sizeof(unsigned char) * SYS_MEM);
	return (&sys_mem[0]);
}
