#Simple Screen IO example
#Uses Ext.h.
#Waits for the user to write "Q" then quits.

:WAT
INT 11
LDX $2000

#Writes whatever was the first character to be written
STX $3000
LDX #10
STX $3001
INT 00

#Compares X to "Q"
CPX #81
BEQ #3
JMP WAT

#Writes "OK"
LDX #79
STX $3000
LDX #75
STX $3001
LDX #10
STX $3002
INT 00