/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_input_management.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 17:33:43 by sophie            #+#    #+#             */
/*   Updated: 2025/09/09 15:46:14 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

bool	is_numerical_only(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if ((s[i] >= '0' && s[i] <= '9') || s[i] == '+' || s[i] == '-'
			|| s[i] == ' ')
		{
			if ((s[i] == '+' || s[i] == '-')
				&& !(s[i + 1] >= '0' && s[i + 1] <= '9'))
			{
				return (false);
			}
			i++;
			continue ;
		}
		return (false);
	}
	return (true);
}

// Free strings_array car alloué dans ft_split
int	count_numbers(char *s)
{
	int		count;
	char	**strings_array;
	int		i;

	count = 0;
	strings_array = ft_split(s, ' ');
	i = 0;
	while (strings_array[i] != NULL)
	{
		count++;
		i++;
	}
	i = 0;
	while (i < count)
	{
		free(strings_array[i]);
		i++;
	}
	free(strings_array);
	return (count);
}

// NULL Car ft_split a mis un \0 à la dernière array
int	*string_to_int_array(char *s, int *numbers_arr)
{
	char	**strings_array;
	int		i;

	strings_array = ft_split(s, ' ');
	i = 0;
	while (strings_array[i] != NULL)
	{
		numbers_arr[i] = ft_atoi_check_long(strings_array[i], numbers_arr);
		i++;
	}
	i = 0;
	while (strings_array[i] != NULL)
	{
		free(strings_array[i]);
		i++;
	}
	free(strings_array);
	return (numbers_arr);
}

// Store the result in long int to check if it's within INT_MIN INT_MAX size
int	ft_atoi_check_long(char *s, int *numbers_arr)
{
	int			i;
	long int	tot;
	int			sign;

	i = 0;
	tot = 0;
	sign = 1;
	while (((s[i] >= 9) && (s[i] <= 13)) || (s[i] == ' '))
		i++;
	if ((s[i] == '+') || (s[i] == '-'))
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while ((s[i] >= '0') && (s[i] <= '9'))
	{
		tot = tot * 10 + s[i] - '0';
		i++;
	}
	if ((tot * sign < INT_MIN) || (tot * sign > INT_MAX))
		clean_early_exit(ERROR_MSG, numbers_arr);
	return (tot * sign);
}

bool	is_sorted(int *numbers_arr, int arr_size)
{
	int	highest_nb;

	highest_nb = INT_MIN;
	while ((numbers_arr) && (arr_size > 0))
	{
		if (*numbers_arr >= highest_nb)
		{
			highest_nb = *numbers_arr;
			numbers_arr++;
			arr_size--;
			continue ;
		}
		else
			return (false);
	}
	return (true);
}
