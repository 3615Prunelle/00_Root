#include <unistd.h>
#include <stdlib.h>

void	ft_swap(char *a, char *b)
{
	char tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_putstr(char *s)
{
	while (*s)
		write(1, s++, 1);
	write(1, "\n", 1);
}

int	ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return (i);
}

void	sort_str(char *s)
{
	int i, j;
	for (i = 0; s[i]; i++)
		for (j = i + 1; s[j]; j++)
			if (s[i] > s[j])
				ft_swap(&s[i], &s[j]);
}

void	permute(char *s, int l, int r)
{
	int i;
	if (l == r)
		ft_putstr(s);
	else
	{
		for (i = l; i <= r; i++)
		{
			ft_swap(&s[l], &s[i]);
			permute(s, l + 1, r);
			ft_swap(&s[l], &s[i]); // backtrack
		}
	}
}

int	main(int ac, char **av)
{
		char str[] = "1324";
		sort_str(str);
		permute(str, 0, ft_strlen(str) - 1);
	return (0);
}
