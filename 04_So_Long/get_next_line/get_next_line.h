/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sophie <sophie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:07:11 by schappuy          #+#    #+#             */
/*   Updated: 2025/08/21 15:10:13 by sophie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# include <stdio.h>

char	*get_next_line(int fd);

void	read_line(int fd, char **buffer, char **line, char **temp);
void	*ft_calloc_copy(size_t nmemb, size_t size);
void	*ft_memset_copy(void *str, int constante, size_t taille);
size_t	ft_strlen_copy(const char *str);
char	*ft_strchr_mod(const char *s, int c);
char	*ft_strlcpy_copy(char *dst, const char *src, size_t size);
char	*ft_strjoin_mod(char *s1, char *s2);
char	*free_null_three(char **buff, char **line, char **temp);

#endif
