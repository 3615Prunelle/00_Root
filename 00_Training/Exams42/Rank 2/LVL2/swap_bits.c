#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

/*
Takes a byte, swaps its halves and returns the result.
Octet :		56 = 0 0 1 1   1 0 0 0 = 38 en hexa
Expect :	1 0 0 0   0 0 1 1 = 83 en hexa

0 0 1 1   1 0 0 0

0 0 0 0   0 0 1 1
1 0 0 0   0 0 0 0

*/

unsigned char	swap_bits(unsigned char octet)
{
	unsigned char	comp = '\0';
	int				bitmask = 1;

	for(int i = 0; i < 4; i++)
	{
		// mettre les 4 derniers bits d'octet dans comp
		comp |= octet & bitmask;
		bitmask *= 2;
	}
	octet = octet >> 4;
	comp = comp << 4;
	comp = comp | octet;

	return(comp);
}

int		main(void)
{
	unsigned char octet = 56;
	printf("%02x\n", octet);

	printf("%02x\n", swap_bits(octet));

	return(0);
}
