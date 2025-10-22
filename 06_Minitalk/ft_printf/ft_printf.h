/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sophie <sophie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:07:11 by schappuy          #+#    #+#             */
/*   Updated: 2025/08/22 17:27:53 by sophie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdint.h>

# include <libft.h>

# define HEXA_MIN "0123456789abcdef"
# define HEXA_MAJ "0123456789ABCDEF"

// Main Functions
void			ft_printf(const char *string, ...);
void			ft_dprintf(int fd, const char *string, ...);
int				print_to_fd(int fd, const char *string, va_list ptr_string);

// Helpers
int				specifiers_call(int fd, char c, va_list ptr_string);
int				c_specifier(int fd, char c);
int				s_specifier(int fd, char *c);
int				d_and_i_specifier(int fd, int i);
unsigned int	u_specifier(int fd, unsigned int i);
int				p_specifier(int fd, void *p);
int				x_specifier(int fd, unsigned long long i, char *hexa);

#endif
