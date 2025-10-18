#include <unistd.h>

void	first_word(char *s)
{
	int i = 0;
	while ((s[i] == 32) || (s[i] == 9))
	{
		i++;
	}

	while (s[i] != '\0')
	{
		while ((s[i] >= 33) && (s[i] <= 126))
		{
			write (1, &(s[i]), 1); //check sans parenthèses
			i++;
		}
		break;
	}

}

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		first_word(argv[1]);
	}
	write(1, "\n", 1);
	return(0);
}
