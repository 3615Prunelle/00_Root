/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sophie <sophie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:40:33 by schappuy          #+#    #+#             */
/*   Updated: 2025/08/20 14:11:28 by sophie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}

// Smart hint by Antoine Forty2 : Marche aussi en une seule ligne (sans le if):
// return (c >= 32 && c <= 126);

// #include <stdio.h>
// #include <ctype.h>

// int main(void)
// {
// 	unsigned char test = 127;

// 	printf("Mine:		%d\n", ft_isprint(test));
// 	printf("Official:	%d\n", isprint(test));
// 	return (0);
// }
