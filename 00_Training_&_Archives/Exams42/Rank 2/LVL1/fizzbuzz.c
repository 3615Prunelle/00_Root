#include <unistd.h>

void	put_number(int i)
{
	char	c;

/*
	if (i == 0)
		write(1, "0", 1);
*/
	if (i > 0)			// si i = 12
	{
		c = i%10 + '0';		// 2
		i /= 10;		// i = 1
		put_number(i);		// return 1
		write (1, &c, 1);
	}

}

int	main(void)
{
	int i = 1;

	while (i < 101)
	{
		if ((i%3 == 0) && (i%5 == 0))
		{
			write (1, "fizzbuzz\n", 9);
			i++;
			continue;
		}
		if (i%5 == 0)
		{
			write (1, "buzz\n", 5);
			i++;
			continue;
		}
		if (i%3 == 0)
		{
			write (1, "fizz\n", 5);
			i++;
			continue;
		}
		put_number(i);
		i++;
		write (1, "\n", 1);
	}

	return(0);
}
