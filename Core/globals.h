unsigned char A=0;
unsigned char X=0;
unsigned char Y=0;
unsigned char Flags=0;
unsigned char SP=0xff;
unsigned char memory[0xffff];
unsigned short PS=0x7000;//Program start address
unsigned short SS=0x0100;//Stack start address
unsigned short PC=0x7000;
	/*
	Memory Divisions:
	0x00xx (zero-page)	- RAM
	0x0100 ~ 0x01ff		- Stack
	0x0200 ~ 0x6fff		- RAM
	0x7000 ~ 0xbfff		- Program
	0xc000 ~ 0xffff		- Screen
	*/

void SetFlag(char i,bool v)
{
	Flags+=(-1+(2*v))*(unsigned char)(((unsigned char)Flags<<(7-i))-(v<<7))>>(7-i);
}

bool GetFlag(char i)
{
	return (unsigned char)((unsigned char)Flags<<(7-i))>>(7-i);
}

bool GetBit(unsigned char i, char a)
{
	return (unsigned char)((unsigned char)i<<(7-a))>>(7-a);
}

void SetBit(unsigned char* f,char i, bool v)
{
	(*f)+=(-1+(2*v))*(unsigned char)(((unsigned char)(*f)<<(7-i))-(v<<7))>>(7-i);
}

