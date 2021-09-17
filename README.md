# Chippy8

**_This is currently a work in progress_**

A (**soon-to-be**) complete Chip8 emulator written _entirely_ in C.

as of right now **only the disassembler** is fully functional, and
it's not even reached it's final form!

The emulator somewhat works with some of the roms. The IBM Logo
runs without a fatal crash.

## How to compile
The included makefile compiles two separate binaries, the emulator and the disassembler.

By default, running make without specifying a rule will compile _both_ of them.

### Makefile Rules

#### [no specified rule]
	Compiles the emulator _and_ the disassembler

#### disas
	Compiles the disassembler
	
#### disas-clean
	Cleans up the disassembler: deletes the executable and the object files.

#### emu
	Compiles the emulator

#### emu-clean
	Cleans up the emulator stuff: deletes the executable and the object files.

## The Dissasembler

This executable takes the path to a chip8 ROM dissasembles it into a pseudo-ASM.
**The mnemonic is currently subject to change**.
It was bullshit I came up with for my own convenience when I was reading documentation.

>	*usage: ./chip8_disassemble [path_to_file]*

## The Emulator

This executable takes the path to a chip8 ROM and emulates it.
**The emulator is not entirely functional as of yet**.

>	*usage: ./chip8_emulator [path_to_file]*
