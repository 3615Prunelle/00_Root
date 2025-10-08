#ifndef	FLOOD_FILL1_H
#define FLOOD_FILL1_H

#include <stdlib.h>
#include <unistd.h>

typedef struct	s_point
{
    int           x;
    int           y;
}		t_point;

char	**make_area(char **zone, int max_lines, int max_columns);
void	print_tab(char **area, int max_lines, int max_columns);
void	putc(char c);

#endif
