#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

unsigned char	reverse_bits(unsigned char octet)
{
	// octet is		1 0 1 0 1 0 1 0		170 en decimal	10 10 en hexa = aa
	// on veut		0 1 0 1 0 1 0 1		85				5 5				55

	unsigned char	new = '\0';		// Pour n'avoir que des 0 par défaut = base clean
	unsigned int	bitmask = 128;

	for (int i = 7; i >= 0; i--)	// >= car 8 bits = 8 passages
	{
		// shifter pour accueillir le nouveau bit (IMPORTANT : garder au début sinon shift en trop)
		// en décalant progressivement, le 1er bit ajouté deviendra le dernier
		new = new >> 1;
		// copier le MSB dans new, en gardant les précédents ajouts en mémoire
		new |= octet & bitmask;
		// puis décaler octet de 1 (vers la gauche) pour toujours checker le MSB
		octet = octet << 1;
	}
	return(new);
}

int		main(void)
{
// Exemple : Char 'C' 🔄 Decimal 67 🔄 Binaire 0 1 0 0 0 0 1 1 🔄 0 1 0 0   0 0 1 1 🔄 Hexa 4   3
	unsigned char	octet = 170;
	printf("Param char : [%02x]\n", octet);		// output : 0x43

	unsigned char	new;
	new = reverse_bits(octet);
	printf("Return : [%02x]\n", new);

	return(0);
}
