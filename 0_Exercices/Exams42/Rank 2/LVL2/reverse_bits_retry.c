#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

/*
Param :		56 = 0 0 1 1   1 0 0 0 = 38 en hexa
Expect :	0 0 0 1   1 1 0 0 = 1c en hexa
*/

unsigned char	reverse_bits(unsigned char octet)
{
	// prendre MSB d'octet et le mettre à LSB result
	unsigned char	result;
	int				bitmask = 128;

	for(int i = 0; i < 8; i++)
	{
		result = result >> 1;			// On fait une place pour le bit à ajouter
		result |= octet & bitmask;
		octet = octet << 1;
	}
	return(result);
}

int		main(void)
{
	unsigned char octet = 56;
	printf("%02x\n", reverse_bits(octet));

	return(0);
}
