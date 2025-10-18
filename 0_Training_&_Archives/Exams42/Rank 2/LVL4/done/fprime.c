#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Un nombre premier est divisible uniquement par 1 et lui-même

bool	is_prime(int i)
{
	int j = 2;

	while((j != i) && (j < i))
	{
		if (i % j == 0)
		{
			return(false);
		}
		j++;
	}
	return(true);
}

void	prime_print(int number)
{
	// Update number à chaque modulo trouvé
	int	mod_to_test = 2;	// Premier nombre premier
	while((number > 1) && (mod_to_test <= number))
	{
		if(is_prime(mod_to_test))
		{
			if(number%mod_to_test == 0)
			{
				printf("%d\n", mod_to_test);
				number = number / mod_to_test;
			}
			else
				mod_to_test++;
		}
		else
			mod_to_test++;
	}
}

int	main(int argc, char **argv)
{
	int number;
	number = atoi(argv[1]);

	printf("Number is : %d\n", number);

	prime_print(number);
	
	return(0);
}
