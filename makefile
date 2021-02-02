install:
	@echo "c6502, by Amélia O. F. da S."
	@make cc6502
	@make c6502
debug:
	gcc ./Compiler/Compiler.c -o cc6502 -w -g
	g++ ./Core/main.cpp -o c6502 -w -g
update:
	rm cc6502
	rm c6502
	@make install
cc6502:
	gcc ./Compiler/Compiler.c -o cc6502 -w
c6502:
	g++ ./Core/main.cpp -o c6502 -w
test:
	make Success
Success:
	make install
	@mkdir Exec -p
	@echo "Testing compiler..."
	./cc6502 Examples/Fibonacci.asm Exec/Fib.6502
	./cc6502 Examples/Subr.asm Exec/Sub.6502
	@echo "Testing simulator..."
	./c6502 Exec/Fib.6502
	echo "QQ" | ./c6502 Exec/Sub.6502
	@echo "Test Successful">Success