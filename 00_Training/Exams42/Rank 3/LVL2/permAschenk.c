
#include <stdio.h>

static void	swap(char *a, char *b)
{
	char	tmp = *a;

	*a = *b;
	*b = tmp;
}

static void	bubblesort(char *str, int length)
{
	int		i = 0;
	int		j;
	int		swapped;

	while (i < length -1)
	{
		j = 0;
		swapped = 0;
		while (j < length - 1 - i)
		{
			if (str[j] > str[j + 1])
			{
				swap(&str[j], &str[j + 1]);
				swapped = 1;
			}
			j++;
		}
		if (!swapped)
			break ;
		i++;
	}
}

static void	print_permutations(char *str, int start, int end, int *used, char *permutation)
{
	int	i = 0;

	if (start == end)
	{
		puts(permutation);
		return ;
	}

	while (i < end)
	{
		if (!used[i])
		{
			used[i] = 1;
			permutation[start] = str[i];
			print_permutations(str, start + 1, end, used, permutation);
			used[i] = 0;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	int	len = 0;
	int	i = 0;

	if (argc != 2)
		return (1);

	while (argv[1][len])
		len++;

	char	permutation[len + 1];
	permutation[len] = '\0';

	int	used[len];
	while (i < len)
	{
		used[i] = 0;
		i++;
	}

	bubblesort(argv[1], len);
	print_permutations(argv[1], 0, len, used, permutation);

	return (0);
}
