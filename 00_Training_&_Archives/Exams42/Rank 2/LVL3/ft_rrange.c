#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <ctype.h>

/*
It must allocate (with malloc()) an array of integers, fill it with consecutive
values that begin at end and end at start (Including start and end !), then
return a pointer to the first value of the array.

Examples:

- With (1, 3) you will return an array containing 3, 2 and 1
- With (-1, 2) you will return an array containing 2, 1, 0 and -1.
- With (0, 0) you will return an array containing 0.
- With (0, -3) you will return an array containing -3, -2, -1 and 0.
*/


int	*ft_rrange(int start, int end)
{
	int	array_size = 0;
	int	*result;

	if(start > end)
		array_size = start - end + 1;
	else if (end > start)
		array_size = end - start + 1;
	else if (start == end)
		array_size = 1;

	result = malloc(sizeof(int) * array_size);

	if (start == end)
		result[0] = start;

	int	copy = array_size;

	for (int i = 0; i < copy; i++)
	{
		if(start > end)
		{
			result[array_size-1] = start - i;
		}
		else
		{
			result[array_size-1] = start + i;
		}
		array_size--;
	}
	return(result);
}

int		main(void)
{
	int	start = 5;
	int	end = -5;

	int	*result;
	result = ft_rrange(start, end);

	free(result);

	return(0);
}
