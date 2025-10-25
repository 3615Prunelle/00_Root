/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:03:16 by schappuy          #+#    #+#             */
/*   Updated: 2025/10/25 20:01:05 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int				ft_index_end(const char *str, const char *totrim);
static int				ft_index_beg(const char *str, const char *totrim);
static unsigned char	ft_is_c_trim(const char char_str0, const char *totrim);

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	char	*trimmed;
	int		end;
	int		beg;

	i = 0;
	if (ft_strlen(s1) == 0)
		return (ft_strdup(""));
	end = ft_index_end(s1, set);
	beg = ft_index_beg(s1, set);
	if (beg > end)
		return (ft_strdup(""));
	trimmed = malloc(end - beg + 2);
	if (!trimmed)
		return (NULL);
	while (beg + i <= end)
	{
		trimmed[i] = s1[beg + i];
		i++;
	}
	trimmed[i] = '\0';
	return (trimmed);
}

static int	ft_index_end(const char *str, const char *totrim)
{
	int	l;

	l = (int)ft_strlen(str) - 1;
	while (l >= 0)
	{
		if (ft_is_c_trim(str[l], totrim) == 0)
		{
			return (l);
		}
		l--;
	}
	return (l);
}

static int	ft_index_beg(const char *str, const char *totrim)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_is_c_trim(str[i], totrim) == 0)
		{
			return (i);
		}
		i++;
	}
	return (i);
}

static unsigned char	ft_is_c_trim(const char char_str0, const char *totrim)
{
	int	i;

	i = 0;
	while (totrim[i] != '\0')
	{
		if (char_str0 == totrim[i])
		{
			return ((unsigned char)1);
		}
		else
		{
			i++;
		}
	}
	return ((unsigned char)0);
}

// int	main(void)
// {
// 	char str[] = "oioo-Removes chars at beg+end till other char is found-oooi";
// 	char totrim[] = "io";

// 	char *final = ft_strtrim(str, totrim);

// 	printf("%s\n", final);

// 	free(final);
// 	return (0);
// }
