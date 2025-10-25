/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:41:39 by schappuy          #+#    #+#             */
/*   Updated: 2025/10/25 17:51:49 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* The  memcmp()  function  compares the first n bytes (each interpreted as
unsigned char) of the memory areas s1 and s2.
The memcmp() function returns an integer less than, equal to, or  greater  than
zero  if  the first  n bytes of s1 is found, respectively, to be less than,
to match, or be greater than the first n bytes of s2.
For a nonzero return value, the sign is determined by the sign of the
difference between the first pair of bytes (interpreted as unsigned char)
that differ in s1 and s2.
If n is zero, the return value is zero.
 */

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
