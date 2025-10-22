/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sophie <sophie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:59:46 by schappuy          #+#    #+#             */
/*   Updated: 2025/08/20 16:47:38 by sophie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_init(int *i, int *idx_fnl, int *sub_beg, int *is_new_word);
static void	ft_let_it_gooo(char **array_of_arrays, int nbr_elements);
static void	ft_final(char **arrays, const char *s, char c, size_t size_s);
static int	ft_count_str(const char *s, char c, size_t size_s);

char	**ft_split(const char *s, char c)
{
	int		nb_str;
	char	**array_of_arrays;

	nb_str = ft_count_str(s, c, ft_strlen(s));
	array_of_arrays = ft_calloc((nb_str + 1), sizeof(char *));
	if (!array_of_arrays)
		return (0);
	ft_final(array_of_arrays, s, c, ft_strlen(s));
	if (!array_of_arrays[0] && nb_str > 0)
	{
		free(array_of_arrays);
		return (NULL);
	}
	return (array_of_arrays);
}

static void	ft_init(int *i, int *idx_fnl, int *sub_beg, int *is_new_word)
{
	*i = -1;
	*idx_fnl = -1;
	*sub_beg = 0;
	*is_new_word = 0;
}

static void	ft_let_it_gooo(char **array_of_arrays, int nbr_elements)
{
	while (nbr_elements > 0)
	{
		free(array_of_arrays[nbr_elements - 1]);
		array_of_arrays[nbr_elements - 1] = NULL;
		nbr_elements--;
	}
}

static void	ft_final(char **arrays, const char *s, char c, size_t size_s)
{
	int	i;
	int	idx_fnl;
	int	sub_beg;
	int	is_new_word;

	ft_init(&i, &idx_fnl, &sub_beg, &is_new_word);
	while (++i <= (int)size_s)
	{
		if ((s[i] == c) || (s[i] == '\0'))
		{
			if (is_new_word == 1)
			{
				arrays[++idx_fnl] = ft_substr(s, sub_beg, i - sub_beg);
				if (!arrays[idx_fnl])
					return (ft_let_it_gooo(arrays, idx_fnl));
			}
			is_new_word = 0;
		}
		if (s[i] != c)
		{
			if (is_new_word == 0)
				sub_beg = i;
			is_new_word = 1;
		}
	}
}

int	ft_count_str(const char *s, char c, size_t size_s)
{
	int	i;
	int	nb_str;
	int	is_new_word;

	i = 0;
	nb_str = 0;
	is_new_word = 0;
	while (i <= (int)size_s)
	{
		if ((s[i] == c) || (s[i] == '\0'))
		{
			if (is_new_word == 1)
				nb_str++;
			is_new_word = 0;
		}
		if (s[i] != c)
			is_new_word = 1;
		i++;
	}
	return (nb_str);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	str0[] = "1hello11111you1wassup!1";
// 	char	c = '1';

// 	char **split1 = ft_split(str0, c);

// 	int i = 0;
// 	while (split1[i] != NULL)
// 	{
// 		printf("%s\n", split1[i]);
// 		i++;
// 	}
// 	char str_empty[] = "";
// 	char **split_empty = ft_split(str_empty, c);
// 	if (split_empty[0] == NULL)
// 		printf("ok\n");
// 	free(split_empty);
// 	return (0);
// }
