/*
bc[0xca]=DEX;
*/
void DEX(unsigned char a1, unsigned char a2)
{
	X-=1;
	SetFlag(1,X==0);
	SetFlag(7,(char)X<(char)0);
	PC+=1;
}
