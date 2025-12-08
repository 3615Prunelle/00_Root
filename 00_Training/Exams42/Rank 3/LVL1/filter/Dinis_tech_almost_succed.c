#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main(int ac, char **av)
{
	size_t	read_ret;
	char	*to_filter = av[1];
	char	c;
	int		i = 0;
	size_t	size_to_filter = strlen(to_filter);

	int	fd = open("/tmp/myfifo", O_RDONLY);	// 'open' probably not allowed - Use only for fifo testing (check shortcuts notes)
	while ((read_ret = read(fd, &c, 1)) >= 0)
	{
		if((c == to_filter[i]) && (i < size_to_filter))
		{
			i++;
			if(i == size_to_filter)
			{
				for (size_t j = 0; j < size_to_filter; j++)
				{
					write(1, "*", 1);
				}
				i = 0;
			}
		}
		else
		{
			if(i != 0)
			{
				write(1, to_filter, i);
				i = 0;
			}
			write(1, &c, 1);
		}
	}
	return 0;
}
