#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

int		ft_cmp(char *s1, char *s2);
void	sort_strings(int amount_strings, char **strings_array);
void	swap_chars(char *c1, char *c2);
void	swap_strings(char **s1, char **s2);
void	perm(char **all_poss, char *s, int idx_start, int idx_end);
int		calcul_facto(int n);

int		ft_cmp(char *s1, char *s2)
{
	int i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if(s1[i] > s2[i])
			return(s1[i] - s2[i]);
		else if(s1[i] < s2[i])
			return(s1[i] - s2[i]);
		i++;
	}
	return 0;
}

void	sort_strings(int amount_strings, char **strings_array)
{
	// A TESTER
	int i = 0;
	int j = 0;
	while (i < amount_strings)
	{
		j = 0;
		while (j < amount_strings)
		{
			if(ft_cmp(strings_array[i], strings_array[j]) > 0)
				swap_strings(&strings_array[i], &strings_array[j]);
			j++;
		}
		i++;
	}
}

void	swap_chars(char *c1, char *c2)
{
	char	tmp;
	tmp = *c1;
	*c1 = *c2;
	*c2 = tmp;
}

void	swap_strings(char **s1, char **s2)
{
	char	*tmp;
	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

void	perm(char **all_poss, char *s, int idx_start, int idx_end)
{
	if(idx_start == idx_end)
	{
		for (size_t i = 0; i < idx_end; i++)
		{
			*all_poss[i] = s[i];
		}
		all_poss++;
		// puts(s);
		return;
	}
	// Swap, appel, unswap, repeat
	// Boucle sur toutes les lettres restantes
    int i = idx_start;
    while (i <= idx_end)
    {
        // 1. Swap pour fixer s[i] en position start
        swap(&s[idx_start], &s[i]);

        // 2. Appel récursif pour permuter le reste
        perm(all_poss, s, idx_start + 1, idx_end);

        // 3. Unswap pour revenir à l'état initial
        swap(&s[idx_start], &s[i]);

        i++;
    }
}

int		calcul_facto(int n)
{
	if(n == 1 || n == 0)
		return 1;
	return(n * calcul_facto(n-1));
}

int		main(int ac, char **av)
{
	int		sz = strlen(av[1]);
	int		possibilities = calcul_facto(sz);
	char	**all_poss;
	all_poss = malloc(sizeof(char*) * possibilities);
	for (size_t i = 0; i < possibilities; i++)
	{
		all_poss[i] = malloc(sizeof(char) * (sz+1));
	}

	char	*s;
	s = malloc(sizeof(char) * (sz + 1));
	int		i = 0;
	while (i <= sz)
	{
		s[i] = av[1][i];
		i++;
	}
	i = 0;
	int j = 0;
	// sort letters - Clue : use 2 indexes
	while (s[i] != '\0')
	{
		j = 0;
		while (s[j] != '\0')
		{
			if (s[i] < s[j])
			{
				swap_chars(&s[i], &s[j]);
			}
			j++;
		}
		i++;
	}
	perm(all_poss, s, 0, sz-1);

	return 0;
}
