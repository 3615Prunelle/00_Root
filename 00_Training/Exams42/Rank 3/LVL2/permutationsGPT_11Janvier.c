#include <unistd.h>
#include <stdlib.h>

static void	putstr(char *s)
{
	while (*s)
		write(1, s++, 1);
	write(1, "\n", 1);
}

static int	strlen_(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return (i);
}

static void	swap(char *a, char *b)
{
	char tmp = *a;
	*a = *b;
	*b = tmp;
}

static void	reverse(char *s, int start, int end)
{
	while (start < end)
	{
		swap(&s[start], &s[end]);
		start++;
		end--;
	}
}

static void	sort(char *s)
{
	int i;
	int j;

	i = 0;
	while (s[i])
	{
		j = i + 1;			// Pour éviter de comparer la lettre à elle même et commencer à la suivante
		while (s[j])
		{
			if (s[j] < s[i])
				swap(&s[i], &s[j]);
			j++;
		}
		i++;
	}
}

/*
** returns 1 if next permutation exists
** returns 0 if it was the last one
*/
static int	next_permutation(char *s)
{
	int i;
	int j;
	int len;

	len = strlen_(s);
	i = len - 2;		// -2 car on veut commencer par comparer les 2 derniers chars de la string, ligne suivante
	// Next : On cherche un pivot = l'endroit le plus à droite où le char de gauche est plus petit que celui de droite
	while (i >= 0 && s[i] >= s[i + 1])
		i--;			// Tant que ca ne croit pas, on recule dans la string, jusqu'à potentiellement arriver à -1
	if (i < 0)
		return (0);		// On est arrivés au bout et on a trouvé aucune montée, donc c'est la dernière permutation
	j = len - 1;
	while (s[j] <= s[i])
		j--;
	swap(&s[i], &s[j]);
	reverse(s, i + 1, len - 1);
	return (1);
}

int	main(int ac, char **av)
{
	if (ac != 2)
		return (0);

	sort(av[1]);
	putstr(av[1]);
	while (next_permutation(av[1]))
		putstr(av[1]);
	return (0);
}
