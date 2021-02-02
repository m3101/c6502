# c6502, a simple, straightforward 6502 simulator

## By Amélia O. F. da S.

---

Build by running the ```make``` command.
Test by running ```make test```.

* ```cc6502 [input file] [target file]``` - Compiles 6502 assembly to an executable file.
* ```c6502 <file> [debug]``` - Executes the file. Writing anything after the filename triggers the debugging mode, which prints every step taken, logs the states of registers and dumps a binary file with the final state of the memory afterwards.

This is a simple program made to make 6502 assembly programming easier (and introducing people to assembly languages). Its simplicity also serves the purpose of inspiring people to write their own interpreters and compilers by showing this can be quite easily (though crudely) done.

Note: This project is still incomplete. Many instructions are not yet supported, but extremely basic programs (such as the examples) can already be compiled and run.
