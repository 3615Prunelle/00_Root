/* Find/Understand the pattern

1234
2341
3412
4123
1243
2431
4312
3124
2143

1234
1243
1324
1342
1423
1432
2134
21
23
23
24
24 */

#include "perm.h"

// !!! ALPHAB ORDER !!!
// Count chars in string
// Create string(all strlen+1 size) array of with the n options possible (NOT length * length)
// Once filled, this array will be sorted then printed

// Recursive options :
// Take a char in param / or index of that char
// add it (n times?) in position 0 of a new string
// Check si prev index has been added to str
// if not, add / if so check next index

// Level 1 (top) = string
// Level 2 = Fix 1st char
// Level 3 = Fix 2nd char
// Etc

int		factorielle(int i)
{
	if(i == 0)
	{
		return(1);
	}
	return(i * factorielle(i-1));
}
// factorielle i = i * factorielle du niveau precedent

// 3*2*1 = "factoriel 3" ou "factoriel de 3" ou 3!

char	**nightmare(char *chaine_restante)			// Call 1	Call 2	Call 3
{
	char	**liste_des_permutations = malloc(factorielle(strlen(chaine_restante)));
	for (size_t i = 0; i < strlen(chaine_restante); i++)
	{
		liste_des_permutations[i] = malloc(strlen(chaine_restante));
	}
// condition d'arret au niveau 0 = une seule lettre

	if(strlen(chaine_restante) == 1)
	{
		liste_des_permutations[0][0] = chaine_restante[0];
		return(liste_des_permutations);
	}
	int i = 0;
	int j = 0;
	while (i < strlen(chaine_restante))
	{
		char **perm_level_down = nightmare(chaine_restante + 1);
		liste_des_permutations[i] = strcat(perm_level_down[j], chaine_restante[i]);
		i++;
	}

}

int		main(void)
{
	char	input[] = "ABC";

	nightmare(input);

	return(0);
}
