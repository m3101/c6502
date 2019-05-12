/*
bc[0x18]=CLC;
*/
void CLC(unsigned char a1, unsigned char a2)
{
	SetFlag(0,0);
	PC+=1;
}
