/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:37:05 by schappuy          #+#    #+#             */
/*   Updated: 2024/12/16 19:44:38 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if ((c >= 'A') && (c <= 'Z'))
	{
		c = c + 32;
	}
	return (c);
}

// #include <ctype.h>
// #include <stdio.h>

// int	main(void)
// {
// 	int	test = 'Z';
// 	int lo = ft_tolower(test);

// 	printf("%c\n", lo);
// 	printf("%c\n", tolower(lo));
// 	return (0);
// }
