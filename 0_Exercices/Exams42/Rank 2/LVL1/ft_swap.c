#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	ft_swap(int *a, int *b)
{
	int	temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

int	main(int argc, char **argv)
{
	if (argc == 3)
	{
		printf("Arg 1 is : %s\n", argv[1]);
		printf("Arg 2 is : %s\n", argv[2]);
		
		int a = atoi(argv[1]);
		int b = atoi(argv[2]);
		printf("* Passage dans atoi *\n");
		printf("Arg a is : %i\n", a);
		printf("Arg b is : %i\n", b);
		
		ft_swap(&a, &b);
		printf("* Swap *\n");
		printf("Arg a is : %i\n", a);
		printf("Arg b is : %i\n", b);

	}
	return(0);
}
