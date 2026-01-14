#include <stdio.h>
#include <stdlib.h>

int		balance(char *s)
{
	int	i = 0;
	int	open = 0;
	int	close = 0;

	while (s[i])
	{
		if(s[i] == '(')
			open++;
		if(s[i] == ')')
		{
			if(open > 0)
				open--;
			else
				close++;
		}
		i++;
	}
	return(open+close);
}

int		ft_length(char *s)
{
	int i = 0;
	while(s[i])
	{
		i++;
	}
	return i;
}

void	rip(char *s, int to_remove, int removed, int index, int length)
{
	if ((removed == to_remove) || (index == length))
	{
		if((balance(s) == 0))
			puts(s);
		return;
	}
	char	tmp = s[index];
	if (s[index] == '(' || s[index] == ')')
	{
		s[index] = ' ';
		rip(s, to_remove, removed+1, index+1, length);
		s[index] = tmp;
	}
	rip(s, to_remove, removed, index+1, length);
}

int		main(int argc, char **argv)
{
	int	to_remove = balance(argv[1]);
	int	length = ft_length(argv[1]);
	rip(argv[1], to_remove, 0, 0, length);
	return 0;
}
