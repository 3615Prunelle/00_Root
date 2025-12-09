/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:41:29 by schappuy          #+#    #+#             */
/*   Updated: 2025/12/09 16:39:55 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i])
	{
		i++;
		if ((s1[i] == '\0') && (s2[i] == '\0'))
			return (0);
	}
	return (s1[i] - s2[i]);
}

// int	main(void)
// {
// 	char t1[] = "Zai";
// 	char t2[] = "Zai";

// 	int oo = ft_strcmp(t1, t2);
// 	int zz = strcmp(t1, t2);

// 	printf("My Ft:\t\t%d\n", oo);
// 	printf("Strcmp:\t\t%d\n", zz);

// 	return (0);
// }
