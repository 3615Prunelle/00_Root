#include <stdio.h>	// Test only, nothing is allowed
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool	is_space(char c)
{
	return((c >= 9 && c <= 13) || c == 32 ? true : false);
}

int	ft_atoi(const char *str)
{
	int i = 0;
	int result = 0;

	if(is_space(str[i]));
		i++;

	if(str[i] == '-')
	{
		i++;
	}
	while(str[i] != '\0')
	{
		// 1234
		// 0*10 + 1 = 1
		// 1*10 + 2 = 12
		// 12*10 + 3 = 123
		// 123*10 + 4 = 1234		
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if(str[0] == '-')
	{
		result *= -1; // mettre à la fin car 0*-1 is 0
	}
	return(result);
}

int	main(int argc, char **argv)
{
	int result;

	if (argc == 2)
	{
		result = ft_atoi(argv[1]);
		printf("My atoi :	%i\n", result);
		printf("Official :	%i\n", atoi(argv[1]));
	}
	return(0);
}
