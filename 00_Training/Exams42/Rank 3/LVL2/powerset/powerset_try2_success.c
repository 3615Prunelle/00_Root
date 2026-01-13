#include <stdio.h>
#include <stdlib.h>

void	print_subset(int *set, int idx)
{
	for (int i = 0; i < idx; i++)
	{
		printf("%d", set[i]);
		if(i != idx-1)
			printf(" ");
	}
	printf("\n");
}

void	find_subset(int n, int max_idx, int *set_init, int *subset, int idx_set, int idx_sub, int sum)
{
	if(idx_set == max_idx)
	{
		if (sum == n)
		{
			print_subset(subset, idx_sub);
		}
		return;
	}
	subset[idx_sub] = set_init[idx_set];
	// step 1 : keep this addition
	find_subset(n, max_idx, set_init, subset, idx_set+1, idx_sub+1, sum+subset[idx_sub]);
	// step 2 : ignore this addition
	find_subset(n, max_idx, set_init, subset, idx_set+1, idx_sub, sum);
}

int		main(int ac, char **av)
{
	int	n = atoi(av[1]);
	int	*set_init;
	int	*subset;
	set_init = malloc(sizeof(int) * (ac-2));
	subset = malloc(sizeof(int) * (ac-2));
	for (int i = 0; i < (ac-2); i++)
	{
		set_init[i] = atoi(av[2+i]);
	}
	find_subset(n, ac-2, set_init, subset, 0, 0, 0);
	return 0;
}
