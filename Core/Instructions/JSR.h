/*
bc[0x20]=JSR_abs;
*/
void JSR_abs(unsigned char a1, unsigned char a2)
{
	unsigned short to=((unsigned short)a2<<8)+(unsigned short)a1;
	unsigned char b1=(unsigned char)(PC>>8);//0x70
	unsigned char b2=((unsigned char)PC<<8)>>8;//0x00
	printf("\r\nGoing to %X from 0x%X+0x%X\r\n",to,b1,b2);
	memory[SS+SP]=b2;
	SP--;
	memory[SS+SP]=b1;
	SP--;
	PC=((unsigned short)a2<<8)+a1;
}
