/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sophie <sophie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:40:45 by schappuy          #+#    #+#             */
/*   Updated: 2025/08/20 14:10:46 by sophie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

// Smart hint by Antoine Forty2 : Marche aussi en une seule ligne (sans le if):
// return (c >= 0 && c <= 127);

// #include <stdio.h>

// int main(void)
// {
// 	int test = 255;
// 	printf("%d", ft_isascii(test));
// 	return (0);
// }
