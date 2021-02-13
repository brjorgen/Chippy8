#include "../../includes/chip8.h"
#include <stdbool.h>
#include <strings.h>
#include <stdlib.h>

typedef struct		stack_s{
	int		top;	// just if i have to return -1
	int		size;	// idk
	unsigned long	*data;	// an array of addresses
}			stack_t;

void			chip8_stack_push(
	t_chip8	*chip8,
	unsigned long	addr
				  )
{
	chip8->pc++;
	chip8->mem[chip8->pc] = addr;
}

unsigned long		chip8_stack_pop(
	t_chip8	*s
				 )
{
	s->pc--;
	return (s->mem[s->pc]);
}

unsigned long		chip_stack_peek(
	t_chip8	*s
				  )
{
	return (s->mem[s->pc]);
}

bool			chip_stack_empty(
	t_chip8 *s
				   )
{
	return (s->pc == CHIP_SECTOR_START_PROG);
}
