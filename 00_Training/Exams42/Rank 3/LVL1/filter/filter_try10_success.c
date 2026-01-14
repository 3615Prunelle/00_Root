#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int	main(int ac, char **av)
{
	char	*to_filter = av[1];
	char	c;
	int		length = strlen(to_filter);
	int		i = 0;
	int		rret = 0;
	int		fd = open("yo.txt", O_RDONLY);

	rret = read(fd, &c, 1);
	if(rret < 0)
		return 1;

	while (rret > 0)
	{
		if (c == to_filter[i])
		{
			i++;						// Increment only here because it's the index for the filtered string only
			if (i == length)
			{
				for (int j = 0; j < length; j++)
					write(1, "*", 1);
				i = 0;
			}
			rret = read(fd, &c, 1);
			continue;
		}
		else
		{
			if (i > 0)
			{
				write(1, to_filter, i);
				i = 0;
				continue;				// don't read further yet, as next char may have to be filtered
			}
			else
			{
				write(1, &c, 1);
			}
			rret = read(fd, &c, 1);
		}
	}
	return(0);
}
