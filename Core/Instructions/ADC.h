#include "CarryOp.h"
/*
Format: bc[0xOpcode]=COM_mode (mode = [im]mediate, [z]ero-page, [z]+[x], [abs]olute, [abs]+[x], [abs]+[y], ([ind]irect,[x]), ([ind]irect)+[y])
bc[0x69]=ADC_im;
bc[0x65]=ADC_z;
bc[0x75]=ADC_zx;
bc[0x6d]=ADC_abs;
bc[0x7d]=ADC_absx;
bc[0x79]=ADC_absy;
bc[0x61]=ADC_indx;
bc[0x71]=ADC_indy;
*/

void ADC_im(unsigned char a1, unsigned char a2)
{
	SetFlag(0,Carry(A,a1));
	A=(char)A+(char)a1;
	if(A==0)SetFlag(1,1);
	PC+=2;
}
void ADC_z(unsigned char a1, unsigned char a2)
{
	char oper=memory[a1];
	SetFlag(0,Carry(A,oper));
	A=(char)A+(char)oper;
	if(A==0)SetFlag(1,1);
	PC+=2;
}
void ADC_zx(unsigned char a1, unsigned char a2)
{
	char oper=memory[a1+X];
	SetFlag(0,Carry(A,oper));
	A=(char)A+(char)oper;
	if(A==0)SetFlag(1,1);
	PC+=2;
}
void ADC_abs(unsigned char a1, unsigned char a2)
{
	char oper=memory[(int)(a1<<8)+(int)a2];
	SetFlag(0,Carry(A,oper));
	A=(char)A+(char)oper;
	if(A==0)SetFlag(1,1);
	PC+=3;
}
void ADC_absx(unsigned char a1, unsigned char a2)
{
	char oper=memory[((int)(a1<<8)+(int)a2)+(int)X];
	SetFlag(0,Carry(A,oper));
	A=(char)A+(char)oper;
	if(A==0)SetFlag(1,1);
	PC+=3;
}
void ADC_absy(unsigned char a1, unsigned char a2)
{
	char oper=memory[((int)(a1<<8)+(int)a2)+(int)Y];
	SetFlag(0,Carry(A,oper));
	A=(char)A+(char)oper;
	if(A==0)SetFlag(1,1);
	PC+=3;
}
void ADC_indx(unsigned char a1, unsigned char a2)
{
	char oper=memory[memory[(int)a1+(int)X]];
	SetFlag(0,Carry(A,oper));
	A=(char)A+(char)oper;
	if(A==0)SetFlag(1,1);
	PC+=2;
}
void ADC_indy(unsigned char a1, unsigned char a2)
{
	char oper=memory[(int)memory[a1]+(int)Y];
	SetFlag(0,Carry(A,oper));
	A=(char)A+(char)oper;
	if(A==0)SetFlag(1,1);
	PC+=2;
}
