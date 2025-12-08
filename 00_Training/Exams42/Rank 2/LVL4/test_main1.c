#include "test_functions1.h"
#include "flood_fill1.h"

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
	area = make_area(zone, size.y, size.x);
	print_tab(area, size.y, size.x);
	flood_fill(area, size, begin);
	putc('\n');
	print_tab(area, size.y, size.x);
	return (0);
}
