#include <stdio.h>	// Test only, nothing is allowed
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

//	printf("Official :	%i\n", atoi(argv[1]));
//	write(1, "X\n", 2);

void	last_word(char *s)
{
	int		i = 0;
	int		last_word_index = 0;

	if((s[i] == 9) || (s[i] == 32))				// on ignore les premiers espaces / tabs
	{
		i++;
	}
	while (s[i] != '\0')						// premier mot trouvé
	{
		while((s[i] == 9) || (s[i] == 32))		// à partir du 1er espace trouvé après le 1er mot
		{
			i++;
			if((s[i] >= 33) && (s[i] <= 126))
			{
				last_word_index = i;
				i++;
				break;
			}
		}
		i++;
	}
	i = 0;
	while (s[i] != '\0')
	{
		if((i >= last_word_index) && ((s[i] != 9) && (s[i] != 32)))
			write(1, &s[i], 1);
		i++;
	}
}

int		main(int argc, char **argv)
{
	if (argc == 2)
	{
		printf("Param given :\t%s\n", argv[1]);
		printf("Output :\t");
		fflush(stdout);
		last_word(argv[1]);
	}
	printf("\n");
	return(0);
}
