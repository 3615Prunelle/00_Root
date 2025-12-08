#include <stdio.h>

void	toto_rec_youpi(int nb)
{
	if(nb == 0)
	{
		printf("0");
		return;
	}
	printf("(");
	toto_rec_youpi(nb - 1);
	printf(" + ");
	toto_rec_youpi(nb - 1);
	printf(")");
}

//	nb 0 - output : 0
//	nb 1 - output : (0 + 0)				// Chaque 0 est remplacé par (0+0) dans toutes les rec supérieures
//	nb 2 - output : ((0 + 0) + (0 + 0))
//	nb 3 - output : (((0 + 0) + (0 + 0)) + ((0 + 0) + (0 + 0)))

int	main(void)
{
	int	nb = 3;

	printf("0 = ");
	toto_rec_youpi(nb);
	printf("\n");
	return(0);
}
