/*
bc[0xc9]=CMP_im;
bc[0xc5]=CMP_z;
bc[0xd5]=CMP_zx;
bc[0xcd]=CMP_abs;
bc[0xdd]=CMP_absx;
bc[0xd9]=CMP_absy;
bc[0xc1]=CMP_indx;
bc[0xd1]=CMP_indy;
*/
void CMP_im(unsigned char a1, unsigned char a2)
{
	char oper=(char)A-(char)a1;
	SetFlag(0,(char)a1<(char)A);
	SetFlag(1,oper==0);
	SetFlag(7,oper<0);
	PC+=2;
}
void CMP_z(unsigned char a1, unsigned char a2)
{
	char oper=(char)A-(char)memory[a1];
	SetFlag(0,(char)memory[a1]<(char)A);
	SetFlag(1,oper==0);
	SetFlag(7,oper<0);
	PC+=2;
}
void CMP_zx(unsigned char a1, unsigned char a2)
{
	char oper=(char)A-(char)memory[a1+X];
	SetFlag(0,(char)memory[a1+X]<(char)A);
	SetFlag(1,oper==0);
	SetFlag(7,oper<0);
	PC+=2;
}
void CMP_abs(unsigned char a1, unsigned char a2)
{
	char oper=(char)A-(char)memory[(int)(a1<<8)+(int)a2];
	SetFlag(0,(char)memory[(int)(a1<<8)+(int)a2]<(char)A);
	SetFlag(1,oper==0);
	SetFlag(7,oper<0);
	PC+=3;
}
void CMP_absx(unsigned char a1, unsigned char a2)
{
	char oper=(char)A-(char)memory[(int)(a1<<8)+(int)a2+X];
	SetFlag(0,(char)memory[(int)(a1<<8)+(int)a2+X]<(char)A);
	SetFlag(1,oper==0);
	SetFlag(7,oper<0);
	PC+=3;
}
void CMP_absy(unsigned char a1, unsigned char a2)
{
	char oper=(char)A-(char)memory[(int)(a1<<8)+(int)a2+Y];
	SetFlag(0,(char)memory[(int)(a1<<8)+(int)a2+Y]<(char)A);
	SetFlag(1,oper==0);
	SetFlag(7,oper<0);
	PC+=3;
}
void CMP_indx(unsigned char a1, unsigned char a2)
{
	char oper=(char)A-(char)memory[memory[(int)a1+(int)X]];
	SetFlag(0,(char)memory[memory[(int)a1+(int)X]]<(char)A);
	SetFlag(1,oper==0);
	SetFlag(7,oper<0);
	PC+=2;
}
void CMP_indy(unsigned char a1, unsigned char a2)
{
	char oper=(char)A-(char)memory[(int)memory[a1]+(int)Y];
	SetFlag(0,(char)memory[(int)memory[a1]+(int)Y]<(char)A);
	SetFlag(1,oper==0);
	SetFlag(7,oper<0);
	PC+=2;
}
