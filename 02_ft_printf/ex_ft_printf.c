/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sophie <sophie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:34:53 by schappuy          #+#    #+#             */
/*   Updated: 2025/08/05 21:24:16 by sophie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *string, ...)
{
	int			i;
	int			j;
	va_list		ptr_string;

	va_start (ptr_string, string);
	i = 0;
	j = 0;
	while (string[i] != '\0')
	{
		if (string[i] == '%')
		{
			j += specifiers_call(string[i + 1], ptr_string);
			i += 2;
		}
		else
		{
			write (1, &string[i], 1);
			i++;
			j++;
		}
	}
	va_end (ptr_string);
	return (j);
}

int	specifiers_call(char c, va_list ptr_string)
{
	int	j;

	j = 0;
	if (c == 'c')
		j = c_specifier ((char)(va_arg(ptr_string, int)));
	else if (c == 's')
		j = s_specifier(va_arg(ptr_string, char *));
	else if (c == 'p')
		j = p_specifier(va_arg(ptr_string, void *));
	else if (c == 'd')
		j = d_and_i_specifier(va_arg(ptr_string, int));
	else if (c == 'i')
		j = d_and_i_specifier (va_arg(ptr_string, int));
	else if (c == 'u')
		j = u_specifier (va_arg(ptr_string, unsigned int));
	else if (c == 'x')
		j = x_specifier ((va_arg(ptr_string, unsigned int)), HEXA_MIN);
	else if (c == 'X')
		j = x_specifier ((va_arg(ptr_string, unsigned int)), HEXA_MAJ);
	else if (c == '%')
		j = c_specifier('%');
	return (j);
}

// int	main(int argc, char **argv)
// {
// 	if(argc == 2)
// 	{
// 		ft_printf("Here's your string : %s\n", argv[1]);
// 	}
// 	return(0);
// }
