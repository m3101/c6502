/*
bc[0xc8]=INY;
*/
void INY(unsigned char a1, unsigned char a2)
{
	Y+=1;
	SetFlag(1,Y==0);
	SetFlag(7,(char)Y<(char)0);
	PC+=1;
}
