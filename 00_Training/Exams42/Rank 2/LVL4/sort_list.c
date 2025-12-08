#include "list.h"

int	ascending(int a, int b)
{
    return (a <= b);
}

t_list	*sort_list(t_list* lst, int (*cmp)(int, int))
{
	t_list	*back_up_head = lst;
	int temp = 0;
	int is_same = 1;

	// rajouter while qui tourne tant que tout n'est pas dans l'ordre
	while(is_same == 1) 
	{
		is_same = 0;
		while(lst->next != NULL)
		{
			if(!(cmp(*(int*)lst->data, *(int*)lst->next->data))) // si false(0)
			{
				// si lst_int est plus grand que son next, on rentre ici
				// créer var temp pour inverser les data
				temp = *(int*)lst->data; 
				*(int*)lst->data = *(int*)lst->next->data;
				*(int*)lst->next->data = temp;
				is_same = 1;
			}
			lst = lst->next;
		}
		lst = back_up_head;	// En dehors de la boucle, reset lst pour repasser dessus
	}
	return(back_up_head);
}

int	main(void)
{
	int	int6 = 999;
	int	int5 = 555;
	int	int4 = 666;
	int	int3 = 100;
	int	int2 = 250;
	int	int1 = 725;

	t_list orange = {NULL, &int3};
	t_list apple = {&orange, &int2};
	t_list pear = {&apple, &int1};	
	t_list kiwi = {&pear, &int4};	
	t_list melon = {&kiwi, &int5};	
	t_list cherry = {&melon, &int6};	

	t_list *looping_ptr = &cherry;
	int i = 1;

	while(looping_ptr != NULL)
	{
		printf("Node %i - Address : %p - Data : %d - Next : %p\n", i, looping_ptr, *(int*)looping_ptr->data, looping_ptr->next);
		looping_ptr = looping_ptr->next;
		i++;
	}
	printf("\n");
	looping_ptr = &cherry;
	i = 1;

	sort_list(&cherry, ascending);

	while(looping_ptr != NULL)
	{
		printf("Node %i - Address : %p - Data : %d - Next : %p\n", i, looping_ptr, *(int*)looping_ptr->data, looping_ptr->next);
		looping_ptr = looping_ptr->next;
		i++;
	}

	return(0);
}
