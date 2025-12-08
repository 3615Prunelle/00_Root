#include <stdio.h>

void	ft_test(int *i)
{
	*i = 9;
}

int	main(void)
{
	int i = 10;

	ft_test(&i);
	printf("Int is :	%i\n", i);

	return(0);
}
