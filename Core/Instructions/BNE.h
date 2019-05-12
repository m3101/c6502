/*
bc[0xd0]=BNE_r;
*/
void BNE_r(unsigned char a1, unsigned char a2)
{
	if(GetFlag(1))
	{
		PC+=2;
		return;
	}
	else
	{
		PC+=(char)a1+2;
	}
}
