#include "gnl.h"

int		search_mem(char *s, char c)
{
	int i = 0;
	while (i < count_chars)
	{
		if(s[i] == c)
			return(i);				// Attention, return 0 si \n est en position 0
		i++;
	}
	return(-1);
}

int		length_f(char *s)			// Utiliser seulement sur f
{
	int i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return(i);
}

int		move_mem(char *dest, char *src, int crop)
{
	int	size_f = length_f(dest);
	int	i = 0;
	int	char_moved = 0;
	while (i < crop)
	{
		dest[size_f] = src[i];
		char_moved++;
		size_f++;
		i++;
	}
	return(char_moved);
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
	static char	b[BUFFER_SIZE];
	char		*f;
	char		*r;
	// b = malloc(sizeof(char) * (BUFFER_SIZE));
	f = malloc(sizeof(char) * 10000);
	r = malloc(sizeof(char) * BUFFER_SIZE);

	static int	read_ret;
	if (search_mem(b, '\n') != -1)
	{
		read_ret = read_ret - count_chars;
		count_chars = move_mem(f, b, search_mem(b, '\n') + 1);	// Move uniquement contenu du buffer jusqu'a \n, a la suite de f - +1 car searchmem return index
		kinda_kalloc(r, BUFFER_SIZE);							// Needed to add chars at index 0
		move_mem(r, b + count_chars, read_ret - count_chars);
		kinda_kalloc(b, BUFFER_SIZE);
		move_mem(b, r, read_ret - count_chars);
	}

	else if(search_mem(b, '\n') == -1)
	{
		while(search_mem(b, '\n') == -1)
		{
			read_ret = read(fd, b, BUFFER_SIZE);
			if((read_ret <= 0) || (fd <= 0))
			{
				// free(b);
				printf("Nope\n");
				return(NULL);
			}
			if (search_mem(b, '\n') != -1)
			{
				count_chars = move_mem(f, b, search_mem(b, '\n') + 1);	// Move uniquement contenu du buffer jusqu'a \n, a la suite de f - +1 car searchmem return index
			}
			else if (search_mem(b, '\0') == -1)
			{
				count_chars = move_mem(f, b, BUFFER_SIZE);
			}
			move_mem(r, b + count_chars, read_ret - count_chars);
			kinda_kalloc(b, BUFFER_SIZE);
			move_mem(b, r, read_ret - count_chars);
		}
	}
	free(r);
	f[count_chars + 1] = '\0';

	return(f);
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
		// free(buffer); // maybe no need because the node will be freed in gnl function ?
		buffer = get_next_line(fd);
		printf("Next line :\t%s", buffer);
		fflush(stdout);
	}
	return(0);
}
