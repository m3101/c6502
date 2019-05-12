#include <stdio.h>
#include <limits>
#include "../Core/globals.h"

int main(int argc, char** argv)
{
	/*char a=0x06;
	char b=0x05;
	bool i=(std::numeric_limits<char>::max()-b)<a;
	if(i)printf("Overflow.\r\n");
	char c=a+b;
	printf("%u + %u = %u\r\n",a,b,c);
	printf("Char limit - %u = %X\r\n",b,std::numeric_limits<char>::max()-b);
	*/
	unsigned char a=0xff;
	unsigned char b=0x05;
	unsigned char i=(std::numeric_limits<char>::max()-b);
	if(i<a)printf("Overflow.\r\n");
	unsigned char c=a+b;
	printf("%u + %u = %u\r\n",a,b,c);
	printf("Char limit - %u = %X = %u\r\n",b,i,i);
	printf("A=%u\r\n\r\n",a);
	unsigned short PC=0x7004;
	unsigned char b1=(unsigned char)(PC>>8);//0x70
	unsigned char b2=((unsigned char)PC<<8)>>8;//0x04
	unsigned short to=((unsigned short)b1<<8)+(unsigned short)b2;
	printf("%x e %x -> Going to %X",b1,b2,to);
	return 0;
}
