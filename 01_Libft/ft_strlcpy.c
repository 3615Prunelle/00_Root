/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:05:32 by schappuy          #+#    #+#             */
/*   Updated: 2025/01/24 17:01:11 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (src[i] != '\0')
	{
		i++;
	}
	if (size == 0)
	{
		return (i);
	}
	while (j < (size - 1) && src[j] != '\0')
	{
		dst[j] = src[j];
		j++;
	}
	dst[j] = '\0';
	return (i);
}

// #include <string.h>
// #include <stdio.h>

// int	main(void)
// {
// 	char my_d[] = "Returns total length of source string, not written bytes";
// 	char off_d[] = "Returns total length of source string, not written bytes";
// 	char s[] = "Copy source in dest if there is room";

// 	size_t oo = ft_strlcpy(my_d, s, 40);
// 	size_t zz = strlcpy(off_d, s, 40);

// 	printf("My ft returns:		%zu\n", oo);
// 	printf("Strlcpy returns:	%zu\n", zz);

// 	return (0);
// }
