#include <unistd.h>
#include <stdlib.h>

// Pourquoi toutes les fonctions sont statiques ?
// static devant une fonction = “cette fonction existe, mais seulement ici”
// Pour éviter les conflits de noms de fonctions avec d'autres fichiers (ex : si swap existe ailleurs)
// Bonne pratique mais pas obligatoire
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
	Cette fonction transforme la permutation actuelle en la suivante en ordre alphabétique.
	Elle ne génère pas toutes les permutations, une seule à la fois.
	- returns 1 if next permutation exists
	- returns 0 if it was the last one
*/
static int	next_permutation(char *s)
{
	int i;			// pivot = dernier (! qu'il y en ait plusieurs ou non) index où i et i+1 sont dans l'ordre
	int j;			// index du char à échanger avec s[i] =
					// plus petit char au-dessus (!) de s[i], entre s[i] et la fin de la string
	int len;

	len = strlen_(s);
	i = len - 2;		// -2 car on veut commencer par comparer les 2 derniers chars de la string, ligne suivante
	// Next : On cherche un pivot = l'endroit le plus à droite où le char de gauche est plus petit que celui de droite
	while (i >= 0 && s[i] >= s[i + 1])
		i--;			// Tant les deux chars ne sont pas dans l'ordre, on recule,
						// jusqu'à potentiellement arriver à -1 si chaine totalement anti-alphabetique
	if (i < 0)
		return (0);		// On est arrivés au bout et on a trouvé aucune montée = dernière permutation = chaine décroissante
	j = len - 1;		// On met j à la fin de la chaine - Ici, i >= 0
	while (s[j] <= s[i])// Tant que le dernier char est plus petit ou egal a s[i]
		j--;
	swap(&s[i], &s[j]);	// Echange entre pivot et sa lettre successeur
						// But : créer une permutation plus grande
						// Mais attention, ca n'est pas forcément la plus petite possible, d'où ligne suivante
	reverse(s, i + 1, len - 1);		// Potentiellement réorganiser la fin de la string
									// On ne touche pas le début, d'où le i+1
									// On va jusqu'à la fin, d'où le len-1
	return (1);			// Permutation suivante trouvée
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
