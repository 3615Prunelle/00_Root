/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sophie <sophie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:00:00 by schappuy          #+#    #+#             */
/*   Updated: 2025/08/20 16:47:51 by sophie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*newstring;
	size_t	i;

	i = 0;
	newstring = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!newstring)
		return (NULL);
	while (s[i])
	{
		newstring[i] = s[i];
		i++;
	}
	newstring[i] = '\0';
	return (newstring);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char test[] = "test";

// 	char *dup = ft_strdup(test);
// 	char *dup_off = strdup(test);

// 	printf("%s", dup);
// 	printf("%s", dup_off);

// 	return (0);
// }
