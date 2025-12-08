#include <unistd.h>
#include <stdio.h>

void	ft_mirror(char *s)
{
	int	i = 0;
	char	swap;

	while (s[i] != '\0')
	{
		if ((s[i] >= 65) && (s[i]<= 90))
		{
			// A	65 becomes 90		a	97 becomes 122
			// B	66 becomes 89
			// et vice versaaaaa
			// Suggestion ChatGPT : Faire une fonction conv à appeler pour simplifier

			swap = 'Z' - (s[i] - 'A'); // si Z --- 90 - (90 - 65) = 90 - 25 = 65
			write(1, &swap, 1);
		}
		else if ((s[i] >= 97) && (s[i] <= 122))
		{
			swap = 'z' - (s[i] - 'a');
			write(1, &swap, 1);
		}
		else
			write(1, &s[i], 1);
		i++;
	}
}

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		ft_mirror(argv[1]);

	}
	write(1, "\n", 1);
	return(0);
}
