#ifndef CHIP8_H
# define CHIP8_H

# include <stdint.h>
# include <stdbool.h>
# include <unistd.h>

# define CHIP8_SECTOR_START_RAM		0x000
# define CHIP8_SECTOR_START_PROG	0x200
# define CHIP8_SECTOR_START_STACK	0x000 // i read some bs about 0xFA0 somewhere
# define CHIP8_STACK_SIZE		16
# define CHIP8_SECTOR_START_PROG_ETI660 0x600
# define CHIP8_SECTOR_START_VID_MEM	0xF00
# define CHIP8_VID_MEM_HEIGHT 32
# define CHIP8_VID_MEM_WIDTH  64
# define CHIP8_SECTOR_SIZE_VID_MEM	64 * 32
# define CHIP8_MEMSIZE			4096

typedef enum	instruction {
	CHIP8_INS_NOP = 0x0000,
	CHIP8_INS_CLS = 0x00E0,
	CHIP8_INS_RET = 0x00EE,
	CHIP8_INS_JMP = 0x1,
	CHIP8_INS_CALL = 0x2,
	CHIP8_INS_SKIP_EQ_VX_NN = 0x3,
	CHIP8_INS_SKIP_NEQ_VX_NN = 0x4,
	CHIP8_INS_SKIP_EQ_VX_VY = 0x5,
	CHIP8_INS_MOV_NN_VX = 0x6,
	CHIP8_INS_ADD_VX_NN = 0x7,
	CHIP8_INS_MOV_VY_VX = 0x8000,
	CHIP8_INS_OR_VX_VY  = 0x8001,		     // and store where?
	CHIP8_INS_AND_VX_VY = 0x8002,		     // /
	CHIP8_INS_XOR_VX_VY = 0x8003,		     // /
	CHIP8_INS_ADD_VX_VY = 0x8004,		     // ... and stores in vx
	CHIP8_INS_SUB_VX_VY = 0x8005,		     // ... and stores in vx
	CHIP8_INS_MOV_LSB_VX_VY_SHIFTR1_VX = 0x8006, // saves LSB of VX in VY & VX >>= 1
	CHIP8_INS_MOV_SUB_VY_VX_VX = 0x8007,	     // VX = VY - VX
	CHIP8_INS_MOV_MSB_VX_VY_SHIFTL1_VX = 0x800E, // saves LSB of VX in VY & VX >>= 1
	CHIP8_INS_SKIP_NEQ_VX_VY = 0x9000,	     // skip if VX != VY
	CHIP8_INS_SET_MOV_NNN_I = 0xA,		     // move NNN into I
	CHIP8_INS_JMP_ADD_NNN_V0 = 0xB,		     // JMP to NNNN + v0
	CHIP8_INS_MOV_RAND_AND_NN_VX = 0xC,	     // move rand & NN (less than or eq NNN) into VX
	CHIP8_INS_DRAW_XY = 0xD,		     // draw pixel to screen @ x, y
	CHIP8_INS_SKPK_VX = 0xE,		     // skips next instruction if key pressed
	CHIP8_INS_LD_DELAY_TIMER_VR = 0xF007,
	CHIP8_INS_WAKP_LD_VR = 0xF00A,
	CHIP8_INS_TIMER_SET_DELAY_VR = 0xF015,
	CHIP8_INS_TIMER_SET_SOUND_VR = 0xF018,
	CHIP8_INS_ADD_I_VR = 0XF01E,		      // store in I 
	CHIP8_INS_SET_I_FNT_VR = 0xF029,
	CHIP8_INS_LD_B_VR = 0xF033,
	CHIP8_INS_LD_I_VR = 0xF055,		      // store regixster 0 to x in mem starting in I
	CHIP8_INS_LD_VR_I = 0xF065,		      // store regixster 0 to x in mem starting in I
	__CHIP8_INS_TOTAL = 35,
	// add 80 with f
}		e_instruction;

#define F 15
#define SPRITE_WIDTH	8

typedef struct		s_chip8 {
	uint8_t		*mem;		// RAM & shit
	uint8_t		*display; // screen
	uint16_t	pc; // program counter
	uint16_t	sp; // program counter
	uint16_t	stack[CHIP8_STACK_SIZE];
	uint8_t		key[16];
	size_t		size;
	bool		drawn;

	struct		registers{
		uint16_t	I;
		uint8_t		*V;
	}		registers;

	struct		timers {
		uint8_t	delay;
		uint8_t	sound;
	}			timers;
}	__attribute__((packed, aligned)) t_chip8;

typedef struct		s_ins {
	uint8_t	*mnemonic;
	uint8_t	opcode;
	void		(*ins_fn)(t_chip8 *);
}			t_ins;

//uint8_t		chip8_ins_get_lo2_nib(uint8_t *u8_memptr);

void		chip8_cpu_setup(t_chip8 *chip8);
size_t		chip8_load_program(char *filename, uint8_t **source_buffer_addr);

uint16_t	chip8_ins_get_ins(uint8_t *u8_memptr);
uint16_t	chip8_ins_get_scnd_nib(uint16_t u16_ins);
uint16_t	chip8_ins_get_thrd_nib(uint16_t u16_ins);

uint8_t		chip8_ins_get_opcode(uint16_t u16_ins);
uint16_t	chip8_ins_get_hi2_nib(uint16_t u16_ins);

uint16_t	chip8_ins_get_lo_nib(uint16_t u16_ins);
uint16_t	chip8_ins_get_lo2_nib(uint16_t u16_ins);
uint16_t	chip8_ins_get_lo3_nib(uint16_t u16_ins);


// Execution stuff
// note : void		(*chip8_cpu_exec_ins_fun[__CHIP8_INS_TOTAL])(t_chip8 *cpu, uint8_t *u8_memptr);
// -- extentions to fptr array
void		chip8_cpu_exec_ins_fun__extend_00XX(t_chip8 *cpu, uint16_t u16_ins);
void		chip8_cpu_exec_ins_fun__extend_800X(t_chip8 *cpu, uint16_t u16_memptr);
void		chip8_cpu_exec_ins_fun__extend_900X(t_chip8 *cpu, uint16_t u16_memptr);
void		chip8_cpu_exec_ins_fun__extend_F0XX(t_chip8 *cpu, uint16_t u16_memptr);

// -- instructions (chosen to be a u16 because they're all two bytes long)
void		chip8_cpu_exec_ins_cls(t_chip8 *cpu, uint16_t u16_ins);
void		chip8_cpu_exec_ins_ret(t_chip8 *cpu, uint16_t u16_ins);
void		chip8_cpu_exec_ins_unhandled(t_chip8 *cpu, uint16_t u16_ins);
void		chip8_cpu_exec_ins_call_nnn(t_chip8 *cpu, uint16_t u16_ins);

void		chip8_cpu_exec_ins_jmp_nnn(t_chip8 *cpu, uint16_t u16_ins);
void		chip8_cpu_exec_ins_skpe_vx_nnn(t_chip8 *cpu, uint16_t u16_ins);
void		chip8_cpu_exec_ins_skpn_vx_nnn(t_chip8 *cpu, uint16_t u16_ins);
void		chip8_cpu_exec_ins_skpe_vx_vy(t_chip8 *cpu, uint16_t u16_ins);
void		chip8_cpu_exec_ins_ld_nnn_i(t_chip8 *cpu, uint16_t u16_ins); // nnn INTO I
void		chip8_cpu_exec_ins_NOP(t_chip8 *cpu, uint16_t u16_ins);
void		chip8_cpu_exec_ins_ld_nnn_vx(t_chip8 *cpu, uint16_t u16_ins);
void		chip8_cpu_exec_ins_add_vx_nnn(t_chip8 *cpu, uint16_t u16_ins);
void		chip8_cpu_exec_ins_mov_vy_vx(t_chip8 *cpu, uint16_t u16_ins);

void		chip8_cpu_exec_ins_jmp_v0_add_nnn(t_chip8 *cpu, uint16_t u16_ins);
void		chip8_cpu_exec_ins_draw(t_chip8 *cpu, uint16_t u16_ins);
void		chip8_cpu_exec_ins_skp_kp(t_chip8 *cpu, uint16_t u16_ins);

void		chip8_cpu_exec_ins_ld_vx_dt(t_chip8 *cpu, uint16_t u16_ins);
void		chip8_cpu_exec_ins_ld_dt_vx(t_chip8 *cpu, uint16_t u16_ins);

void		chip8_cpu_exec_ins_ld_st_vx(t_chip8 *cpu, uint16_t u16_ins);

void		chip8_cpu_exec_ins_ld_add_vx_I(t_chip8 *cpu, uint16_t u16_ins);

void		chip8_cpu_exec_ins_rnd(t_chip8 *cpu, uint16_t u16_ins);
void		chip8_cpu_exec_ins_sne(t_chip8 *cpu, uint16_t u16_ins);
bool		in_array(int a, int *b, size_t s);

// all the 0x800N shit
void		chip8_cpu_exec_ins_sub_vy_vx(t_chip8 *cpu, uint16_t u16_ins);
void		chip8_cpu_exec_ins_add_vy_vx(t_chip8 *cpu, uint16_t u16_ins);
void		chip8_cpu_exec_ins_xor_vy_vx(t_chip8 *cpu, uint16_t u16_ins);
void		chip8_cpu_exec_ins_and_vy_vx(t_chip8 *cpu, uint16_t u16_ins);
void		chip8_cpu_exec_ins_or_vy_vx(t_chip8 *cpu, uint16_t u16_ins);
void		chip8_cpu_exec_ins_movlsb_vx_vy_shiftr1_vx(t_chip8 *cpu, uint16_t u16_ins);

// stack
void		chip8_stack_init(t_chip8 *chip8);
void		chip8_stack_push(t_chip8 *chip8, uint16_t addr);
uint16_t	chip8_stack_pop(t_chip8	*s);
uint16_t	chip8_stack_peek(t_chip8 *s);
bool		chip8_stack_empty(t_chip8 *s);

#endif
