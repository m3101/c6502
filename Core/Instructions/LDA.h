/*
Format: bc[0xOpcode]=COM_mode (mode = [im]mediate, [z]ero-page, [z]+[x], [abs]olute, [abs]+[x], [abs]+[y], ([ind]irect,[x]), ([ind]irect)+[y])
bc[0xa9]=LDA_im;
bc[0xa6]=LDA_z;
bc[0xb6]=LDA_zy;
bc[0xae]=LDA_abs;
bc[0xbe]=LDA_absy;
*/

void LDA_im(unsigned char a1, unsigned char a2)
{
	A=a1;
	PC+=2;
}
void LDA_z(unsigned char a1, unsigned char a2)
{
	A=memory[a1];
	PC+=2;
}

void LDA_zx(unsigned char a1, unsigned char a2)
{
	A=memory[a1+X];
	PC+=2;
}

void LDA_zy(unsigned char a1, unsigned char a2)
{
	A=memory[(int)a1+(int)Y];
	PC+=2;
}
void LDA_abs(unsigned char a1, unsigned char a2)
{
	A=memory[(int)(a1<<8)+(int)a2];
	PC+=3;
}
void LDA_absx(unsigned char a1, unsigned char a2)
{
	A=memory[(int)(a1<<8)+(int)a2+X];
	PC+=3;
}
void LDA_absy(unsigned char a1, unsigned char a2)
{
	A=memory[((int)(a1<<8)+(int)a2)+(int)Y];
	PC+=3;
}
void LDA_indx(unsigned char a1, unsigned char a2)
{
	A=memory[memory[(int)a1+X]];
	PC+=2;
}
void LDA_indy(unsigned char a1, unsigned char a2)
{
	A=memory[memory[(int)a1]+Y];
	PC+=2;
}