/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:39:29 by schappuy          #+#    #+#             */
/*   Updated: 2024/12/12 20:28:23 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *srce, size_t size)
{
	size_t	i;
	size_t	length_s;
	size_t	length_d;

	i = 0;
	length_s = ft_strlen(srce);
	length_d = ft_strlen(dest);
	if (size <= length_d)
		return (size + length_s);
	while ((srce[i] != '\0') && (length_d + i < size - 1))
	{
		dest[length_d + i] = srce[i];
		i++;
	}
	dest[length_d + i] = '\0';
	return (length_d + length_s);
}

// #include <stdio.h>
// #include <string.h>

// int main(void)
// {
// 	char sr[] = "Returns total length it tried to create, not written bytes";
// 	char d_myft[20] = "Appends source to dest if there is room";
// 	char d_offcl[20] = "Appends source to dest if there is room";

// 	size_t oo = ft_strlcat(d_myft,sr,10);
// 	size_t zz = strlcat(d_offcl,sr, 10);

// 	printf("My ft :     %zu\n", oo);
// 	printf("Strlcat :   %zu\n", zz);

// 	return (0);
// }
