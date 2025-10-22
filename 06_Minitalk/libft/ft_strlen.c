/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:39:02 by schappuy          #+#    #+#             */
/*   Updated: 2025/05/05 23:11:30 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	test[] = "Length of a string";

// 	size_t oo = ft_strlen(test);
// 	size_t zz = strlen(test);

// 	printf("My Ft :		%s has %zu characters\n", test, oo);
// 	printf("Strlen :	%s has %zu characters\n", test, zz);

// 	return (0);
// }
