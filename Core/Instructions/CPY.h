/*
bc[0xc0]=CPY_im;
bc[0xc4]=CPY_z;
bc[0xcc]=CPY_abs;
*/
void CPY_im(unsigned char a1, unsigned char a2)
{
	char oper=(char)Y-(char)a1;
	SetFlag(0,(char)a1<(char)Y);
	SetFlag(1,oper==0);
	SetFlag(7,oper<0);
	PC+=2;
}
void CPY_z(unsigned char a1, unsigned char a2)
{
	char oper=(char)Y-(char)memory[a1];
	SetFlag(0,(char)memory[a1]<(char)Y);
	SetFlag(1,oper==0);
	SetFlag(7,oper<0);
	PC+=2;
}
void CPY_abs(unsigned char a1, unsigned char a2)
{
	char oper=(char)Y-(char)memory[(int)(a1<<8)+(int)a2];
	SetFlag(0,(char)memory[(int)(a1<<8)+(int)a2]<(char)Y);
	SetFlag(1,oper==0);
	SetFlag(7,oper<0);
	PC+=3;
}
