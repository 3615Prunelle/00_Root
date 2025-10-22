/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:39:02 by schappuy          #+#    #+#             */
/*   Updated: 2025/05/05 23:25:27 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_size(int n)
{
	size_t	size;

	if (n > 0)
		size = 0;
	else
		size = 1;
	while (n)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	num;
	size_t	size;

	num = n;
	size = get_size(n);
	if (n < 0)
		num = -num;
	str = (char *)malloc(size + 1);
	if (!str)
		return (NULL);
	str[size--] = '\0';
	while (num > 0)
	{
		str[size--] = num % 10 + '0';
		num /= 10;
	}
	if (size == 0 && str[1] == '\0')
		str[size] = '0';
	else if (size == 0 && str[1])
		str[size] = '-';
	return (str);
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
