/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_algorithms.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sophie <sophie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:05:12 by sophie            #+#    #+#             */
/*   Updated: 2025/08/20 14:27:37 by sophie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// pas mis le 1er 'if (a_b->stack_a->next->index == 1)' car si on arrive ici,
// c'est que next->next->index est 2 = les nombres sont dans l'ordre
void	sort_3(t_2stacks *a_b, int *ops_counter)
{
	if (a_b->stack_a->index == 0)
	{
		if (a_b->stack_a->next->index == 2)
		{
			swap_a(a_b, ops_counter);
			rotate_a(a_b, ops_counter);
		}
	}
	if (a_b->stack_a->index == 1)
	{
		if (a_b->stack_a->next->index == 0)
			swap_a(a_b, ops_counter);
		else if (a_b->stack_a->next->index == 2)
			reverse_rotate_a(a_b, ops_counter);
	}
	if (a_b->stack_a->index == 2)
	{
		if (a_b->stack_a->next->index == 0)
			rotate_a(a_b, ops_counter);
		else if (a_b->stack_a->next->index == 1)
		{
			rotate_a(a_b, ops_counter);
			swap_a(a_b, ops_counter);
		}
	}
}

// If lowest number position 0, only last push b necessary
// push_b = mettre smallest dans stack b et trier le reste avec sort_3
void	sort_4(t_2stacks *a_b, int *ops_counter)
{
	if (a_b->stack_a->next->index == 0)
	{
		swap_a(a_b, ops_counter);
	}
	if (a_b->stack_a->next->next->index == 0)
	{
		rotate_a(a_b, ops_counter);
		rotate_a(a_b, ops_counter);
	}
	if (a_b->stack_a->next->next->next->index == 0)
	{
		reverse_rotate_a(a_b, ops_counter);
	}
	push_b(a_b, ops_counter);
	add_idx_till_5(a_b->stack_a);
	sort_3(a_b, ops_counter);
	push_a(a_b, ops_counter);
}

// If lowest number position 0, only last push b necessary
// push_b = mettre smallest dans stack b et trier le reste avec sort4 puis sort3
void	sort_5(t_2stacks *a_b, int *ops_counter)
{
	if (a_b->stack_a->next->index == 0)
	{
		swap_a(a_b, ops_counter);
	}
	if (a_b->stack_a->next->next->index == 0)
	{
		rotate_a(a_b, ops_counter);
		rotate_a(a_b, ops_counter);
	}
	if (a_b->stack_a->next->next->next->index == 0)
	{
		reverse_rotate_a(a_b, ops_counter);
		reverse_rotate_a(a_b, ops_counter);
	}
	if (a_b->stack_a->next->next->next->next->index == 0)
	{
		reverse_rotate_a(a_b, ops_counter);
	}
	push_b(a_b, ops_counter);
	add_idx_till_5(a_b->stack_a);
	sort_4(a_b, ops_counter);
	push_a(a_b, ops_counter);
}

// Uniquement pour les fonctions <= 5 params
// free(stack_compare) mis dans loop plutôt qu'à la fin car mem leaks
t_node	*add_idx_till_5(t_node *stack)
{
	int		lower_numbers_counter;
	t_node	*stack_compare;
	t_node	*looping_ptr;

	stack_compare = malloc(sizeof(t_node));
	looping_ptr = stack;
	stack_compare->content = looping_ptr->content;
	stack_compare->next = looping_ptr->next;
	while (looping_ptr != NULL)
	{
		free(stack_compare);
		stack_compare = stack;
		lower_numbers_counter = 0;
		while (stack_compare != NULL)
		{
			if (*(int *)looping_ptr->content > *(int *)stack_compare->content)
				lower_numbers_counter++;
			stack_compare = stack_compare->next;
		}
		looping_ptr->index = lower_numbers_counter;
		looping_ptr = looping_ptr->next;
	}
	return (stack);
}

// a_b->stack_a->index & bit_mask = Transférer pairs dans stack b (last bit 0)
void	sort_above_5(t_2stacks *a_b, int *ops_counter, int *arr_size,
		int highest_nb)
{
	int	i;
	int	bit_mask;

	bit_mask = 1;
	while (true)
	{
		i = 0;
		while ((a_b->stack_a != NULL) && (i < *arr_size))
		{
			if (a_b->stack_a->index > highest_nb)
				highest_nb = a_b->stack_a->index;
			if (!(a_b->stack_a->index & bit_mask))
				push_b(a_b, ops_counter);
			else
				rotate_a(a_b, ops_counter);
			i++;
		}
		while (a_b->stack_b != NULL)
			push_a(a_b, ops_counter);
		bit_mask *= 2;
		if (bit_mask > highest_nb)
			break ;
	}
	return ;
}
