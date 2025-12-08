#include <unistd.h>

void	cam_to_sna(char *s)
{
	int i = 0;
	while(s[i] != '\0')
	{
		if((s[i] >= 'a') && (s[i] <= 'z'))
		{
			write(1, &s[i] , 1);
		}
		else if((s[i] >= 'A') && (s[i] <= 'Z'))
		{
			write(1, "_", 1);
			s[i] = s[i] + 32;
			write(1, &s[i] , 1);
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		cam_to_sna(argv[1]);
	}
	write(1, "\n", 1);
	return(0);
}
