#include <limits>

bool Carry(unsigned char x, unsigned char y)
{
	return (std::numeric_limits<char>::max()-y)<x;
}

bool CarryS(char x, char y)
{//Yet to be done
	return (std::numeric_limits<char>::max()-y)<x;
}
