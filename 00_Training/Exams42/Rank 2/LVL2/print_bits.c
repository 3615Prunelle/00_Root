#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

/* Write a function that takes a byte, and prints it in binary WITHOUT A NEWLINE AT THE END.
Example, if you pass 2 to print_bits, it will print "00000010" */

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

int		main(void)
{
	unsigned char octet = 2;
	print_bits(octet);

	return(0);
}
