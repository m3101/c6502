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

bool GetFlag(char i)
{
	return Flags & 1<<(7-i);
}
void SetFlag(char i,bool v)
{
	if(!GetFlag(i))Flags=Flags|(v<<(7-i));
	else
	{
		Flags-=(1<<(7-i));
		Flags=Flags|(v<<(7-i));
	}
	
}

bool GetBit(unsigned char i, char a)
{
	return a & (1<<(7-i));
}
void SetBit(unsigned char* f,char i, bool v)
{
	if(!GetBit(i,*f))(*f)=(*f)|(v<<(7-i));
	else
	{
		(*f)-=(1<<(7-i));
		(*f)=(*f)|(v<<(7-i));
	}
}

