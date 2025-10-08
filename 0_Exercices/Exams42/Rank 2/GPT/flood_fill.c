#include "flood_fill.h"
#include "test_functions.h"

bool	is_f(char **tab, char char_to_replace, t_point target, int x_max, int y_max)	// Update .h before testing
{
	if((target.x == x_max) || (target.y == y_max))
	{
		return(false);
	}
	else if(tab[target.x][target.y] == 'F')
	{
		return(false);
	}
	else if(tab[target.x][target.y] == char_to_replace)
	{
		tab[target.x][target.y] = 'F';
		return(true);
	}
	else
	{
		return(false);
	}

}
void	flood_fill(char **tab, t_point size, t_point begin)
{
	t_point	right = {begin.x + 1, begin.y};
	t_point	left = {begin.x - 1, begin.y};
	t_point	up = {begin.x,  begin.y - 1};
	t_point	down = {begin.x, begin.y + 1};
	
	char pass = 'F';						// Possibly useless
	char char_to_replace = tab[begin.x][begin.y];

	if(is_f(tab, char_to_replace, right, size.x, size.y))
	{
		return;
	}
}

int	main(void)
{
	char **area;
	t_point size = {8, 5};
	t_point begin = {2, 2};
	char *zone[] = {
		"11111111",
		"10001001",
		"10010001",
		"10110001",
		"11100001",
	};
	area = make_area(zone, size.x, size.y);
	print_tab(area);
	flood_fill(area, size, begin);
	print_tab(area);

	return(0);
}
