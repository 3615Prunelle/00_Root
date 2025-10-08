#include "flood_fill.h"
#include "test_functions.h"

char	**make_area(char **zone, int x_max, int y_max)	// Update .h file
{
	char	**area;
	int	i = 0;
	int	j = 0;

	area = calloc(sizeof(char*), (y_max + 1));
	while(i < y_max)
	{
		area[i] = calloc(sizeof(char), (x_max + 1));
		i++;
	}
	i = 0;	
	while (i < y_max)
	{
		j = 0;
		while (j < x_max)
		{
			area[i][j] = zone[i][j];
			j++;
		}
		i++;
	}
	return(area);
}

void	print_tab(char **zone)		// Update .h file
{
	int i = 0;

	while(zone[i] != NULL)
	{
		printf("%s\n", zone[i]);
		i++;
	}
	printf("\n");
}
