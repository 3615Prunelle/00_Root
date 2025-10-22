/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:07:11 by schappuy          #+#    #+#             */
/*   Updated: 2025/04/20 18:20:05 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Name of new library defined here (so we can use #include "current_ft.h")
#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

//All #define can be placed only here
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 8
# endif

//All #include only here (put #include "current_ft.h" is in each file)
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

//For test purposes only, comment out when done
# include <stdio.h>

// Main Function
char		*get_next_line(int fd);

// Helpers
void		read_line(int fd, char **buffer, char **line, char **temp);
void		*ft_calloc_copy(size_t nmemb, size_t size);
void		*ft_memset_copy(void *str, int constante, size_t taille);
size_t		ft_strlen_copy(const char *str);
char		*ft_strchr_mod(const char *s, int c);
char		*ft_strlcpy_copy(char *dst, const char *src, size_t size);
char		*ft_strjoin_mod(char *s1, char *s2);
char		*free_null_three(char **buff, char **line, char **temp);

#endif
