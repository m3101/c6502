/*
bc[0x30]=BMI_r;
*/
void BMI_r(unsigned char a1, unsigned char a2)
{
	if(!GetFlag(7))
	{
		PC+=2;
		return;
	}
	else
	{
		PC+=(char)a1+2;
	}
}
