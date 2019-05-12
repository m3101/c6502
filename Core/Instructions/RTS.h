/*
bc[0x60]=RTS;
*/
void RTS(unsigned char a1, unsigned char a2)
{
	unsigned short to=((unsigned short)memory[SS+SP+1]<<8)+(unsigned short)memory[SS+SP+2];
	printf("\r\nReturning to %X\r\n",to);
	SP+=2;
	PC=to+3;
}
