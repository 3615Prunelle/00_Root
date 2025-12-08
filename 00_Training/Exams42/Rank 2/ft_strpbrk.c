#include <string.h>
#include <stdio.h>

// Test sans utiliser d'index - GOOD FUCKING LUCK

char	*ft_strpbrk(const char *s1, const char *s2)
{
	// On veut return s1, à partir des chars communs à s2
	// Même si une partie des chars est différente
	// "Hello" "lo" renvoie lo
	// "Hello" "e" renvoie ello
	// "Hello" "elln" renvoie ello
	// "Hello" "bbblo" renvoie llo (car le 1er "l" esr considéré)
	// En gros : un char en commun = 
	// feu vert pour balancer la string à partir de ce char
	// METHODO :
	// Parser S1
	// Pour chaque char, comparer avec tous les chars de s2
	// quand un char commun est trouvé, return s1 à la position de ce char
	
	char *temp = (char *)s2;	// Cast mandatory otherwise error
	char *s1_copy = (char *)s1;	// Idem

	while(*s1)
	{
		s2 = temp;		// To reinitialise s2
		while ((*s2) && (*s1 != *s2))
		{
			s2++;
		}
		if (*s1 == *s2)
		{
			s1_copy = (char *)s1; // Ou sinon, re++ avec le s1++
			return (s1_copy);
		}
		s1++;
	}
	
	return(NULL); // Aucun char en commun
}

int	main(int argc, char **argv)
{
	if (argc == 3)
	{
		printf("Official :	%s\n", strpbrk(argv[1], argv[2]));
		printf("Mine :		%s\n", ft_strpbrk(argv[1], argv[2]));
	}
	return(0);
}
