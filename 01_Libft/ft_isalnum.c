/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sophie <sophie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:40:57 by schappuy          #+#    #+#             */
/*   Updated: 2025/08/20 16:42:29 by sophie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(unsigned char c)
{
	if ((c >= 48 && c <= 57) || ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)))
		return (c);
	else
		return (0);
}
/*
Smart hint by Antoine Forty2 :Marche aussi en une seule ligne (sans le if):
return ((c >= 48 && c <= 57)||((c >= 65 && c <= 90)||(c >= 97 && c <= 122)));
 */

// #include <stdio.h>

// int	main(void)
// {
// 	unsigned char	test = '1';

// 	printf("%d\n", ft_isalnum(test));
// 	return (0);
// }
