/*
Format: bc[0xOpcode]=COM_mode (mode = [im]mediate, [z]ero-page, [z]+[x], [abs]olute, [abs]+[x], [abs]+[y], ([ind]irect,[x]), ([ind]irect)+[y])
bc[0x49]=EOR_im;
bc[0x45]=EOR_z;
bc[0x55]=EOR_zx;
bc[0x4d]=EOR_abs;
bc[0x5d]=EOR_absx;
bc[0x59]=EOR_absy;
bc[0x41]=EOR_indx;
bc[0x51]=EOR_indy;
*/

void EOR_im(unsigned char a1, unsigned char a2)
{
	A=A^a1;
	SetFlag(7,GetBit(A,7));
	if(A==0)SetFlag(1,1);
	PC+=2;
}
void EOR_z(unsigned char a1, unsigned char a2)
{
	char oper=memory[a1];
	A=A^oper;
	SetFlag(7,GetBit(A,7));
	if(A==0)SetFlag(1,1);
	PC+=2;
}
void EOR_zx(unsigned char a1, unsigned char a2)
{
	char oper=memory[a1+X];
	A=A^oper;
	SetFlag(7,GetBit(A,7));
	if(A==0)SetFlag(1,1);
	PC+=2;
}
void EOR_abs(unsigned char a1, unsigned char a2)
{
	char oper=memory[(int)(a1<<8)+(int)a2];
	A=A^oper;
	SetFlag(7,GetBit(A,7));
	if(A==0)SetFlag(1,1);
	PC+=3;
}
void EOR_absx(unsigned char a1, unsigned char a2)
{
	char oper=memory[((int)(a1<<8)+(int)a2)+(int)X];
	A=A^oper;
	SetFlag(7,GetBit(A,7));
	if(A==0)SetFlag(1,1);
	PC+=3;
}
void EOR_absy(unsigned char a1, unsigned char a2)
{
	char oper=memory[((int)(a1<<8)+(int)a2)+(int)Y];
	A=A^oper;
	SetFlag(7,GetBit(A,7));
	if(A==0)SetFlag(1,1);
	PC+=3;
}
void EOR_indx(unsigned char a1, unsigned char a2)
{
	char oper=memory[memory[(int)a1+(int)X]];
	A=A^oper;
	SetFlag(7,GetBit(A,7));
	if(A==0)SetFlag(1,1);
	PC+=2;
}
void EOR_indy(unsigned char a1, unsigned char a2)
{
	char oper=memory[(int)memory[a1]+(int)Y];
	A=A^oper;
	SetFlag(7,GetBit(A,7));
	if(A==0)SetFlag(1,1);
	PC+=2;
}
