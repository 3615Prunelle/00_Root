#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool	*char_to_bin(char c)
{
	bool *strbool = malloc (sizeof(bool) * 8);
	int bitmask = 1;
	int i = 0;

	printf("Char is %c - Its ASCII is %d\n", c, c);

	while(i < 8)
	{
		if(c & bitmask)
			strbool[7-i] = 1;
		else
			strbool[7-i] = 0;
		i++;
		c = c >> 1;
	}
	return(strbool);
}

int	main(int argc, char **argv)
{
	char c = argv[1][0];
	bool *strbool;
	strbool = char_to_bin(c);
	for (int i = 0; i < 8; i++)
	{
		printf("Bool str : [%d]\n", strbool[i]);
	}
	return(0);
}
