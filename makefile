install:
	@echo "c6502, by Sérgio F. Jr."
	make cc6502
	make c6502
cc6502:
	gcc ./Compiler/Compiler.c -o cc6502 -w
c6502:
	g++ ./Core/main.cpp -o c6502 -w