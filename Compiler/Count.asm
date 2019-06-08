#i=0
LDX #0

#loop_while
:ART
#i++
INX #1

#$00=x
STX $00

#A=$00
LDA $00
#$A=A
STA ($00),Y

#if_x==99
CPX #99
#Break
BEQ #3
JMP ART