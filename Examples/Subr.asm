#Simple Screen IO with Subroutines example
#Uses Ext.h.
#Waits for the user to write a character and stores it in Y
#then waits for the user to type it again then quits.

JMP STR

:CHR
#Subroutine CHR
#Waits for a charater correspondent to Y register to be typed

STY $00
INT 11

#Writes whatever was the first character to be written
LDX $2000
STX $3000
LDX #10
STX $3001
INT 00
LDX $2000
#Compares X to Y
CPX $00
BEQ #3
JMP CHR
RTS #

:STR
#Reads a character and stores it on Y
INT 11
LDY $2000
JSR CHR

#Writes "OK"
LDX #79
STX $3000
LDX #75
STX $3001
LDX #10
STX $3002
INT 00