#include <stdio.h>
#include <stdlib.h>

int		balance(char *s)
{
	int	i = 0;
	int	open = 0;
	int	close = 0;

	while (s[i] != '\0')
	{
		if (s[i] == '(')
		{
			open++;
		}
		else if (s[i] == ')')
		{
			if (open > 0)
			{
				open--;
			}
			else
				close++;
		}
		i++;
	}
	if (open > close)
		return(open-close);
	return(close-open);
}

void	rip(char *s, int to_remove, int removed, int idx, int idx_max)
{
	if ((removed == to_remove) && (idx == idx_max))		// A REVOIR
	{
		if(balance(s) == 0)
			puts(s);
		return;
	}
	// step 1 : backup char, to be able to backtrack
	char tmp = s[idx];
	// step 2 : make sure we're on a parenthesis - If so, replace by space
	if(s[idx] == '(' || s[idx] == ')')
	{
		s[idx] = ' ';
		removed++;
	}
	// step 3 : check new string w/ space
	rip(s, to_remove, removed, idx+1, idx_max);
	// step 4 : backtrack
	s[idx] = tmp;
	rip(s, to_remove, removed, idx, idx_max);			// A REVOIR
}

int		length(char *s)
{
	int i = 0;
	while(s[i] != '\0')
		i++;
	return i;
}

int 	main(int ac, char **av)
{
	int	to_remove = balance(av[1]);
	int	idx_max = length(av[1]) - 1;
	rip(av[1], to_remove, 0, 0, idx_max);
	return 0;
}
