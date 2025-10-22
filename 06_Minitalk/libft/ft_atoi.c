/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:52:10 by schappuy          #+#    #+#             */
/*   Updated: 2024/12/16 19:39:22 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	tot;
	int	sign;

	i = 0;
	tot = 0;
	sign = 1;
	while (((nptr[i] >= 9) && (nptr[i] <= 13)) || (nptr[i] == ' '))
	{
		i++;
	}
	if ((nptr[i] == '+') || (nptr[i] == '-'))
	{
		if (nptr[i] == '-')
		{
			sign = -1;
		}
		i++;
	}
	while ((nptr[i] >= '0') && (nptr[i] <= '9'))
	{
		tot = tot * 10 + nptr[i] - '0';
		i++;
	}
	return (tot * sign);
}

// #include <stdio.h>
// #include <stdlib.h>

// int main(void)
// {
// 	const char u[] = "++123a";
// 	const char v[] = "--123a";
// 	const char w[] = "-+123a";
// 	const char x[] = "+-123a";
// 	const char y[] = "   123a";
// 	const char z[] = ".123a";

// 	printf("My Ft:	%i\n", ft_atoi(u));
// 	printf("Atoi:	%i\n\n", atoi(u));
// 	printf("My Ft:	%i\n", ft_atoi(v));
// 	printf("Atoi:	%i\n\n", atoi(v));
// 	printf("My Ft:	%i\n", ft_atoi(w));
// 	printf("Atoi:	%i\n\n", atoi(w));
// 	printf("My Ft:	%i\n", ft_atoi(x));
// 	printf("Atoi:	%i\n\n", atoi(x));
// 	printf("My Ft:	%i\n", ft_atoi(y));
// 	printf("Atoi:	%i\n\n", atoi(y));
// 	printf("My Ft:	%i\n", ft_atoi(z));
// 	printf("Atoi:	%i\n\n", atoi(z));
// 	return (0);
// }
