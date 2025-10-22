/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_check_and_exit.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sophie <sophie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 17:45:21 by sophie            #+#    #+#             */
/*   Updated: 2025/08/22 17:37:18 by sophie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

bool	is_number_repeat(int *numbers_arr, int arr_size)
{
	int	i;
	int	j;
	int	count_occurences;

	i = 0;
	while (i < arr_size)
	{
		j = 0;
		count_occurences = 0;
		while (j < arr_size)
		{
			if (numbers_arr[i] == numbers_arr[j])
			{
				count_occurences++;
				if (count_occurences > 1)
					return (true);
			}
			j++;
		}
		i++;
	}
	return (false);
}

// Ici on créée des nodes sans nom à la chaine+malloc du node (pas du content)
t_node	*create_stack(t_node *stack, int *numbers_arr, int *arr_size)
{
	t_node	*new;
	int		i;

	stack = new_node(&numbers_arr[0]);
	i = 1;
	while (i < *arr_size)
	{
		new = new_node(&numbers_arr[i]);
		add_node_down(&stack, new);
		i++;
	}
	return (stack);
}

// print sur stderr
void	clean_early_exit(char *msg, int *numbers_arr)
{
	if (numbers_arr)
		free(numbers_arr);
	ft_dprintf(2, "%s", msg);
	exit(1);
}

// lstclear not used because it frees node+content (and no content was malloc)
// No need to check for stack b, car il n'a (à priori) jamais été malloc'é
void	free_nodes(t_2stacks *a_b)
{
	t_node	*loop_pointer;
	t_node	*backup_next;

	if (a_b)
	{
		if (a_b->stack_a)
		{
			loop_pointer = a_b->stack_a;
			while (loop_pointer != NULL)
			{
				backup_next = loop_pointer->next;
				free(loop_pointer);
				loop_pointer = backup_next;
			}
			a_b->stack_a = NULL;
			free(a_b);
			a_b = NULL;
		}
	}
}

// void	print_sorted_stack(t_node *stack)
// {
// 	while (stack != NULL)
// 	{
// 		ft_printf("%i ", *(int *)(stack->content));
// 		stack = stack->next;
// 	}
// 	ft_printf("\n\n");
// }
