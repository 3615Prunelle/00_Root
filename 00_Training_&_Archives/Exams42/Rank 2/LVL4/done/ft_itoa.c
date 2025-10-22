#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <ctype.h>

/*
*/

char	*ft_itoa(int nbr);

int		size_string(int nbr)
{
	int i = 0;
	while(nbr > 0)
	{
		i++;
		nbr /= 10;
	}
	return(i);
}

char	*ft_itoa(int nbr)
{
	int	size;
	int	is_neg = 0;
	if(nbr < 0)
	{
		is_neg = 1;
		nbr = -nbr;
	}
	size = size_string(nbr) + 1 + is_neg;

	char	*result;
	result = malloc(sizeof(char) * size);
	result[size-1] = '\0';
	size--;
	while(size > 0)
	{
		result[size-1] = nbr%10 + '0';
		nbr /= 10;
		size--;
	}
	if(is_neg == 1)
	{
		result[0] = '-';
	}
	return(result);
}

int		main(void)
{
	int	nbr = 0;
	printf("String : %s\n", ft_itoa(nbr));
	return(0);
}
