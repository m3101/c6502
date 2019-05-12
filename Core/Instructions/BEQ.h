/*
bc[0xf0]=BEQ_r;
*/
void BEQ_r(unsigned char a1, unsigned char a2)
{
	if(!GetFlag(1))
	{
		PC+=2;
		return;
	}
	else
	{
		PC+=(char)a1+2;
	}
}
