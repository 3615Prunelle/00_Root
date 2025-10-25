/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:38:22 by schappuy          #+#    #+#             */
/*   Updated: 2025/10/25 17:49:45 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
The  memchr()  function  scans  the initial n bytes of the memory area pointed
to by s for the first instance of c.  Both c and the bytes of the memory area
pointed to by s are  interpreted as unsigned char.
The memchr() function returns a pointer to the matching byte or NULL if the
character does not occur in the given memory area.
*/

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*pts;
	unsigned char	cc;

	i = 0;
	pts = (unsigned char *)s;
	cc = (unsigned char)c;
	while (i < n)
	{
		if (pts[i] != cc)
			i++;
		else
			return (&pts[i]);
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char *s = "Test";
// 	int c = 'e';
// 	size_t n = 3;

// 	char *oo = ft_memchr(s, c, n);
// 	char *zz = memchr(s, c, n);

// 	printf("My Ft:	%p\n", oo);
// 	printf("Memchr:	%p\n", zz);

// 	return (0);
// }
