#include "flood_fill.h"
#include "test_functions.h"

bool	is_f(char **tab, char char_to_replace, t_point target, int x_max, int y_max)
{
	if((target.x == x_max) || (target.y == y_max) || (target.x < 0) || (target.y < 0))
	{
		return(false);
	}
	else if(tab[target.y][target.x] == 'F')
	{
		return(false);
	}
	else if(tab[target.y][target.x] == char_to_replace)
	{
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

	char pass = 'F';
	char char_to_replace = tab[begin.y][begin.x];
	tab[begin.y][begin.x] = pass;

	if(is_f(tab, char_to_replace, right, size.x, size.y))
	{
		flood_fill(tab, size, right);
	}
	if(is_f(tab, char_to_replace, left, size.x, size.y))
	{
		flood_fill(tab, size, left);
	}
	if(is_f(tab, char_to_replace, up, size.x, size.y))
	{
		flood_fill(tab, size, up);
	}
	if(is_f(tab, char_to_replace, down, size.x, size.y))
	{
		flood_fill(tab, size, down);
	}
}
