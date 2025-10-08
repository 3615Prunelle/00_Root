#include <unistd.h>
#include <stdio.h>

void	repeat_alpha(char *s)	// tester retour void
{
	int i = 0;
	int j;
	while(s[i] != '\0')
	{
		if((s[i] >= 97) && (s[i] <= 122))
		{
			j = s[i] - 96;
			while (j > 0)
			{
				//printf("\nCheck before write - i is %i - j is %i - char is %c\n", i, j, s[i]);
				write(1, &s[i], 1);
				j--;
			}
			i++;
			continue;
		}
		if((s[i] >= 65) && (s[i] <= 90))
		{
			j = s[i] - 64;
			while (j > 0)
			{
				write(1, &s[i], 1);
				j--;
			}
			i++;
			continue;
		}
		else
		{
			write(1, &s[i], 1);
			i++;
		}
	}

}

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		repeat_alpha(argv[1]);
	}
	write(1, "\n", 1);
	return(0);
}

