#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main(int ac, char **av)
{
	if (ac != 2 || !*av[1])
		return 1;
	char c;
	ssize_t r;
	char *s = av[1];
	size_t i, len = strlen(s);
	while ((r = read(0, &c, 1)) > 0) {
		if (c == s[0]) {
			i = 1;
			while (i < len && read(0, &c, 1) > 0 && c == s[i])
				i++;
			if (i == len) {
				for (size_t j = 0; j < len; j++)
					write(1, "*", 1);
			} else {
				write(1, s, i);		// write chars that matched before fail
				write(1, &c, 1);	// write the mismatching char
			}
		} else
			write(1, &c, 1);
	}
	if (r < 0)
		return (perror("Error"), 1);
	return 0;
}
