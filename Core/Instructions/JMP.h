/*
bc[0x4c]=JMP_abs;
bc[0x6c]=JMP_ind;
*/
void JMP_abs(unsigned char a1, unsigned char a2)
{
	PC=((unsigned short)a2<<8)+(unsigned short)a1;
}
void JMP_ind(unsigned char a1, unsigned char a2)
{
	PC=((unsigned short)memory[((unsigned short)a2<<8)+(unsigned short)a1]>>8);
}
