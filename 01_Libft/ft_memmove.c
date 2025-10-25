/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:40:20 by schappuy          #+#    #+#             */
/*   Updated: 2025/10/25 17:52:59 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *srce, size_t siz)
{
	size_t	i;

	i = 0;
	if (!dest && !srce)
		return (NULL);
	if ((unsigned char *)dest > (const unsigned char *)srce)
	{
		while (siz > 0)
		{
			siz--;
			((unsigned char *)dest)[siz] = ((const unsigned char *)srce)[siz];
		}
	}
	else
	{
		while (i < siz)
		{
			((unsigned char *)dest)[i] = ((const unsigned char *)srce)[i];
			i++;
		}
	}
	return (dest);
}

// int main(void)
// {
// 	char s[] = "Copy n bytes to temp, overlap ok, returns pointer to dest";
// 	char my_dest[20] = "";
// 	char off_dest[20] = "";
// 	size_t size = 7;

// 	char *oo = ft_memmove(my_dest, s, size);
// 	char *zz = memmove(off_dest, s, size);

// 	printf("My Ft :     %s\n", oo);
// 	printf("Memmove :   %s\n", zz);
// 	return (0);
// }
