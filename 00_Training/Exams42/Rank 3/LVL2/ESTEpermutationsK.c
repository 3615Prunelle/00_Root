/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ESTEpermutationsK.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sophie <sophie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:17:03 by kmaeda            #+#    #+#             */
/*   Updated: 2026/01/11 19:01:40 by sophie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// NOT OK - not perfectly in alphabetical order - try w/ abc, 2 last prints are inverted

void	swap(char *a, char *b)
{
	char	t = *a;
	*a = *b;
	*b = t;
}

void	backtrack(char *s, int start, int len)
{
	if (start == len)
	{
		puts(s);
		return ;
	}
	int	i = start;
	while (i < len)
	{
		swap(&s[start], &s[i]);
		backtrack(s, start + 1, len);
		swap(&s[start], &s[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	char	*str = argv[1];
	int	len = 0, i = 0, j;
	while (str[len])
		len++;
	char	*s = malloc(len + 1);
	if (!s)
		return (1);
	while (i <= len)
	{
		s[i] = str[i];
		i++;
	}
	i = 0;
	while (i < len - 1)
	{
		j = i + 1;
		while (j < len)
		{
			if (s[i] > s[j])
				swap(&s[i], &s[j]);
			j++;
		}
		i++;
	}
	backtrack(s, 0, len);
	free(s);
	return (0);
}
