/*
bc[0x90]=BCC_r;
*/
void BCC_r(unsigned char a1, unsigned char a2)
{
	char c=((unsigned char)(Flags<<7))>>7;
	if(c)
	{
		PC+=2;
		return;
	}
	else
	{
		PC+=(char)a1+2;
	}
}
