#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <ctype.h>

/*
Takes a string, and displays this string with exactly one space between words,
with no spaces or tabs either at the beginning or the end, followed by a \n.

A "word" is defined as a part of a string delimited either by spaces/tabs, or
by the start/end of the string.
*/

int		index_last_char(char *s)
{
	int i = strlen(s) - 1;
	while (i > 0)
	{
		if(s[i] == ' ')
			i--;
		else
			break;
	}
	return(i);
}

void	epur_str(char *s)
{
	int	i = 0;
	int	last_char = index_last_char(s);

	while(s[i] == ' ')
	{
		i++;
	}
	while (i <= last_char)
	{
		if((isprint(s[i])) && (s[i] != ' '))
		{
			write(1, &s[i], 1);
		}
		else if((s[i] == ' ') && (s[i-1] != ' '))
		{
			write(1, &s[i], 1);
		}
		i++;
	}
}
int		main(void)
{
	char *s = "    This    is a string   .   ";
	epur_str(s);
	return(0);
}
