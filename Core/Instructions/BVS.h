/*
bc[0x70]=BVS_r;
*/
void BVS_r(unsigned char a1, unsigned char a2)
{
	if(!GetFlag(6))
	{
		PC+=2;
		return;
	}
	else
	{
		PC+=(char)a1+2;
	}
}
