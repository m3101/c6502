/*
Format: bc[0xOpcode]=COM_mode (mode = [im]mediate, [z]ero-page, [z]+[x], [abs]olute, [abs]+[x], [abs]+[y], ([ind]irect,[x]), ([ind]irect)+[y])
bc[0xa9]=STA_im;
bc[0xa6]=STA_z;
bc[0xb6]=STA_zy;
bc[0xae]=STA_abs;
bc[0xbe]=STA_absy;
*/

void STA_z(unsigned char a1, unsigned char a2)
{
	memory[a1]=A;
	PC+=2;
}

void STA_zx(unsigned char a1, unsigned char a2)
{
	memory[a1+X]=A;
	PC+=2;
}

void STA_zy(unsigned char a1, unsigned char a2)
{
	memory[(int)a1+(int)Y]=A;
	PC+=2;
}
void STA_abs(unsigned char a1, unsigned char a2)
{
	memory[(int)(a1<<8)+(int)a2]=A;
	PC+=3;
}
void STA_absx(unsigned char a1, unsigned char a2)
{
	memory[(int)(a1<<8)+(int)a2+X]=A;
	PC+=3;
}
void STA_absy(unsigned char a1, unsigned char a2)
{
	memory[((int)(a1<<8)+(int)a2)+(int)Y]=A;
	PC+=3;
}
void STA_indx(unsigned char a1, unsigned char a2)
{
	memory[memory[(int)a1+X]]=A;
	PC+=2;
}
void STA_indy(unsigned char a1, unsigned char a2)
{
	memory[memory[(int)a1]+Y]=A;
	PC+=2;
}