#include <stdio.h>

// Fait par/avec Antoine Forty2.
// Failed to succeed by myself
// Retry alone at some point (France i0i)

void  zero(int nb)
{
	if (nb == 0)
	{
		printf("0");
		fflush(stdout);
		return;
	}

	printf("(");
	fflush(stdout);

	zero(nb - 1);	// REC 1

	printf(" + ");
	fflush(stdout);

	zero(nb - 1);	// REC 2

	printf(")");
	fflush(stdout);
}

int	main(void)
{
	int nb;
	scanf("%d", &nb);

	printf("0 = ");

	if ((nb >= 0) && (nb <= 15))
	{
		zero(nb);
		printf("\n");
	}
	return(0);
}

/*
CONSTRAINTS
0 <= N <= 15
INPUT
L'entier N.

OUTPUT
La chaîne indiquant la valeur de 0, en ayant remplacé N fois les zéros à droite de l'égalité "0 = 0" par leur valeur "(0 + 0)".

EXAMPLEs
input:
0
output:
0 = 0

EXAMPLE 2
input:
2
output:
0 = ((0 + 0) + (0 + 0))

EXAMPLE 3
input:
3
output:
0 = (((0 + 0) + (0 + 0)) + ((0 + 0) + (0 + 0)))

*/
