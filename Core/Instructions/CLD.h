/*
bc[0xd8]=CLD;
*/
void CLD(unsigned char a1, unsigned char a2)
{
	SetFlag(3,0);
	PC+=1;
}
