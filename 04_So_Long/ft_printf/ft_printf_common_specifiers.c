/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_common_specifiers.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sophie <sophie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:25:57 by schappuy          #+#    #+#             */
/*   Updated: 2025/08/22 15:06:33 by sophie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	c_specifier(int fd, char c)
{
	write(fd, &c, 1);
	return (1);
}

int	s_specifier(int fd, char *c)
{
	int	size;

	if (!c)
	{
		write(1, "(null)", 6);
		return (6);
	}
	size = ft_strlen(c);
	write(fd, c, size);
	return (size);
}

int	d_and_i_specifier(int fd, int i)
{
	char	*itoa_conv;
	int		length_itoa;

	itoa_conv = ft_itoa(i);
	length_itoa = ft_strlen(itoa_conv);
	write(fd, itoa_conv, length_itoa);
	free(itoa_conv);
	return (length_itoa);
}

unsigned int	u_specifier(int fd, unsigned int i)
{
	char		c;
	static int	count;

	count = 0;
	if (i / 10)
		u_specifier(fd, i / 10);
	c = (i % 10) + '0';
	write(fd, &c, 1);
	count++;
	return (count);
}
