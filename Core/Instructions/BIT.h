/*
bc[0x24]=BIT_z;
bc[0x2c]=BIT_abs;
*/
void BIT_z(unsigned char a1, unsigned char a2)
{
	char oper=memory[a1];
	oper=A&&oper;
	SetFlag(7,GetBit(A,7));
	SetFlag(6,GetBit(A,6));
	if(oper==0)SetFlag(1,1);
	PC+=2;
}
void BIT_abs(unsigned char a1, unsigned char a2)
{
	char oper=memory[(int)(a1<<8)+(int)a2];
	oper=A&&oper;
	SetFlag(7,GetBit(A,7));
	SetFlag(6,GetBit(A,6));
	if(oper==0)SetFlag(1,1);
	PC+=3;
}
