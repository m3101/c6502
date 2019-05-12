/*
bc[0x0a]=ASL_ac;
bc[0x06]=ASL_z;
bc[0x16]=ASL_zx;
bc[0x0e]=ASL_abs;
bc[0x1e]=ASL_absx;
*/

void ASL_ac(unsigned char a1, unsigned char a2)
{
	Flags+=A>>7;
	A=A<<1;
	if(A==0)SetFlag(1,1);
	PC+=1;
}
void ASL_z(unsigned char a1, unsigned char a2)
{
	char oper=memory[a1];
	SetFlag(0,oper>>7);
	memory[a1]=oper<<1;
	if(oper<<1==0)SetFlag(1,1);
	PC+=2;
}
void ASL_zx(unsigned char a1, unsigned char a2)
{
	char oper=memory[(int)a1+(int)X];
	SetFlag(0,oper>>7);
	memory[(int)a1+(int)X]=oper<<1;
	if(oper<<1==0)SetFlag(1,1);
	PC+=2;
}
void ASL_abs(unsigned char a1, unsigned char a2)
{
	char oper=memory[(int)(a1<<8)+(int)a2];
	SetFlag(0,oper>>7);
	memory[(int)(a1<<8)+(int)a2]=oper<<1;
	if(oper<<1==0)SetFlag(1,1);
	PC+=3;
}
void ASL_absx(unsigned char a1, unsigned char a2)
{
	char oper=memory[(int)(a1<<8)+(int)a2]+(int)X;
	SetFlag(0,oper>>7);
	memory[(int)(a1<<8)+(int)a2+(int)X]=oper<<1;
	if(oper<<1==0)SetFlag(1,1);
	PC+=3;
}
