/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:59:46 by schappuy          #+#    #+#             */
/*   Updated: 2025/02/05 23:00:10 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*new;

	i = 0;
	if (!s || !f)
		return (NULL);
	new = ft_calloc((ft_strlen(s) + 1), sizeof(char));
	if (!new)
		return (NULL);
	while (s[i] != '\0')
	{
		new[i] = f(i, s[i]);
		i++;
	}
	return (new);
}

// char	ft_toupper2(unsigned int index, char lowercase_letter)
// {
// 	return ((char)ft_toupper(lowercase_letter)); //on ignore l'index
// }
// char	ft_star(unsigned int index, char bfr) //renvoie une * si i est pair
// {
// 	if (index % 2 == 0)
// 	{
// 		return ('*');
// 	}
// 	return(bfr);
// }

// #include <stdio.h>

// int	main(void)
// {
// 	const char	*str_bfr = "Each char will be mod in a new str";

// 	const char *str_aft = ft_strmapi(str_bfr, ft_toupper2);

// 	printf("%p", str_aft);

// 	return (0);
// }
