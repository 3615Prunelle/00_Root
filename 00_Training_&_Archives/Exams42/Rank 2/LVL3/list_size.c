#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <ctype.h>

/*
Write a function that returns the number of elements in the linked list that's
passed to it.
*/

# include "list_size.h"

int	ft_list_size(t_list *begin_list)
{
	int i = 0;
	while (begin_list != NULL)
	{
		begin_list = begin_list->next;
		i++;
	}
	return(i);
}
int		main(void)
{
	t_list	blue = {NULL, "Last"};
	t_list	green = {&blue, "Mid2"};
	t_list	purple = {&green, "Mid1"};
	t_list	red = {&purple, "First"};

	printf("%d\n", ft_list_size(&red));

	return(0);
}
