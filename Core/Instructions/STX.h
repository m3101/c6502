/*
Format: bc[0xOpcode]=COM_mode (mode = [im]mediate, [z]ero-page, [z]+[x], [abs]olute, [abs]+[x], [abs]+[y], ([ind]irect,[x]), ([ind]irect)+[y])
bc[0x86]=STX_z;
bc[0x96]=STX_zy;
bc[0x8e]=STX_abs;
*/

void STX_z(unsigned char a1, unsigned char a2)
{
	memory[a1]=X;
	PC+=2;
}
void STX_zy(unsigned char a1, unsigned char a2)
{
	memory[(int)a1+(int)Y]=X;
	PC+=2;
}
void STX_abs(unsigned char a1, unsigned char a2)
{
	memory[(int)(a1<<8)+(int)a2]=X;
	PC+=3;
}
