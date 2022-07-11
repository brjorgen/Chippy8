# How This Works
## Instructions
Instructions are two bytes wide for a total of 16 bits.
The first four bits of an instruction are it's opcode.
the other 12 are reserved for the operation's arguments.

Some instructions contain "groups", i.e instructions starting in the
same opcodes can have a group member specifiers. i.e: the 0x8... functions
form a "group", as they all start in 0x8 but the group member specifier are 
contained within the last four bits of this opcode: 0x8xy0 adds 
cpu.registers.V[y] to cpu.registers.V[x] (and sets the carry flag), 
0x8xy1 or's the value of V[x] and V[y] and sets V[x] to the result, etc..

The interface for getting specific members of instructions is contained within
chip8\_ins\_get\_ins.c. Getters for each set of 4 bits (nibble) has been implemented.
let's consider 0xDXYN:
	chip8\_ins\_get\_opcode gets D
	chip8\_ins\_get\_scnd\_nib gets X
	chip8\_ins\_get\_thrd\_nib gets Y
	chip8\_ins\_get\_lo\_nib gets N

These are all implemented using bitmasks behind the scenes.

## The CPU
The CPU is defined as a typedef'd struct containing a memory buffer, registers, fonts,
pointers to various places in the memory buffer (i.e CHIP8\_SECTOR\_START\_VID\_MEM), etc.
Said struct is defined in $PROJECT\_ROOT\includes/chip8.h.
It's initialization code is located in $PROJECT\_ROOT/src/setup

## Loading the Rom
Treated as part of the intialization sequence.
The rom file is read byte by byte and is copied directly to the memory buffer.
Each two byte instruction is read into a uint16_t.

## Executing the Rom
Technicals aside, this is a simple fetch - decode - execute loop.

All instruction implementation address are stored in a function pointer array (FPA).

Instruction bytes contained within the memory buffer are iterated over two by two, and sequencially executed by
dereferencing the FPA using bthe opcode bits of the instruction. If this opcode contains is a group,
it'll call a function that'll defer the FPA of this function group using the member specifier bits.
Otherwise, the function implementing the instruction is called through the FPA directly.
This FPA is defined in main.c, and its "extentions" are defined in chip8\_ins\_exec\_ins\_extended.c

Each instruction function receives the adress to the CPU struct and the value of it's own
16 bit instruction, executes the instruction code, returns to the cpu loop.

## Considerations
"uwu why no switch case" - Just a bit of fun. I wanted to write my own function pointer array mechanism.
That's it. You should definetly use a switch/case statement to implement this if you're trying to.

"Aren't the FPAs going to be huge? These hex values sure are big!" - No.
This only uses the first four bits of the instruction for the opcode and there are only 32 instructions within three FPAs
That's a total of (32 * 8 = 256, + 2 * 8 for the extention functions of 8 and 0 opcodes) 272 bytes used on the stack
to store all instruction functions's addresses. we're good on space.

"Why make this?" - You learn by doing 😉
