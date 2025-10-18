#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char	*ft_strdup(char *s)
{
	char *d;
	int i = 0;
	d = malloc(sizeof(char) * (strlen(s) + 1));
	if (!d)
		return(NULL);
	
	while(s[i] != '\0')
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
	return(d);

}

int	main(int argc, char **argv)
{
	char *dup;
	dup = ft_strdup(argv[1]);
	if (argc == 2)
	{
		printf("%s\n", dup);
	}
	free(dup);
	return(0);
}
