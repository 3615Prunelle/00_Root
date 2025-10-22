/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:41:05 by schappuy          #+#    #+#             */
/*   Updated: 2024/12/16 19:39:32 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *str, size_t siz)
{
	char	*cha;
	size_t	i;

	cha = str;
	i = 0;
	while (i < siz)
	{
		cha[i] = '\0';
		i++;
	}
}

// #include <stdio.h>

// int	main(void)
// {
// 	char test[] = "HHHHHHHH";

// 	ft_bzero(test,3);

// 	return (0);
// }
