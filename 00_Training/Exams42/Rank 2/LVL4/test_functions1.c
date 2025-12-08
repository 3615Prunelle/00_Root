#include "test_functions1.h"
#include "flood_fill1.h"

char	**make_area(char **zone, int max_lines, int max_columns)
{
	char	**area;
	area = malloc(sizeof(char*) * (max_lines + 2));	// Malloc des lignes uniquement - \n + \0
	for(int i = 0; i < max_columns; i++)
	{
		area[i] = malloc(sizeof(char) * (max_columns + 1));	// \0
	}
	area[max_lines] = NULL;
	
	for(int i = 0; i < max_lines; i++)
	{
		for(int j = 0; j < max_columns; j++)
		{
			area[i][j] = zone[i][j];
		}
		area[i][max_columns] = '\n';
	}
	return(area);
}

void	print_tab(char **area, int max_lines, int max_columns)
{
	for(int i = 0; i < max_lines; i++)
	{
		for(int j = 0; j <= max_columns; j++)
		{
			putc(area[i][j]);
		}
	}
}

void	putc(char c)
{
	write(1, &c, 1);
}
