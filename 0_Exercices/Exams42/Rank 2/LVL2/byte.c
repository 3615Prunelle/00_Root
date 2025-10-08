#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

//			write(1, &s[i], 1);
//			printf("Param given :\t%s\n", argv[1]);

unsigned char	swap_bits(unsigned char octet)
{
	unsigned char	copie_octet = octet;
	unsigned char	final;

	octet = octet >> 4;					// on se retrouve avec 0000 au début soit x x x x 0 0 1 1
	copie_octet = copie_octet << 4;		// on se retrouve avec 0000 à la fin soit 0 1 1 0 x x x x
										//						On veut :		  0 1 1 0 0 0 1 1
										// | OR (”Is at least one of both bits set to 1?”) - Ex : x | y = 7 = true

	final = octet | copie_octet;		// FUCK YEAH

	return(final);
}

int		main(void)
{
	unsigned char	octet = '6'; 		// ascii 54 --- 0 0 1 1 0 1 1 0
										// inverse binaire 0 1 1 0 0 0 1 1 = 99 = 'c'

	printf("Before : %c\n", octet);
	octet = swap_bits(octet);
	printf("After : %c\n", octet);

	return(0);
}
