#include <stdio.h>

// Doesn't print all the possibilites for ()))

int balance(char *str)
{
	int count = 0;
	while (*str)
	{
		if (*str == '(')
			count++;
		else if (*str == ')')
			count--;
		str++;
	}
	return count;
}

void solve(char to_remove, char* str, int i)
{
	if (!str[i])
		return;
	if (balance(str) == 0)
	{
		puts(str);
		return;
	}

	if (str[i] == to_remove)
	{
		str[i] = ' ';
		solve(to_remove, str, i + 1);
		str[i] = to_remove;
		solve(to_remove, str, i + 1);
	}
	else
		solve(to_remove, str, i + 1);
}

int	main(int argc, char **argv)
{
	(void)argc;
	int bal = balance(argv[1]);

	char to_remove = '(';
	if (bal < 0)
		to_remove = ')';

	solve(to_remove, argv[1], 0);
	return 0;
}
