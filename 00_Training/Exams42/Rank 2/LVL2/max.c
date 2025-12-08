#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

//			write(1, &s[i], 1);
//			printf("Param given :\t%s\n", argv[1]);

int		max(int* tab, unsigned int len)
{
	int				result = 0;
	unsigned int	i = 0;

	while(i < len)
	{
		if(tab[i] >= result)
			result = tab[i];
		i++;
	}
	return(result);
}

int		main(void)
{
	int				tab[4] = {0};
	unsigned int	len = 4;

	int				result = 0;

	result = max(tab, len);
	printf("Result : %d\n", result);
	return(0);
}
