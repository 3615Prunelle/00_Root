#include <stdio.h>

// Made by ChatGPT - Fail to succeed by myself #shame
// Try to redo at some point
// Sujet dans Piscine C05

int ft_recursive_factorial(int nb)
{
	if (nb < 0)        // cas invalide
		return 0;
	if (nb == 0)       // cas de base
		return 1;
	return nb * ft_recursive_factorial(nb - 1);  // cas récursif
}

int	main(void)
{
	int nb;
	scanf("%d", &nb);

	int res;
	res = ft_recursive_factorial(nb);

	printf("%d\n", res);

	return(0);
}
