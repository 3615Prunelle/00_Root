#define _GNU_SOURCE	// memmem
#include <unistd.h>	// read
#include <string.h>	// strlen
#include <stdlib.h>	// malloc calloc realloc free
#include <stdio.h>	// printf perror
#include <errno.h>	// perror
#include <string.h>	// memmem memcpy

void	c_parti(char *i1, char *i2, int si1, int si2);
char	*string_to_check(void);

void	c_parti(char *i1, char *i2, int si1, int si2)
{
	int		i = 0;
	char	*occurence;
	int		chars_left;
	occurence = memmem(i2, si2, i1, si1);
	if ((si2 < si1) || (!occurence))
	{
		printf("%s\n", i2);
		return;
	}

	int	position = occurence - i2;

	while (i2[i] != '\0')
	{
		occurence = memmem(&i2[i], si2 - i, i1, si1);
		if(!occurence)
		{
			chars_left = si2 - i;
			for(int k = 0; k < chars_left; k++)
			{
				write(1, &i2[i], 1);
				i++;
			}
			break;
		}
		else
		{
			position = occurence - &i2[i];
		}

		if(position == 0)
		{
			for(int k = 0; k < si1; k++)
			{
				write(1, "*", 1);
				i++;
			}
		}
		else
		{
			for(int k = 0; k < position; k++)
			{
				write(1, &i2[i], 1);
				i++;
			}
			for(int k = 0; k < si1; k++)
			{
				write(1, "*", 1);
				i++;
			}
		}
	}
	printf("\n");
}

char	*string_to_check(void)
{
	char	*buffer;
	char	*buffer1;
	// int		i = 0;

	buffer = malloc(sizeof(char) * 1001);
	int read_return = read(0, buffer, 1000);	// includes \n, that will be replaced by \0
	if((read_return <= 0) || (buffer[0] == '\n'))
	{
		write(1, "\n", 1);
		free(buffer);
		return(NULL);
	}
	buffer1 = realloc(buffer, read_return);
	buffer1[read_return - 1] = '\0';
	return(buffer1);
}

int	main(int argc, char **argv)
{
	char *s;
	if((argc != 2) || argv[1][0] == '\0')
	{
		return(1);
	}
	int	l_i1;
	l_i1 = strlen(argv[1]);
	s = malloc(l_i1 + 1);
	if(!s)
	{
		perror("Malloc Fail");
		return(1);
	}
	s = memcpy(s, argv[1], l_i1);
	s[l_i1] = '\0';

	char *buffer;

	while (1)
	{
		buffer = string_to_check();
		if(buffer)
		{
			c_parti(s, buffer, l_i1, strlen(buffer));
		}

	}
	return(0);
}

