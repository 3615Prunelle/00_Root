#include <unistd.h>

void	ft_rot(char *s)
{
	int i = 0;
	char new13;

	while(s[i] != '\0')
	{
		if (((s[i] >= 65) && (s[i] <= 77)) || ((s[i] >= 97) && (s[i] <= 109))) // Until m ou M
		{
			new13 = s[i] + 13;
			write(1, &new13, 1);
		}
		else if (((s[i] >= 78) && (s[i] <= 90)) || ((s[i] >= 110) && (s[i] <= 122)))
		{
			new13 = s[i] - 13;
			write(1, &new13, 1);
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
		ft_rot(argv[1]);
	}
	write(1, "\n", 1);
	return(0);
}
