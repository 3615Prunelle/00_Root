#include "gnl.h"

char *ft_strchr(char *s, int c)
{
	int i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return s + i;
		i++;
	}
	return(NULL);
}

void *ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t i = 0;
	while (i < n)
	{
		((char*)dest)[i] = ((char*)src)[i];
		i++;
	}
	return dest;
}

size_t ft_strlen(char *s)
{
	if(!s)
		return 0;
	size_t ret = 0;
	while (*s)
	{
		s++;
		ret++;
	}
	return (ret);
}

int str_append_mem(char **s1, char *s2, size_t size2)		// maybe add a check at beginning ?
{
	size_t size1 = ft_strlen(*s1);
	char *tmp = malloc(size2 + size1 + 1);
	if (!tmp)
		return 0;
	ft_memcpy(tmp, *s1, size1);
	ft_memcpy(tmp + size1, s2, size2);
	tmp [size1 + size2] = 0;
	free(*s1);
	*s1 = tmp;
	return 1;
}

int str_append_str(char **s1, char *s2)
{
	return str_append_mem(s1, s2, ft_strlen(s2));
}

void *ft_memmove(void *dest, const void *src, size_t n)
{
	if (dest < src)
		return ft_memcpy(dest, src, n);
	else if (dest == src)
		return dest;
//	size_t i = ft_strlen((char *)src) - 1;
	size_t i = n;
	while (i > 0 && ((char*)src)[i])				// maybe don't check (char*)src)[i] - Issue if it's \0 ?
	{
		((char *)dest)[i] = ((char *)src)[i];
		i--;
	}
	return dest;
}

char *get_next_line(int fd)
{
	static char	b[BUFFER_SIZE + 1] = "";
	char		*ret = NULL;

	char *tmp = ft_strchr(b, '\n');
	while (!tmp)						// tant qu'on a pas trouvé de return
	{
		if (!str_append_str(&ret, b))
			return NULL;				// only malloc issue
		for (size_t j = 0; j < BUFFER_SIZE; j++)
			b[j] = '\0';
		int read_ret = read(fd, b, BUFFER_SIZE);
		if (read_ret <= 0)
		{
			free(ret);					// has been malloc'ed in str_append_str
			return NULL;
		}
		b[read_ret] = 0;
		tmp = ft_strchr(b, '\n');
	}
	// out of the loop = \n found
	// or \n found in static buffer
	if (!str_append_mem(&ret, b, tmp - b + 1))		// append till \n in ret
	{
		free(ret);
		return NULL;
	}
	// update buffer
	ft_memmove(b, tmp+1, BUFFER_SIZE);
	return ret;
}
int		main(void)
{
	int		fd = open("test_gnl.txt", O_RDONLY);
	char	*line;
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	return 0;
}
