/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sophie <sophie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:41:39 by schappuy          #+#    #+#             */
/*   Updated: 2025/08/20 16:44:58 by sophie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*pt_s1;
	unsigned char	*pt_s2;

	i = 0;
	pt_s1 = (unsigned char *)s1;
	pt_s2 = (unsigned char *)s2;
	while (i < n)
	{
		if (pt_s1[i] == pt_s2[i])
		{
			i++;
		}
		else
			return (pt_s1[i] - pt_s2[i]);
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char s1[] = "Test";
// 	char s2[] = "Tent";

// 	int oo = ft_memcmp(s1, s2, 2);
// 	int zz = memcmp(s1, s2, 2);

// 	printf("My Ft:	%d\n", oo);
// 	printf("Memcmp:	%d\n", zz);

// 	return (0);
// }
