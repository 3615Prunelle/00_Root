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
	int	fd = open("/tmp/myfifo", O_RDONLY);
	int	r_r = 0;
	int	i = 0;
	int	sz_t_f = strlen(to_filter);
	int	chars_checked = 0;

	while((r_r = read(fd, &c, 1)) != 0)
	{
		if((c == to_filter[i]) && (i < sz_t_f))
		{
			i++;
			chars_checked++;
			if(i == sz_t_f)
			{
				for(int j = 0; j < sz_t_f; j++)
					write(1, "*", 1);
				i = 0;
				chars_checked = 0;
			}
		}
		else
		{
			i = 0;
			if(chars_checked > 0)
			{
				write(1, to_filter, chars_checked);
				chars_checked = 0;
			}
			else
			{
				write(1, &c, 1);
			}
		}
	}
	
	return(0);
}
