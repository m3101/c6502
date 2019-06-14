#Usaremos_o_endereço_$00_como_nosso_"i"_e_$01_como_o_ponteiro_para_a_posição_onde
#está_o_fim_da_lista-2_(começa_em_$01)

#Guardamos_j=0_em_$00
LDX #0
STX $00
#Inicializamos_fibonacci_($01=arr={0x01,0x01})
LDX #1
STX $01
STX $02

:LOP
#Carregamos_X=j
LDX $00

#Esse_trecho_transfere_X_para_Y
STX $90
LDY $90
#Carregamos_A=arr[x]
LDA ($01),Y

#E_somamos_ao_seguinte
INX #1
STX $90
LDY $90
ADC ($01),Y

#Guardamos_na_posição_seguinte
INX #1
STX $90
LDY $90
STA ($01),Y

#Incrementamos_j
LDX $00
INX #1
STX $00

#Se_j=5_quebramos_o_loop
CPX #10
BEQ #03
JMP LOP