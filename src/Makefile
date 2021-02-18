NAME = chip8_emu.bin
CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -Wold-style-definition -g
SRC = 	main.c										\
	setup/chip8_setup.c								\
	instructions/chip8_cpu_exec_extended.c						\
	instructions/chip8_ins_get_nibbles.c						\
	instructions/chip8_cpu_exec_ins.c

all :
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	rm $(NAME)

# -Wmissing-prototypes -Wstrict-prototypes
