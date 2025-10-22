/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:40:10 by schappuy          #+#    #+#             */
/*   Updated: 2025/01/24 16:59:59 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int constante, size_t taille)
{
	unsigned char	*ptr_s;
	size_t			i;

	ptr_s = (unsigned char *)str;
	i = 0;
	while (i < taille)
	{
		ptr_s[i] = (unsigned char)constante;
		i++;
	}
	return (str);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char min[] = "Fills the first s bytes with int c";
// 	char off[] = "Doesn't create a new string";
// 	int	s = 2;
// 	int	n = 'c';

// 	void *mine = ft_memset(min, n, s);
// 	void *offi = memset(off, n, s);

// 	printf("My Ft :		%p\n", mine);
// 	printf("Memset :	%p\n", offi);

// 	return (0);
// }
