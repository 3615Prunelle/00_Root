/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sophie <sophie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:40:40 by schappuy          #+#    #+#             */
/*   Updated: 2025/08/20 14:11:07 by sophie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

// Smart hint by Antoine Forty2 : Marche aussi en une seule ligne (sans le if):
// return (c >= '0' && c <= '9');

// #include <stdio.h>

// int main(void)
// {
// 	unsigned char test = '8';
// 	printf("%d", ft_isdigit(test));
// 	return (0);
// }
