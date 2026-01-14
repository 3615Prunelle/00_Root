#include <stdio.h>
#include <stdlib.h>

void	print_set(int *set, int idx)
{
	int i = 0;
	while (i < idx)
	{
		printf("%d", set[i]);
		if(i != (idx-1))
			printf(" ");
		i++;
	}
	printf("\n");
}

void	create_subset(int n, int *set, int sz, int *subset, int idx_set, int idx_sub, int sum)
{
	if (sum == n || (idx_set == sz))
	{
		if(sum == n)
			print_set(subset, idx_sub);
		return;
	}
	subset[idx_sub] = set[idx_set];
	// keep it
	create_subset(n, set, sz, subset, idx_set+1, idx_sub+1, sum+subset[idx_sub]);
	// ignore it
	create_subset(n, set, sz, subset, idx_set+1, idx_sub, sum);
}

int		main(int ac, char **av)
{
	int		n = atoi(av[1]);
	int		tot = ac - 2;
	int		*set;
	int		*subset;
	set = malloc(sizeof(int) * tot);
	subset = malloc(sizeof(int) * tot);
	for (size_t j = 0; j < tot; j++)
	{
		set[j] = atoi(av[2+j]);
		subset[j] = 0;
	}
	create_subset(n, set, tot, subset, 0, 0, 0);
	return 0;
}
