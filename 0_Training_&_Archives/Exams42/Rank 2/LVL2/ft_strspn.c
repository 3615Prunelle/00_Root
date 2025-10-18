#include <stdio.h>
#include <string.h>

size_t	ft_strcspn(const char *s, const char *reject)
{
	int i = 0;
	int j = 0;
	size_t size = 0;

	while(s[i] != '\0')
	{
		j = 0;
		while((s[i] != reject[j]) && (reject[j]!= '\0'))
		{
			j++;
		}
		if(s[i] == reject[j])
			return(size);
		size++;
		i++;
	}
	return(size);
}

int	main(int argc, char **argv)
{
	printf("strcspn :	%li\n", strcspn(argv[1], argv[2]));
	printf("my strcspn :	%li\n", ft_strcspn(argv[1], argv[2]));
	return(0);
}
