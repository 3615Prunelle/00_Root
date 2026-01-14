#include "gnl.h"

char *ft_strchr(char *s, int c)
{
	int i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == c)
		return s + i;
	else
		return NULL;
}

void *ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i = 0;
	while (n > i)
	{
		((char*)dest)[i] = ((char*)src)[i];
		i++;
	}
	return dest;
}

size_t ft_strlen(char *s)
{
	size_t ret = 0;
	if (!s)
		return (0);
	while (s[ret])
		ret++;
	return (ret);
}

int str_append_mem(char **s1, char *s2, size_t size2)
{
	size_t size1 = ft_strlen(*s1);
	char *tmp = malloc(size2 + size1 + 1);
	if (!tmp)
		return 0;
	if (*s1)
		ft_memcpy(tmp, *s1, size1);
	ft_memcpy(tmp + size1, s2, size2);
	tmp[size1 + size2] = 0;
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
	else if (dest == src || n == 0)
		return dest;
	while (n > 0)
	{
		n--;
		((char*)dest)[n] = ((char*)src)[n];
	}
	return dest;
}

char *get_next_line(int fd)
{
	static char b[BUFFER_SIZE + 1] = "";
	char *ret = NULL;
	char *tmp = ft_strchr(b, '\n');

	while (!tmp)
	{
		if (!str_append_str(&ret, b))
		{
			free(ret);						// Not sure it's useful
			return NULL;
		}
		int read_ret = read(fd, b, BUFFER_SIZE);
		if (read_ret <= 0)
		{
			if (ret && *ret)				// Useless ?
				return (ret);
			free(ret);
			return NULL;
		}
		b[read_ret] = 0;
		tmp = ft_strchr(b, '\n');
	}
	if (!str_append_mem(&ret, b, tmp - b + 1))
	{
		free(ret);
		return NULL;
	}
	ft_memmove(b, tmp + 1, ft_strlen(tmp + 1) + 1);
	return ret;
}

#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	char	*line;
	int	fd = open("test_gnl.txt", O_RDONLY);

	while ((line = get_next_line(fd)))
	{
		printf("line: %s", line);
		free (line);
	}
	return (0);
}
