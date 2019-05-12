/*
bc[0xe6]=INC_z;
bc[0xf6]=INC_zx;
bc[0xee]=INC_abs;
bc[0xfe]=INC_absx;
*/
void INC_z(unsigned char a1, unsigned char a2)
{
	memory[a1]=memory[a1]+1;
	SetFlag(1,memory[a1]==0);
	SetFlag(7,(char)memory[a1]<(char)0);
	PC+=2;
}
void INC_zx(unsigned char a1, unsigned char a2)
{
	memory[a1+X]=memory[a1+X]+1;
	SetFlag(1,memory[a1+X]==0);
	SetFlag(7,(char)memory[a1+X]<(char)0);
	PC+=2;
}
void INC_abs(unsigned char a1, unsigned char a2)
{
	int addr=((int)a1<<8)+(int)a2;
	memory[addr]=memory[addr]+1;
	SetFlag(1,memory[addr]==0);
	SetFlag(7,(char)memory[addr]<(char)0);
	PC+=3;
}
void INC_absx(unsigned char a1, unsigned char a2)
{
	int addr=((int)a1<<8)+(int)a2+X;
	memory[addr]=memory[addr]+1;
	SetFlag(1,memory[addr]==0);
	SetFlag(7,(char)memory[addr]<(char)0);
	PC+=3;
}
