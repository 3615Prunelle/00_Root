#ifndef FLOOD_FILL_H
# define FLOOD_FILL_H

#include<stdio.h>
#include <stdbool.h>

// Structs

typedef struct  s_point
{
	int           x;
	int           y;
}               t_point;

// Functions

void	flood_fill(char **tab, t_point size, t_point begin);
bool	is_f(char **tab, char char_to_replace, t_point target, int x_max, int y_max);

#endif
