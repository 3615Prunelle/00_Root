#include <stdio.h>

int	ft_iterative_factorial(int nb)
{
	int res = 1;

	while(nb > 0)
	{
		res = res * nb;
		nb -= 1;
	}
	return(res);
}

int	main(void)
{
	int nb;
	scanf("%d", &nb);

	int res;

	if(nb >= 0)
	{
		res = ft_iterative_factorial(nb);
		printf("%d\n", res);
	}
	return(0);
}
/*

• Create an iterated function that returns a number. This number is the result of a
factorial operation based on the number given as a parameter.
• If the argument is not valid the function should return 0.
• Overflows must not be handled, the function return will be undefined.
• Here’s how it should be prototyped :
int ft_iterative_factorial(int nb);

*/
