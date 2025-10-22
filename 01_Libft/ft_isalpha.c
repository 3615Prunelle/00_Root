/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sophie <sophie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:40:52 by schappuy          #+#    #+#             */
/*   Updated: 2025/08/20 14:09:50 by sophie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}
// Smart hint by Antoine Forty2 : Marche aussi en une seule ligne (sans le if):
// return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));

// #include <stdio.h>

// int main(void)
// {
// 	unsigned char test = '*';
// 	printf("%d\n", ft_isalpha(test));
// 	return (0);
// }
