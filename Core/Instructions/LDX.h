/*
Format: bc[0xOpcode]=COM_mode (mode = [im]mediate, [z]ero-page, [z]+[x], [abs]olute, [abs]+[x], [abs]+[y], ([ind]irect,[x]), ([ind]irect)+[y])
bc[0xa2]=LDX_im;
bc[0xa6]=LDX_z;
bc[0xb6]=LDX_zy;
bc[0xae]=LDX_abs;
bc[0xbe]=LDX_absy;
*/

void LDX_im(unsigned char a1, unsigned char a2)
{
	X=a1;
	PC+=2;
}
void LDX_z(unsigned char a1, unsigned char a2)
{
	X=memory[a1];
	PC+=2;
}
void LDX_zy(unsigned char a1, unsigned char a2)
{
	X=memory[(int)a1+(int)Y];
	PC+=2;
}
void LDX_abs(unsigned char a1, unsigned char a2)
{
	X=memory[(int)(a1<<8)+(int)a2];
	PC+=3;
}
void LDX_absy(unsigned char a1, unsigned char a2)
{
	X=memory[((int)(a1<<8)+(int)a2)+(int)Y];
	PC+=3;
}
