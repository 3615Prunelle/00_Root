/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hexa_specifiers.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sophie <sophie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:25:57 by schappuy          #+#    #+#             */
/*   Updated: 2025/08/22 15:06:33 by sophie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	p_specifier(int fd, void *p)
{
	uintptr_t	pos_ptr;
	int			count;

	if (!p)
		return (write(fd, "(nil)", 5));
	pos_ptr = (uintptr_t)p;
	write(fd, "0x", 2);
	count = x_specifier(fd, (unsigned long)pos_ptr, "0123456789abcdef");
	return (count + 2);
}

int	x_specifier(int fd, unsigned long long i, char *hexa)
{
	static int	count;
	char		c;

	count = 0;
	if (i / 16)
		x_specifier(fd, i / 16, hexa);
	c = hexa[i % 16];
	write(fd, &c, 1);
	count++;
	return (count);
}
