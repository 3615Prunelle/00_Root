#include <unistd.h>
#include <stdio.h>

int	ft_strlen(char *s)
{
	int i = 0;
	while (s[i] != '\0')
		i++;
	return(i);
}

int	main(int argc, char **argv)
{
	int length;

	if (argc == 2)
	{
		length = ft_strlen(argv[1]);
		//printf("Length is %i\n", length);
		while (length >= 0)
		{
			write(1, &argv[1][length-1], 1);
			length--;
		}
	}
	write(1, "\n", 1);
	return(0);
}
