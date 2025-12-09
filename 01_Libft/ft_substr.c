/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:26:41 by schappuy          #+#    #+#             */
/*   Updated: 2025/12/09 16:01:15 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub;

	i = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	sub = ft_calloc(len + 1, sizeof(char));
	if (!sub)
		return (NULL);
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	return (sub);
}

// int	main(void)
// {
// 	char s[] = "Creates a string of len size from start index";
// 	unsigned int start = 2;
// 	size_t len = 4;

// 	char *zz = ft_substr(s, start, len);

// 	// printf("%p\n", zz);
// 	printf("%s\n", zz);

// 	return (0);
// }
