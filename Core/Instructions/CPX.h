/*
bc[0xe0]=CPX_im;
bc[0xe4]=CPX_z;
bc[0xec]=CPX_abs;
*/
void CPX_im(unsigned char a1, unsigned char a2)
{
	char oper=(char)X-(char)a1;
	SetFlag(0,(char)a1<(char)X);
	SetFlag(1,oper==0);
	SetFlag(7,oper<0);
	PC+=2;
}
void CPX_z(unsigned char a1, unsigned char a2)
{
	char oper=(char)X-(char)memory[a1];
	SetFlag(0,(char)memory[a1]<(char)X);
	SetFlag(1,oper==0);
	SetFlag(7,oper<0);
	PC+=2;
}
void CPX_abs(unsigned char a1, unsigned char a2)
{
	char oper=(char)X-(char)memory[(int)(a1<<8)+(int)a2];
	SetFlag(0,(char)memory[(int)(a1<<8)+(int)a2]<(char)X);
	SetFlag(1,oper==0);
	SetFlag(7,oper<0);
	PC+=3;
}
