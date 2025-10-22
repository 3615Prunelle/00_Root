#include <stdio.h>
#include <unistd.h>
#include <string.h>

// Made by ChatGPT - Failed to succeed by myself - Retry later
// Sujet : Inverser la string dans la mémoire en utilisant récursive (Sujet LeetCode)

void reverse_string(char *s, int length)
{
	char temp;

	if (length <= 1)
		return;

	temp = s[0];
	s[0] = s[length - 1];
	s[length - 1] = temp;

	reverse_string(s + 1, length - 2);
}

int		main(void)
{
	char s[] = "Hello";
	int length = strlen(s);

	reverse_string(s, length);
	printf("%s\n", s);
	return(0);
}
