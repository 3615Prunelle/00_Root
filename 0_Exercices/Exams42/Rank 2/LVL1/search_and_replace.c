#include <unistd.h>

//	void	_exit(int status)

void	ft_sar(char *s, char to_rep, char new)
{
	int i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == to_rep)
			write(1, &new, 1);
		else
			write(1, &s[i] , 1);
		i++;
	}
}

int	main(int argc, char **argv)
{
	char to_replace;
	char new;

	if(argc == 4)
	{
		if ((argv[2][1] == '\0') && (argv[3][1] == '\0')) // Chaque str doit être 1 char
		{
			// !! Convertir les char str en char
			to_replace = argv[2][0];
			new = argv[3][0];
			ft_sar(argv[1], to_replace, new);
		}
	}
	write(1, "\n", 1);
	return(0);
}
