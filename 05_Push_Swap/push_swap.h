/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 15:47:23 by sophie            #+#    #+#             */
/*   Updated: 2025/09/09 15:33:57 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

// ⚪ #define
# define ERROR_MSG "Error\n"

// ⚪ #include
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// ⚪ #include from other 42 projects
# include <ft_printf.h>
# include <libft.h>

// ⚪ Structs
// changer void* pour int* instead of void ?
typedef struct node
{
	void		*content;
	int			index;
	struct node	*next;
}				t_node;

typedef struct stacks
{
	t_node		*stack_a;
	t_node		*stack_b;
}				t_2stacks;

// ⚪ Functions signatures - Pre_Stack Creation (Input Management & Check)
int				*two_argv(char *input, int *numbers_arr, int *arr_size);
int				*above_two_argv(char **inputs, int argc, int *numbers_arr,
					int *arr_size);
int				ft_atoi_check_long(char *s, int *numbers_arr);
int				count_numbers(char *s);
int				*string_to_int_array(char *s, int *numbers_arr);
bool			is_numerical_only(char *s);
void			check_array(int *numbers_arr, int *arr_size);
bool			is_number_repeat(int *numbers_arr, int arr_size);
bool			is_sorted(int *numbers_arr, int arr_size);

// ⚪ Post Stack Creation
t_node			*create_stack(t_node *stack, int *numbers_arr, int *arr_size);
void			struct_config(int *numbers_arr, int *arr_size);
t_2stacks		*algorithm_selection(t_2stacks *a_b, int *arr_size,
					int *ops_counter, int *numbers_arr);
t_node			*add_idx_above_5(int *numbers_arr, int *arr_size,
					t_node *stack);
t_node			*add_idx_till_5(t_node *stack);

// ⚪ Lst functions
t_node			*new_node(void *content);
t_node			*find_last_node(t_node *lst);
void			add_node_up(t_node **lst, t_node *new);
void			add_node_down(t_node **lst, t_node *new);
int				count_nodes(t_node *lst);

// ⚪ Algorithms
void			sort_3(t_2stacks *a_b, int *ops_counter);
void			sort_4(t_2stacks *a_b, int *ops_counter);
void			sort_5(t_2stacks *a_b, int *ops_counter);
void			sort_above_5(t_2stacks *a_b, int *ops_counter, int *arr_size,
					int highest_nb);

// ⚪ Operations
t_2stacks		*swap_a(t_2stacks *a_b, int *ops_counter);
// t_2stacks		*swap_b(t_2stacks *a_b, int *ops_counter);
// t_2stacks		*swap_a_b(t_2stacks *a_b, int *ops_counter);
t_2stacks		*push_a(t_2stacks *a_b, int *ops_counter);
t_2stacks		*push_b(t_2stacks *a_b, int *ops_counter);
t_2stacks		*rotate_a(t_2stacks *a_b, int *ops_counter);
// t_2stacks		*rotate_b(t_2stacks *a_b, int *ops_counter);
// t_2stacks		*rotate_a_b(t_2stacks *a_b, int *ops_counter);
t_2stacks		*reverse_rotate_a(t_2stacks *a_b, int *ops_counter);
// t_2stacks		*reverse_rotate_b(t_2stacks *a_b, int *ops_counter);
// t_2stacks		*reverse_rotate_a_b(t_2stacks *a_b, int *ops_counter);

// ⚪ Clean up functions
void			clean_early_exit(char *msg, int *numbers_arr);
void			free_nodes(t_2stacks *a_b);

// ⚪ Test functions
// void			print_sorted_stack(t_node *stack);
#endif
