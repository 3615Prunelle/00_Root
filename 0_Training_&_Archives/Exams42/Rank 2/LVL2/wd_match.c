#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

/*
takes two strings and checks whether it's possible to write the first string with characters
from the second string, while respecting the order in which these characters appear in the second string.
If it's possible, the program displays the string, followed by a \n

$>./wdmatch "faya" "fgvvfdxcacpolhyghbreda" | cat -e
faya$
$>./wdmatch "faya" "fgvvfdxcacpolhyghbred" | cat -e
$
$>./wdmatch "quarante deux" "qfqfsudf arzgsayns tsregfdgs sjytdekuoixq " | cat -e
quarante deux$
$>./wdmatch "error" rrerrrfiiljdfxjyuifrrvcoojh | cat -e
$
$>./wdmatch | cat -e
$
*/

void	wd_match(char *s1, char *s2)
{
	int i = 0;
	int j = 0;
	int	found = 1;
	int	start_from = 0;

	while ((s1[i] != '\0') && found == 1)
	{
		found = 0;
		j = 0;
		while (s2[j] != '\0')
		{
			if((s1[i] == s2[j]) && (j >= start_from))
			{
				found = 1;
				start_from = j;
				break;				// au cas où *s1 = *s2 une autre fois
			}
			j++;
		}
		i++;
	}
	if(found == 1)
	{
		write(1, s1, strlen(s1));
	}
}

int		main(void)
{
	char	*s1 = "error";
	char	*s2 = "rrerrrfiiljdfxjyuifrrvcoojh";

	wd_match(s1, s2);

	return(0);
}
