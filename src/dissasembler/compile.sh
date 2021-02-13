#!/bin/sh

gcc -Wall -Werror -Wextra -Wpedantic ./chip8_dissasemble.c ./chip8_ins_get_nibbles.c -o chip8_dissasemble
