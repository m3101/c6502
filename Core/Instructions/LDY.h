/*
Format: bc[0YOpcode]=COM_mode (mode = [im]mediate, [z]ero-page, [z]+[Y], [abs]olute, [abs]+[Y], [abs]+[y], ([ind]irect,[Y]), ([ind]irect)+[y])
bc[0Ya2]=LDY_im;
bc[0Ya6]=LDY_z;
bc[0Yb6]=LDY_zy;
bc[0Yae]=LDY_abs;
bc[0Ybe]=LDY_absy;
*/

void LDY_im(unsigned char a1, unsigned char a2)
{
	Y=a1;
	PC+=2;
}
void LDY_z(unsigned char a1, unsigned char a2)
{
	Y=memory[a1];
	PC+=2;
}
void LDY_zy(unsigned char a1, unsigned char a2)
{
	Y=memory[(int)a1+(int)Y];
	PC+=2;
}
void LDY_abs(unsigned char a1, unsigned char a2)
{
	Y=memory[(int)(a1<<8)+(int)a2];
	PC+=3;
}
void LDY_absy(unsigned char a1, unsigned char a2)
{
	Y=memory[((int)(a1<<8)+(int)a2)+(int)Y];
	PC+=3;
}
