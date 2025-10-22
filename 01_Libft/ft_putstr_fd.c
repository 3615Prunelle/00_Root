/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sophie <sophie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:59:46 by schappuy          #+#    #+#             */
/*   Updated: 2025/08/20 16:47:16 by sophie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

/*
Smart hint by Antoine Forty2:
Utiliser ft_strlen et write(fd, string, length) - Pas besoin de loop
*/

// int	main(void)
// {
// 	char *s = "Fraise Tagada";
// 	int fd = 2;

// 	ft_putstr_fd(s, fd);

// 	return (0);
// }
