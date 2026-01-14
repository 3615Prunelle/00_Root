#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void	print_board(int *board, int size)
{
	int i = 0;
	while (i < size)
	{
		printf("%d", board[i]);
		if(i != (size-1))
			printf(" ");
		i++;
	}
	printf("\n");

}

bool		is_safe(int *all_cols, int line, int col)
{
	int i = 0;
	while (i < col)		// No need to check after that because it hasn't been filled yet
	{
		if ((all_cols[i] == line) ||					// check for same line
			(all_cols[i] - i == line - col) ||			// check diag towards town -	mem : down =	-i / line-col
			(all_cols[i] + i == line + col) )			// check diag up				mem : up = 		+1 / line + col
		{
			return false;
		}
		i++;
	}
	return true;			// Safe to place
}
void	place_queens(int size, int *all_cols, int current_col)
{
	if (current_col == size)
	{
		print_board(all_cols, size);
		return;
	}
	int line = 0;
	while (line < size)
	{
		if (is_safe(all_cols, line, current_col))
		{
			all_cols[current_col] = line;
			place_queens(size, all_cols, current_col+1);	// Go straight to next column because this one now has a queen
		}
		line++;
	}
}

int		main(int ac, char **av)
{
	int	size = atoi(av[1]);
	int	*all_cols;
	all_cols = calloc(size, sizeof(int));
	place_queens(size, all_cols, 0);
	return (0);
}
