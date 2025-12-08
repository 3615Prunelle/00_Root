#include <unistd.h>

int		length(char *s);
int		count_digits(int number);
void	print_itoa(int i);

int		length(char *s)
{
	int i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return(i);
}

int		count_digits(int number)
{
	int i = 0;
	while(number > 0)
	{
		i++;
		number /= 10;
	}
	return(i);
}

void	print_itoa(int number)
{
	int		digits_in_length = count_digits(number);
	char	s[digits_in_length];

	s[digits_in_length] = '\0';					// Bien penser à le mettre, et double check sa position pour éviter trash chars

	while (number > 0)
	{
		s[digits_in_length - 1] = (number%10) + '0';
		number /= 10;
		digits_in_length--;
	}
	int i = 0;
	while(s[i] != '\0')
	{
		write(1, &s[i], 1);
		i++;
	}
}

int		main(int argc, char **argv)
{
	(void)argv;
	int	how_many_args;

	if(argc > 1)
	{
		how_many_args = argc - 1;			// l'executable (argv[0]) ne compte pas
		print_itoa(how_many_args);
	}
	else
	{
		write(1, "0", 1);
	}
	write(1, "\n", 1);
	return(0);
}
