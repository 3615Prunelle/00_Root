#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

/*

*/

bool	is_prime(int i)
{
	int	comp = 2;

	if(i <= 1)
		return(false);

	while(comp < i)
	{
		if(i % comp == 0)
		{
			return(false);
		}
		comp++;
	}
	return(true);
}
int		main(void)
{
	int	nbr = 7;
	int	result = 0;

	for (int i = 0; i <= nbr; i++)
	{
		if(is_prime(i))
		{
			result += i;
		}
	}
	printf("%d\n", result);
	return(0);
}
