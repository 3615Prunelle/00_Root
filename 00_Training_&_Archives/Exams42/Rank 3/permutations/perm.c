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

void	maybe_rec(char **all_poss, size_t length, size_t total_poss, char *s, char c)
{
	int i = 0;
	if(strlen(all_poss[i]) == length)
	{
		return;
	}
	all_poss[i] = c;
	maybe_rec(all_poss, length, total_poss, s, s[i]);
}

void	nightmare_round1(char *s)
{
	// base case - 2 outputs : rec or return
	// base case - strlen = size of input str ?
	size_t	length_string = strlen(s);
	size_t	amount_of_possibilities = length_string;

	for (size_t i = length_string; i > 0; i--)							// if strlen = 3 --- 3 * 2 * 1 = 6 // if 4 --- 4 * 3 * 2 * 1 = 24
	{
		if(i > 1)
			amount_of_possibilities = amount_of_possibilities * (i - 1);
	}

	char	*all_poss[amount_of_possibilities];							// Pointeur vers un tableau de n strings
	for (size_t i = 0; i < amount_of_possibilities; i++)
	{
		all_poss[i] = calloc(sizeof(char), (length_string + 1));
	}

}

int		main(void)
{
	char	input[] = "abcd";

	nightmare_round1(input);

	return(0);
}
