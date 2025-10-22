#include <stdio.h>
#include <unistd.h>
#include <string.h>

// Print only - Ne reverse pas la string dans la mémoire

void	print_reverse_string(char *s, int length)
{
	if(length == 0)
	{
		return;
	}
	write(1, &s[length-1], 1);
	print_reverse_string(s, length - 1);
}

int		main(void)
{
	char *s = "Hello";
	int length = strlen(s);

	print_reverse_string(s, length);
	return(0);
}
