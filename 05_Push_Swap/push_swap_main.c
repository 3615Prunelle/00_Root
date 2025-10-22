/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 15:37:06 by sophie            #+#    #+#             */
/*   Updated: 2025/09/09 17:50:19 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// (argc == 2) means long string OR only one number
int	main(int argc, char **argv)
{
	int	arr_size;
	int	*numbers_arr;

	numbers_arr = NULL;
	if (argc < 2)
	{
		clean_early_exit("", NULL);
	}
	else if (argc == 2)
	{
		numbers_arr = two_argv(argv[1], numbers_arr, &arr_size);
	}
	else if (argc > 2)
	{
		numbers_arr = above_two_argv(argv, argc, numbers_arr, &arr_size);
	}
	check_array(numbers_arr, &arr_size);
	return (0);
}

int	*two_argv(char *input, int *numbers_arr, int *arr_size)
{
	if (is_numerical_only(input))
	{
		*arr_size = count_numbers(input);
		if (*arr_size == 1)
			clean_early_exit("", NULL);
		numbers_arr = ft_calloc(sizeof(int), *arr_size);
		numbers_arr = string_to_int_array(input, numbers_arr);
	}
	else
		clean_early_exit(ERROR_MSG, NULL);
	return (numbers_arr);
}

// i = 1 car un des args sera a.out donc on compte à partir du 1
int	*above_two_argv(char **inputs, int argc, int *numbers_arr, int *arr_size)
{
	int	i;

	i = 1;
	*arr_size = 0;
	while (argc > 1)
	{
		if (is_numerical_only(inputs[i]))
		{
			(*arr_size)++;
			argc--;
			i++;
			continue ;
		}
		else
			clean_early_exit(ERROR_MSG, numbers_arr);
	}
	numbers_arr = malloc(sizeof(int) * *arr_size);
	i = 0;
	while (i < *arr_size)
	{
		numbers_arr[i] = ft_atoi_check_long(inputs[i + 1], numbers_arr);
		i++;
	}
	return (numbers_arr);
}

// Renvoi d'un "" car aucune action si numbers already sorted
// INT_MIN et INT_MAX are checked in atoi
void	check_array(int *numbers_arr, int *arr_size)
{
	int	i;

	i = 0;
	if (is_number_repeat(numbers_arr, *arr_size))
		clean_early_exit(ERROR_MSG, numbers_arr);
	if (is_sorted(numbers_arr, *arr_size))
		clean_early_exit("", numbers_arr);
	struct_config(numbers_arr, arr_size);
}
