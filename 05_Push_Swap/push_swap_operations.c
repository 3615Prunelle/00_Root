/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_operations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sophie <sophie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 17:20:00 by sophie            #+#    #+#             */
/*   Updated: 2025/08/03 18:04:21 by sophie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Malloc node2 pas nécessaire car used only here
// Toujours updater next avant toute opération
// addfront update next pour le newfirstnode (node2) + ptr du stack (head)
t_2stacks	*swap_a(t_2stacks *a_b, int *ops_counter)
{
	t_node	*backup_node1;
	t_node	*node2;

	ft_printf("sa\n");
	if ((a_b->stack_a == NULL) || (count_nodes(a_b->stack_a) == 1))
		return (a_b);
	backup_node1 = a_b->stack_a;
	node2 = a_b->stack_a->next;
	backup_node1->next = node2->next;
	add_node_up(&a_b->stack_a, node2);
	(*ops_counter)++;
	return (a_b);
}

// t_2stacks	*swap_b(t_2stacks *a_b, int *ops_counter)
// {
// 	t_node	*backup_node1;
// 	t_node	*node2;

// 	ft_printf("sb\n");
// 	if ((a_b->stack_b == NULL) || (count_nodes(a_b->stack_b) == 1))
// 		return (a_b);
// 	backup_node1 = a_b->stack_b;
// 	node2 = a_b->stack_b->next;
// 	backup_node1->next = node2->next;
// 	add_node_up(&a_b->stack_b, node2);
// 	(*ops_counter)++;
// 	return (a_b);
// }

// t_2stacks	*swap_a_b(t_2stacks *a_b, int *ops_counter)
// {
// 	ft_printf("ss\n");
// 	a_b = swap_a(a_b, ops_counter);
// 	a_b = swap_b(a_b, ops_counter);
// 	(*ops_counter)++;
// 	return (a_b);
// }

// NULL car count_nodes(a_b->stack_b) == 0 donnait des memory leaks
t_2stacks	*push_a(t_2stacks *a_b, int *ops_counter)
{
	t_node	*backup_node1b;

	ft_printf("pa\n");
	if (a_b->stack_b == NULL)
		return (a_b);
	backup_node1b = a_b->stack_b;
	a_b->stack_b = backup_node1b->next;
	add_node_up(&a_b->stack_a, backup_node1b);
	(*ops_counter)++;
	return (a_b);
}

t_2stacks	*push_b(t_2stacks *a_b, int *ops_counter)
{
	t_node	*backup_node1a;

	ft_printf("pb\n");
	if (a_b->stack_a == NULL)
		return (a_b);
	backup_node1a = a_b->stack_a;
	a_b->stack_a = backup_node1a->next;
	add_node_up(&a_b->stack_b, backup_node1a);
	(*ops_counter)++;
	return (a_b);
}

// The first element becomes the last one
t_2stacks	*rotate_a(t_2stacks *a_b, int *ops_counter)
{
	t_node	*backup_node1;
	t_node	*backup_node2;

	ft_printf("ra\n");
	if ((a_b->stack_a == NULL) || (a_b->stack_a->next == NULL))
		return (a_b);
	backup_node1 = a_b->stack_a;
	backup_node2 = a_b->stack_a->next;
	a_b->stack_a = backup_node2;
	add_node_down(&a_b->stack_a, backup_node1);
	backup_node1->next = NULL;
	(*ops_counter)++;
	return (a_b);
}

// // The first element becomes the last one
// t_2stacks	*rotate_b(t_2stacks *a_b, int *ops_counter)
// {
// 	t_node	*backup_node1;
// 	t_node	*backup_node2;

// 	ft_printf("rb\n");
// 	if ((a_b->stack_b == NULL) || (a_b->stack_b->next == NULL))
// 		return (a_b);
// 	backup_node1 = a_b->stack_b;
// 	backup_node2 = a_b->stack_b->next;
// 	a_b->stack_b = backup_node2;
// 	add_node_down(&a_b->stack_b, backup_node1);
// 	backup_node1->next = NULL;
// 	(*ops_counter)++;
// 	return (a_b);
// }

// // ra and rb at the same time
// t_2stacks	*rotate_a_b(t_2stacks *a_b, int *ops_counter)
// {
// 	ft_printf("rr\n");
// 	a_b = rotate_a(a_b, ops_counter);
// 	a_b = rotate_b(a_b, ops_counter);
// 	(*ops_counter)++;
// 	return (a_b);
// }

// Last element becomes the first one
// Condition d'arrêt next->next = avant dernier node
t_2stacks	*reverse_rotate_a(t_2stacks *a_b, int *ops_counter)
{
	t_node	*loop_ptr;
	t_node	*last_node;

	ft_printf("rra\n");
	loop_ptr = a_b->stack_a;
	if ((a_b->stack_a == NULL) || (a_b->stack_a->next == NULL))
		return (a_b);
	while (loop_ptr->next->next != NULL)
	{
		loop_ptr = loop_ptr->next;
	}
	last_node = loop_ptr->next;
	loop_ptr->next = NULL;
	last_node->next = a_b->stack_a;
	a_b->stack_a = last_node;
	(*ops_counter)++;
	return (a_b);
}

// t_2stacks	*reverse_rotate_b(t_2stacks *a_b, int *ops_counter)
// {
// 	t_node	*loop_ptr;
// 	t_node	*last_node;

// 	ft_printf("rrb\n");
// 	loop_ptr = a_b->stack_b;
// 	if ((a_b->stack_b == NULL) || (a_b->stack_b->next == NULL))
// 		return (a_b);
// 	while (loop_ptr->next->next != NULL)
// 	{
// 		loop_ptr = loop_ptr->next;
// 	}
// 	last_node = loop_ptr->next;
// 	loop_ptr->next = NULL;
// 	last_node->next = a_b->stack_b;
// 	a_b->stack_b = last_node;
// 	(*ops_counter)++;
// 	return (a_b);
// }

// // rra and rrb at the same time
// t_2stacks	*reverse_rotate_a_b(t_2stacks *a_b, int *ops_counter)
// {
// 	ft_printf("rrr\n");
// 	a_b = reverse_rotate_a(a_b, ops_counter);
// 	a_b = reverse_rotate_b(a_b, ops_counter);
// 	(*ops_counter)++;
// 	return (a_b);
// }
