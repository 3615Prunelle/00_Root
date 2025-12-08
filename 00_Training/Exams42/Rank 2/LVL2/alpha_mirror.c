#include <unistd.h>
#include <stdio.h>

void	ft_mirror(char *s)
{
	int	i = 0;
	char	swap;
	char	swap_lo;
	char	reverse_alpha_up[26];
	char	reverse_alpha_lo[26];

	swap = 90;
	swap_lo = 122;

	while(i < 26)
	{
		reverse_alpha_up[i] = swap;
		reverse_alpha_lo[i] = swap_lo;
		i++;
		swap--;
		swap_lo--;
	}

	i = 0;

	while (s[i] != '\0')
	{
		if ((s[i] >= 65) && (s[i]<= 90))
		{
			// 65 becomes 90	97 becomes 122
			// 66 becomes 89
			// et vice versaaaaa

			swap = reverse_alpha_up[s[i]-65];
			write(1, &swap, 1);
		}
		else if ((s[i] >= 97) && (s[i] <= 122))
		{
			swap = reverse_alpha_lo[s[i]-97];
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
