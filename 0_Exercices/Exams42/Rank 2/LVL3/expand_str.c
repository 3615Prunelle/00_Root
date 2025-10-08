#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <ctype.h>

/*
Takes a string and displays it with exactly three spaces
between each word, with no spaces or tabs either at the beginning or the end,
followed by a newline.

A word is a section of string delimited either by spaces/tabs, or by the
start/end of the string.
*/

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	expand_str(char *s)
{
	int i = 0;
	int	space_found = 0;

	while(s[i] == ' ')
	{
		i++;
	}
	while(s[i] != '\0')
	{
		if((space_found == 1) && ((s[i] > 33) && (s[i] < 127)))
		{
			putchar(' ');
			putchar(' ');
			putchar(' ');
			space_found = 0;
		}
		while((s[i] > 33) && (s[i] < 127))
		{
			putchar(s[i]);
			i++;
		}
		while(s[i] == ' ')
		{
			i++;
			space_found = 1;
		}
	}

}

int		main(void)
{
	char *s = "seulement          la c'est      plus dur ";
	expand_str(s);
	return(0);
}
