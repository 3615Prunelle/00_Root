#include "gnl.h"

// NOUVELLE TENTATIVE : Tech d'Antoine - Tout sur la stack avec tres gros buffer - BINGO

int		search_mem(char *s, char c)
{
	static int i = -1;
	i++;							// Pour commencer au char suivant a la prochaine lecture
	while (s[i] != '\0')
	{
		if(s[i] == c)
		{
			return(i);
		}
		i++;
	}
	return(-1);
}

int		length_all(char *s)			// Utiliser seulement sur all
{
	int i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return(i);
}

void	copy_chars_in_mem(char *dest, char *src, int crop)
{
	int	size_f = length_all(dest);
	int	i = 0;
	while (i < crop)
	{
		dest[size_f] = src[i];
		size_f++;
		i++;
	}
}

void	kinda_kalloc(char *s, int z)
{
	int i = 0;
	while (z > 0)
	{
		s[i] = '\0';
		i++;
		z--;
	}
}

char	*get_next_line(int fd)
{
	char		b[BUFFER_SIZE] = {0};
	static char	all[10000] = {0};
	static char	line[10000] = {0};
	static int	read_ret;
	static int	index_start = 0;
	static int	index_end = 0;
	static bool	first_pass = true;

	if (first_pass)
	{
		read_ret = read(fd, b, BUFFER_SIZE);
		if((read_ret <= 0) || (fd < 0))					// 0 = stdin
		{
			return(NULL);
		}
		first_pass = false;
	}

	kinda_kalloc(line, 10000);
	// for (size_t i = 0; i < 10000; i++)				// Use kinda calloc instead
	// {
	// 	line[i] = '\0';
	// }
 	while(read_ret != 0)
	{
		copy_chars_in_mem(all, b, BUFFER_SIZE);		// Need valeur de retour ? Idee condition d'arret si souci avec read (while char_moved = BUFFER_SIZE)
		kinda_kalloc(b, BUFFER_SIZE);
		// for (size_t i = 0; i < BUFFER_SIZE; i++)	// Use kinda calloc instead
		// {
		// 	b[i] = '\0';
		// }
		read_ret = read(fd, b, BUFFER_SIZE);
	}
	// Ici, all contient l'intégralité du fd
	// Check si \n et combien - Si nada, return all
	index_end = search_mem(all, '\n') + 1;		// Le +1 fucks up everything pour le last pass
	if (index_end != -1)
	{
		// Si \n found : keep index beg + end et copy les chars dans str a return
		copy_chars_in_mem(line, &all[index_start], (index_end - index_start));
		index_start = index_end;
		if (line[0] == '\0')
		{
			return(NULL);
		}
		return(line);
	}
	else
		return(all);
}

int		main(void)
{
	int	fd;
	fd = open("./test_gnl.txt", 0);

	char	*buffer;
	buffer = get_next_line(fd);
	printf("\n\nFinal :\t\t%s", buffer);
	fflush(stdout);

	while(buffer != NULL)
	{
		buffer = get_next_line(fd);
		printf("Next line :\t%s", buffer);
		fflush(stdout);
	}
	return(0);
}
