#!/bin/sh

gcc -Wall -Werror -Wextra -Wpedantic ./chip8_dissasemble.c ./chip8_ins_get_nibbles.c ../setup/chip8_setup.c -o chip8_dissasemble.bin
