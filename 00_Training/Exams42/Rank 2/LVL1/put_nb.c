#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void	put_nb (int i)	// prend un grand entier et le print en utlisant write
{
	char c;
	if (i > 0)
	{
		c = i%10 + '0';
		i /= 10;
		put_nb (i);
		write (1, &c, 1);
	}

}

int	main(int argc, char **argv)
{
	int	retatoi = atoi (argv[1]);
	printf("Converted int = %i\n", retatoi);

	printf("* Passage dans fonction put_nb *\n");
	
	put_nb (retatoi);

	return(0);
}
