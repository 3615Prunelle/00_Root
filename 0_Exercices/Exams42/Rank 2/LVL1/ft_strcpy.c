#include <stdio.h>
#include <string.h>

void	ft_strcpy(char *s1, char *s2)	// s1 is dest - s2 is source
{
	int i = 0;
	while (s2[i] != '\0')
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	//return(s1);	// Pas indispensable d'avoir un retour mais si je veux en avoir,
			// changer le type de retour dans la déclaration de fonction
}

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		int length = strlen(argv[1]);
		printf("Source is : %s\n", argv[1]);
		printf("Length is : %i\n", length);
		char s1[length+1];		// Dest
		ft_strcpy(s1, argv[1]);
		
		char temoin[length+1];
		strcpy(temoin, argv[1]);

		printf("Official dest str	: %s\n", temoin);
		printf("My dest str		: %s\n", s1);
	}

	return(0);
}
