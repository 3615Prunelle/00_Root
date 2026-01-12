#include <stdio.h>
#include <stdlib.h>

void	print_set(int *tmp_subset, int subset_length)
{
	int i = 0;
	while (i < subset_length)
	{
		printf("%d", tmp_subset[i]);
		fflush(stdout);
		if (i != (subset_length-1))
		{
			printf(" ");
			fflush(stdout);
		}
		i++;
	}
	printf("\n");
}

void	find_subsets(int n, int *set, int sz_set, int *tmp_subset, int idx_set, int subset_length, int sum)
{
	if(idx_set == sz_set)
	{
		if(sum == n)
			print_set(tmp_subset, subset_length);
		return;
	}
	tmp_subset[subset_length] = set[idx_set];
	find_subsets(n, set, sz_set, tmp_subset, idx_set+1, subset_length+1, sum + tmp_subset[subset_length]);
	find_subsets(n, set, sz_set, tmp_subset, idx_set+1, subset_length, sum);
}

int		main(int ac, char **av)
{
	int	n = atoi(av[1]);
	int	*set;
	int	*tmp_subset;
	set = malloc(sizeof(int) * ac-2);
	tmp_subset = malloc(sizeof(int) * ac-2);
	int i = 0;
	while(i < ac-2)
	{
		set[i] = atoi(av[i+2]);
		i++;
	}
	find_subsets(n, set, ac-2, tmp_subset, 0, 0, 0);
	return 0;
}
