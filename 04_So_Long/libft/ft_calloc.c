/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sophie <sophie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 19:35:56 by schappuy          #+#    #+#             */
/*   Updated: 2025/08/20 16:41:00 by sophie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	while (i < nmemb * size)
	{
		ptr[i] = '\0';
		i++;
	}
	return (ptr);
}

// #include <stdio.h>

// int	main(void)
// {
// 	size_t	nn = 2;
// 	size_t	ss = 3;

// 	unsigned char* pp = ft_calloc(nn, ss);
// 	unsigned char* off = calloc(nn, ss);

// 	printf("My Calloc pointer :	%p\n", pp);
// 	printf("Official Calloc :	%p\n", off);
// 	return (0);
// }
