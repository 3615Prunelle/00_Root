/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:40:26 by schappuy          #+#    #+#             */
/*   Updated: 2025/10/25 17:52:21 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *srce, size_t siz)
{
	size_t				i;
	unsigned char		*ptr_dest;
	const unsigned char	*ptr_srce;

	if (!dest && !srce)
		return (NULL);
	ptr_dest = (unsigned char *)dest;
	ptr_srce = (const unsigned char *)srce;
	i = 0;
	while (i < siz)
	{
		ptr_dest[i] = ptr_srce[i];
		i++;
	}
	return (dest);
}

// #include <stdio.h>
// #include <string.h>

// int main(void)
// {
// 	char s[] = "99999";
// 	char d[] = "111111";

// 	char *ii = ft_memcpy(d, s, 3);
// 	char *oo = memcpy(d, s, 3);

// 	printf("My Ft :     %s\n", ii);
// 	printf("Memcpy :    %s\n", oo);
// 	return (0);
// }
