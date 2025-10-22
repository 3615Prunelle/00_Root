/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sophie <sophie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:59:46 by schappuy          #+#    #+#             */
/*   Updated: 2025/08/20 16:47:55 by sophie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}

// void	ft_toupper3(unsigned int index, char *str)
// {
// 	char maj = ft_toupper(str[index]);
// 	str[index] = maj;
// }

// #include <stdio.h>

// int	main(void)
// {
// 	char before[] = "Each char will be changed in memory";

// 	ft_striteri(before, ft_toupper3);

// 	printf("%s", before);

// 	return (0);
// }
