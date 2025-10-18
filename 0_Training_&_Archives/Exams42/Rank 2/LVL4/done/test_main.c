#include "flood_fill.h"
#include "test_functions.h"

int	main(void)
{
	char **area;
	t_point size = {8, 5};
	t_point begin = {1, 1};
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
