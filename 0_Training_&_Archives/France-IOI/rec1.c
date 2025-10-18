#include <stdio.h>

// Autre façon de faire avec une seule fonction (autre que main) - Voir rec2.c
// Hint : la récursivité ne se fait pas toujours dans un if

void	brackets_party1(int nb1, int nb2)
{
	if (nb2 > 0)
	{
		printf("[");
		// fflush(stdout);
		brackets_party1(nb1, nb2-1);
	}
}

void	brackets_party2(int nb1, int nb2)
{
	if (nb2 > 0)
	{
		printf("]");
		// fflush(stdout);
		brackets_party2(nb1, nb2-1);
	}
}

int	main(void)
{
	int nb1;
	int nb2;

	scanf("%d", &nb1);
	scanf("%d", &nb2);

	brackets_party1(nb1, nb2);
	printf("%d", nb1);
	brackets_party2(nb1, nb2);

	printf("\n\n");
	return(0);
}

/*
Écrivez un programme qui lit deux entiers sur l'entrée, et qui affiche le premier entier,
entouré d'autant de paires de crochets '[' et ']', qu'indiqué par la valeur du deuxième nombre.

Votre programme doit impérativement utiliser une fonction récursive, et non une boucle.

CONSTRAINTS
0 <= E <= 50, où E est le nombre de crochets à mettre de chaque côté.

EXAMPLES
input:
42 3
output:
[[[42]]]

input:
5 0
output:
5
*/
