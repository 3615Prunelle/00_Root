#include <stdio.h>

void	brackets_party(int nb1, int nb2)
{
		printf("[");
		if(nb2 == 0)
		{
			printf("%d", nb1);
			return;
		}
		brackets_party(nb1, nb2 - 1);
		printf("]");
}

int	main(void)
{
	int nb1;
	int nb2;

	scanf("%d", &nb1);
	scanf("%d", &nb2);

	brackets_party(nb1, nb2);

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
