/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sophie <sophie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:34:53 by schappuy          #+#    #+#             */
/*   Updated: 2025/08/22 17:27:53 by sophie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* Version classique sans fd
Quand elle est appelée, elle appelle print_to_fd et lui donne
la sortie standard en param pour que tout marche comme avant
NB : sortie standard = stdout = 1 (interchangeables) */
void	ft_printf(const char *string, ...)
{
	va_list	ptr_string;
	int		fd;

	fd = 1;
	va_start(ptr_string, string);
	print_to_fd(fd, string, ptr_string);
	va_end(ptr_string);
}

/* C'est cette fonction qui sera appelée, quand besoin d'afficher
sur un fd (quasi-copie de l'officielle fprintf)
Et elle appelle la fonction intermédiataire print_to_fd
qui accepte un FD comme param
Donc bien penser à lui donner (par ex fd 2 = sortie erreur, etc)
TO DO : updater le .h avec ces deux nouvelles fonctions
WHen done testing, use it in push_swap */
void	ft_dprintf(int fd, const char *string, ...)
{
	va_list	ptr_string;

	va_start(ptr_string, string);
	print_to_fd(fd, string, ptr_string);
	va_end(ptr_string);
}

/*
Créé cette fonction pour push_swap, et les autres programmes qui ont besoin
d'afficher une string sur une autre sortie que 1
(fd 1 = sortie standard, qui était jusque là dans tous les write)
NB: S'il s'agit d'une string simple sans %, je peux aussi utiliser ft_putstr_fd
Le 1er paramètre (fd) peut donc désormais être 2
(sortie erreur standard = fd 2) par exemple.
*/
int	print_to_fd(int fd, const char *string, va_list ptr_string)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (string[i] != '\0')
	{
		if (string[i] == '%')
		{
			j += specifiers_call(fd, string[i + 1], ptr_string);
			i += 2;
		}
		else
		{
			write(fd, &string[i], 1);
			i++;
			j++;
		}
	}
	return (j);
}

int	specifiers_call(int fd, char c, va_list ptr_string)
{
	int	j;

	j = 0;
	if (c == 'c')
		j = c_specifier(fd, (char)(va_arg(ptr_string, int)));
	else if (c == 's')
		j = s_specifier(fd, va_arg(ptr_string, char *));
	else if (c == 'p')
		j = p_specifier(fd, va_arg(ptr_string, void *));
	else if (c == 'd')
		j = d_and_i_specifier(fd, va_arg(ptr_string, int));
	else if (c == 'i')
		j = d_and_i_specifier(fd, va_arg(ptr_string, int));
	else if (c == 'u')
		j = u_specifier(fd, va_arg(ptr_string, unsigned int));
	else if (c == 'x')
		j = x_specifier(fd, (va_arg(ptr_string, unsigned int)), HEXA_MIN);
	else if (c == 'X')
		j = x_specifier(fd, (va_arg(ptr_string, unsigned int)), HEXA_MAJ);
	else if (c == '%')
		j = c_specifier(fd, '%');
	return (j);
}
