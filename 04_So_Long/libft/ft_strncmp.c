/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:41:29 by schappuy          #+#    #+#             */
/*   Updated: 2024/12/16 19:44:56 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && ((s1[i] != '\0') || (s2[i] != '\0')))
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char t1[] = "Zai Zai Zai Zai";
// 	char t2[] = "Zaik";
// 	size_t	t = 3;

// 	int oo = ft_strncmp(t1, t2, t);
// 	int zz = strncmp(t1, t2, t);

// 	printf("My Ft:  	%d\n", oo);
// 	printf("Strncmp:	%d\n", zz);

// 	return (0);
// }
