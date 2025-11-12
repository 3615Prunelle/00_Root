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
	static int	backup = 0;
	static char	b[BUFFER_SIZE + 1] = "";
	char *ret = NULL;

	char *tmp = NULL;
	while (!tmp) {
		if(backup != 0)
		{
			str_append_mem(&ret, b + backup, BUFFER_SIZE - backup);
		}
		int read_ret = read(fd, b, BUFFER_SIZE);
		if ((read_ret <= 0) && (b[0] == '\0'))
			return NULL;
		if(read_ret != 0)
			b[read_ret] = '\0';							// Otherwise issue when read is 0 but char left in buffer to print
		if ((tmp = ft_strchr(b, '\n')) == NULL)
		{
			str_append_str(&ret, b);
		}
		else
		{
			str_append_mem(&ret, b, tmp - b + 1);
		}
	}
	backup = tmp - b + 1;
	return(ret);
}

int		main(void)
{
	// char	str_dst[] = "123456";
	// char	str_src[] = "abcdef";
	// char	char_test = '3';
	// size_t	size_test = 4;

	// char	*str_1;
	// str_1 = malloc(sizeof(char)* 7 );
	// for (size_t i = 0; i < 7; i++)
	// {
	// 	str_1[i] = 0;
	// }
	// for (size_t i = 0; i < 6; i++)
	// {
	// 	str_1[i] = '*';
	// }

	// char	*str_2;
	// str_2 = malloc(sizeof(char)* 7 );
	// for (size_t i = 0; i < 7; i++)
	// {
	// 	str_2[i] = 0;
	// }
	// for (size_t i = 0; i < 6; i++)
	// {
	// 	str_2[i] = '-';
	// }
	// ft_memmove(str_1, str_2, 4);

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
