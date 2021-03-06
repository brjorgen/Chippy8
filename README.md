# Chippy8

**_This is currently a work in progress_**

A (**soon-to-be**) complete Chip8 emulator written _entirely_ in C.

as of right now **only the disassembler** is fully functional, and
it's not even reached it's final form!

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

## The Emulator

This executable takes the path to a chip8 ROM and, emulating the chip8 machine, emulates it.
**The emulator is not functional as of yet**.
