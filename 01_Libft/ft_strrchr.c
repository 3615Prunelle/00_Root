/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:41:19 by schappuy          #+#    #+#             */
/*   Updated: 2024/12/16 19:44:45 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			j = i;
		}
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	if (j == -1)
		return (0);
	return ((char *)&s[j]);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char o[] = "Ptr to last occurrence of char c in str s";
// 	int z = 'l';

// 	char *oo = ft_strrchr(o ,z);
// 	char *zz = strrchr(o, z);

// 	printf("My Ft:  	%s\n", oo);
// 	printf("Strrchr:	%s\n", zz);

// 	return (0);
// }
