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
	return NULL;
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
	size_t ret = 0;
	if(!s)
		return(ret);
	while (*s)
	{
		s++;
		ret++;
	}
	return (ret);
}

int str_append_mem(char **s1, char *s2, size_t size2)
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
	if (dest > src)
		return ft_memcpy(dest, src, n);
	else if (dest == src)
		return dest;
	int i = n-1;
	while (i >= 0)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i--;
	}
	return dest;
}

char *get_next_line(int fd)
{
	static char b[BUFFER_SIZE + 1];
	static int b_len = 0;  // Track how much valid data is in buffer
	char *ret = NULL;

	if (fd < 0)
		return NULL;

	// Allocate empty string for ret
	ret = malloc(1);
	if (!ret)
		return NULL;
	ret[0] = '\0';

	while (1)
	{
		// If buffer is empty, read more data
		if (b_len == 0)
		{
			int read_ret = read(fd, b, BUFFER_SIZE);
			if (read_ret == -1)
			{
				free(ret);
				return NULL;
			}
			if (read_ret == 0)
			{
				// EOF reached
				if (ft_strlen(ret) > 0)
					return ret;
				free(ret);
				return NULL;
			}
			b[read_ret] = '\0';
			b_len = read_ret;
		}

		// Look for newline in buffer
		char *newline_pos = ft_strchr(b, '\n');

		if (newline_pos)
		{
			// Found newline - copy up to and including \n
			int copy_len = newline_pos - b + 1;
			if (!str_append_mem(&ret, b, copy_len))
			{
				free(ret);
				return NULL;
			}

			// Move remaining data to start of buffer
			int remaining = b_len - copy_len;
			if (remaining > 0)
			{
				ft_memmove(b, b + copy_len, remaining);
				b[remaining] = '\0';
				b_len = remaining;
			}
			else
			{
				b[0] = '\0';
				b_len = 0;
			}

			return ret;
		}
		else
		{
			// No newline found - copy entire buffer to ret
			if (!str_append_str(&ret, b))
			{
				free(ret);
				return NULL;
			}
			b[0] = '\0';
			b_len = 0;  // Mark buffer as empty
		}
	}
}

int		main(void)
{
	int	fd;
	fd = open("./test_gnl.txt", 0);
	char	*buffer;
	buffer = get_next_line(fd);
	printf("%s", buffer);
	fflush(stdout);

	while(buffer != NULL)
	{
		buffer = get_next_line(fd);
		printf("%s", buffer);
		fflush(stdout);
	}
	return(0);
}
