/*
Format: bc[0xOpcode]=COM_mode (mode = [im]mediate, [z]ero-page, [z]+[x], [abs]olute, [abs]+[x], [abs]+[y], ([ind]irect,[x]), ([ind]irect)+[y])
bc[0x29]=AND_im;
bc[0x25]=AND_z;
bc[0x35]=AND_zx;
bc[0x2d]=AND_abs;
bc[0x3d]=AND_absx;
bc[0x39]=AND_absy;
bc[0x21]=AND_indx;
bc[0x31]=AND_indy;
*/

void AND_im(unsigned char a1, unsigned char a2)
{
	A=A&&a1;
	SetFlag(7,GetBit(A,7));
	if(A==0)SetFlag(1,1);
	PC+=2;
}
void AND_z(unsigned char a1, unsigned char a2)
{
	char oper=memory[a1];
	A=A&&oper;
	SetFlag(7,GetBit(A,7));
	if(A==0)SetFlag(1,1);
	PC+=2;
}
void AND_zx(unsigned char a1, unsigned char a2)
{
	char oper=memory[a1+X];
	A=A&&oper;
	SetFlag(7,GetBit(A,7));
	if(A==0)SetFlag(1,1);
	PC+=2;
}
void AND_abs(unsigned char a1, unsigned char a2)
{
	char oper=memory[(int)(a1<<8)+(int)a2];
	A=A&&oper;
	SetFlag(7,GetBit(A,7));
	if(A==0)SetFlag(1,1);
	PC+=3;
}
void AND_absx(unsigned char a1, unsigned char a2)
{
	char oper=memory[((int)(a1<<8)+(int)a2)+(int)X];
	A=A&&oper;
	SetFlag(7,GetBit(A,7));
	if(A==0)SetFlag(1,1);
	PC+=3;
}
void AND_absy(unsigned char a1, unsigned char a2)
{
	char oper=memory[((int)(a1<<8)+(int)a2)+(int)Y];
	A=A&&oper;
	SetFlag(7,GetBit(A,7));
	if(A==0)SetFlag(1,1);
	PC+=3;
}
void AND_indx(unsigned char a1, unsigned char a2)
{
	char oper=memory[memory[(int)a1+(int)X]];
	A=A&&oper;
	SetFlag(7,GetBit(A,7));
	if(A==0)SetFlag(1,1);
	PC+=2;
}
void AND_indy(unsigned char a1, unsigned char a2)
{
	char oper=memory[(int)memory[a1]+(int)Y];
	A=A&&oper;
	SetFlag(7,GetBit(A,7));
	if(A==0)SetFlag(1,1);
	PC+=2;
}
