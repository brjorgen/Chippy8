disas :
	@echo "Compiling dissasembler..."
	@cd ./src/dissasembler && ./compile.sh && cd - && mv ./src/dissasembler/chip8_dissasemble.bin .
	@echo "done."
