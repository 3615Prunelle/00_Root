#include <unistd.h>
#include <stdlib.h>

int		f_strlen(char *s);
void	sort_chars(char *s, int sz);
void	swap(char *a, char *b);
int		find_perm(char *s, int sz);
void	sort_end(char *s, int start, int sz);

void	print_str(char *s, int sz)
{
	write(1, s, sz);
	write(1, "\n", 1);
}

int		f_strlen(char *s)
{
	int	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return(i);
}

void	sort_chars(char *s, int sz)
{
	int	i = 0;
	int	j = 0;

	while (i < sz)
	{
		j = i + 1;
		while (j < sz)
		{
			if (s[i] > s[j])
			{
				swap(&s[i], &s[j]);
			}
			j++;
		}
		i++;
	}
}

void	swap(char *a, char *b)
{
	char	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sort_end(char *s, int start, int end)
{
	while (start < end)
	{
		swap(&s[start], &s[end]);
		start++;
		end--;
	}
}

int	find_perm(char *s, int sz)
{
	int	i = sz - 2;
	int	j = sz - 1;

	while (i >= 0 && s[i] > s[i+1])
		i--;
	if(i < 0)
		return(0);
	while ((s[j] < s[i]) && j > i)
		j--;
	swap(&s[i], &s[j]);
	sort_end(s, i+1, sz-1);
	return 1;
}

int		main(int ac, char **av)
{
	int sz = f_strlen(av[1]);
	sort_chars(av[1], sz);
	print_str(av[1], sz);

	while (find_perm(av[1], sz))
	{
		print_str(av[1], sz);
	}

	return 0;
}
