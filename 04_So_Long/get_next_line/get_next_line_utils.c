/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 23:21:43 by schappuy          #+#    #+#             */
/*   Updated: 2025/04/20 18:20:05 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc_copy(size_t nmemb, size_t size)
{
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	while (i < nmemb * size)
	{
		ptr[i] = '\0';
		i++;
	}
	return (ptr);
}

char	*ft_strlcpy_copy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (src[i] != '\0')
	{
		i++;
	}
	if (size == 0)
	{
		return (dst);
	}
	while (j < (size - 1) && src[j] != '\0')
	{
		dst[j] = src[j];
		j++;
	}
	dst[j] = '\0';
	return (dst);
}

char	*ft_strchr_mod(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0' || s[i] == (char)c)
	{
		if (s[i] == (char)c)
		{
			return ((char *)&s[i + 1]);
		}
		i++;
	}
	return (0);
}

size_t	ft_strlen_copy(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin_mod(char *s1, char *s2)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1)
		return (s2);
	temp = malloc(ft_strlen_copy(s1) + ft_strlen_copy(s2) + 1);
	if (!temp)
	{
		free(s1);
		return (NULL);
	}
	while (s1[i])
	{
		temp[i] = s1[i];
		i++;
	}
	while (s2[j])
		temp[i++] = s2[j++];
	temp[i] = '\0';
	free(s1);
	return (temp);
}
