#include <unistd.h>

void	print_bits(unsigned char octet)
{
	int	bitmask = 128;
	for(int i = 0; i < 8; i++)
	{
		if(octet & bitmask)
		{
			write(1, "1", 1);
		}
		else
		{
			write(1, "0", 1);
		}
		bitmask /= 2;
	}
}

int	main(void)
{
	unsigned char octet = 'c';
	print_bits(octet);
	return(0);
}
