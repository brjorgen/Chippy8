NAME = chip8_disassembler.bin
CC = clang
CFLAGS = -Wall -Werror -Wextra -g -std=gnu17 -pedantic -Wold-style-definition

SRC =	chip8_disassemble.c \
	../instructions/chip8_ins_get_nibbles.c \
	../setup/chip8_setup.c \
	../setup/chip8_stacks.c

all:
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	rm $(NAME)

