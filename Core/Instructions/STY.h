/*
Format: bc[0xOpcode]=COM_mode (mode = [im]mediate, [z]ero-page, [z]+[x], [abs]olute, [abs]+[x], [abs]+[y], ([ind]irect,[x]), ([ind]irect)+[y])
bc[0x86]=STX_z;
bc[0x96]=STX_zy;
bc[0x8e]=STX_abs;
*/

void STY_z(unsigned char a1, unsigned char a2)
{
	memory[a1]=Y;
	PC+=2;
}
void STY_zx(unsigned char a1, unsigned char a2)
{
	memory[(int)a1+X]=Y;
	PC+=2;
}
void STY_abs(unsigned char a1, unsigned char a2)
{
	memory[(int)(a1<<8)+(int)a2]=Y;
	PC+=3;
}
