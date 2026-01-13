#include <stdio.h>
#include <stdlib.h>

void	print_subset(int *subset, int subset_len)
{
	int	i = 0;

	while (i < subset_len)
	{
		printf("%d", subset[i]);
		if (i + 1 != subset_len)
			printf(" ");
		i++;
	}
	printf("\n");
}

void	find_subsets(int n, int *set, int s_len, int *tmp_subset, int subset_len, int s_index, int sum)
{
	if (s_index == s_len)
	{
		if (sum == n)
			print_subset(tmp_subset, subset_len);
		return ;
	}
	tmp_subset[subset_len] = set[s_index];						// on ajoute un chiffre
	find_subsets(n, set, s_len, tmp_subset, subset_len + 1, s_index + 1, sum + set[s_index]); // on garde ce chiffre
	find_subsets(n, set, s_len, tmp_subset, subset_len, s_index + 1, sum);					   // on ne le garde pas
}

int	main(int argc, char **argv)
{
	if (argc < 2)
		return (0);

	int	n = atoi(argv[1]);
	int	s_len = argc - 2;
	int	*set = malloc(sizeof(int) * s_len);
	if (!set)
		return (1);
	int	*subset = malloc(sizeof(int) * s_len);
	if (!subset)
	{
		free(set);
		return (1);
	}
	int	i = 0;
	while (i < s_len)
	{
		set[i] = atoi(argv[i + 2]);
		i++;
	}
	find_subsets(n, set, s_len, subset, 0, 0, 0);
	free(set);
	free(subset);
	return (0);
}
