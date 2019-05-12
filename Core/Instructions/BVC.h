/*
bc[0x50]=BVC_r;
*/
void BVC_r(unsigned char a1, unsigned char a2)
{
	if(GetFlag(6))
	{
		PC+=2;
		return;
	}
	else
	{
		PC+=(char)a1+2;
	}
}
