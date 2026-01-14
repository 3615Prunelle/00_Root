#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void	ft_swap(char *c1, char *c2);

void	sort_string(char *s)
{
	int i = 0;
	int j = 0;
	while (s[i])
	{
		j = i + 1;
		while (s[j])
		{
			if (s[i] > s[j])
			{
				ft_swap(&s[i], &s[j]);
			}
			j++;
		}
		i++;
	}
}

void	ft_swap(char *c1, char *c2)
{
	char	tmp = *c1;
	*c1 = *c2;
	*c2 = tmp;
}

void	reverse(char *s, int start, int end)
{
	while (start < end)
	{
		ft_swap(&s[start], &s[end]);
		start++;
		end--;
	}
}

int		find_next_perm(char *s, int sz)
{
	// trouver pivot
	int	i = sz - 2;
	// trouver next bigger apres pivot
	int j = sz - 1;
	// cmp les 2 derniers jusqu'à trouver le dernier où c'est dans l'ordre
	while (s[i] > s[i+1] && i >= 0)
	{
		i--;
	}
	// si string dans le desordre, return 1
	if (i < 0)
	{
		return 1;
	}
	// trouver j = la + proche alpha de i, apres i
	while (j > i && s[i] > s[j])
	{
		j--;
	}
	// swap
	ft_swap(&s[i], &s[j]);
	// sort second part of the string
	reverse(s, i+1, sz-1);
	return 0;

}

int		main(int ac, char **av)
{
	int sz = strlen(av[1]);
	sort_string(av[1]);
	puts(av[1]);
	while ((find_next_perm(av[1], sz)) == 0)
	{
		puts(av[1]);
	}
	return 0;
}
