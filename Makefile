# Dissasembler stuff
PATH_DISAS = src/disassembler
NAME_DISAS = chip8_disassembler.bin
NAME_LINK_DISAS = chip8_disassembler

# Emulator stuff
PATH_EMU = src/
NAME_EMU = chip8_emu.bin
NAME_LINK_EMU = chip8_emulator
PATH_EMU = src
EMU_TEST_ROM = "./roms/chip8-test-rom/test_opcode.ch8"

all:	disas emu
	ln -sf $(PATH_DISAS)/$(NAME_DISAS) $(NAME_LINK_DISAS)
	ln -sf $(PATH_EMU)/$(NAME_EMU) $(NAME_LINK_EMU)

clean:
	rm $(NAME_LINK_DISAS)
	rm $(NAME_LINK_EMU)
	make clean -C $(PATH_EMU)
	make clean -C $(PATH_DISAS)

disas :
	@echo "Compiling dissasembler..."
	@make -C $(PATH_DISAS)
	@echo "done."

disas-clean :
	@echo "Removing dissasembler..."
	@make clean -C $(PATH_DISAS)
	@echo "done."

emu :
	@echo "Compiling chip8_emulator.bin..."
	@make -C $(PATH_EMU)
	@echo "done."

emu-clean:
	@echo "Removing chip8_emulator.bin..."
	@make clean -C $(PATH_EMU)
	@echo "done."

emu-test:
	@echo "Running test rom:" $(EMU_TEST_ROM)
	./$(NAME_LINK_EMU) $(EMU_TEST_ROM)
	@echo "done."

emu-debug:
	@echo "De-bugging " $(EMU_TEST_ROM)
	lldb ./$(NAME_LINK_EMU) $(EMU_TEST_ROM)
