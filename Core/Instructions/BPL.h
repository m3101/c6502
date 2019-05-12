/*
bc[0x10]=BPL_r;
*/
void BPL_r(unsigned char a1, unsigned char a2)
{
	if(GetFlag(7))
	{
		PC+=2;
		return;
	}
	else
	{
		PC+=(char)a1+2;
	}
}
