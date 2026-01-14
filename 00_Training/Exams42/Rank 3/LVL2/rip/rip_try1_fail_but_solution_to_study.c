#include <stdio.h>
#include <stdlib.h>

int ft_balance(char *s)
{
	int i = 0;
	int open = 0;
	int close = 0;

	while (s[i] != '\0')
	{
		if (s[i] == '(')
			open++;
		else if (s[i] == ')')
		{
			if (open > 0)
				open--;
			else
				close++;
		}
		i++;
	}
	return (open + close);  // pas open - close !
}

void rip(char *s, int balance, int removed, int idx, int idx_max)
{
	if (removed == balance)
	{
		if(ft_balance(s) == 0)
			puts(s);
		return;
	}
	if (idx == idx_max)
		return;

	char tmp = s[idx];

	// Branche 1 : si c'est une parenthèse, teste en la virant (puis teste toutes les options successives) puis backtrack
	if(s[idx] == '(' || s[idx] == ')')
	{
		s[idx] = ' ';
		rip(s, balance, removed + 1, idx+1, idx_max);
		s[idx] = tmp;
	}

	// Branche 2 : teste TOUJOURS sans la virer (passe à la suivante)
	rip(s, balance, removed, idx+1, idx_max);
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
	int	to_remove = ft_balance(av[1]);
	int	idx_max = length(av[1]);
	rip(av[1], to_remove, 0, 0, idx_max);
	return 0;
}
