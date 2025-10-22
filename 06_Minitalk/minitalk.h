/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 23:41:59 by sophie            #+#    #+#             */
/*   Updated: 2025/09/17 23:14:19 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

// ⚪ #define
# define INT_SIZE 32
# define BYTE_SIZE 8
# define ONE_BIT 1
# define YES 1
# define NO 0

// ⚪ #include
# include <ft_printf.h>
# include <libft.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h> // Pour getpid & usleep

// ⚪ Functions signatures - Server
void	receive_and_print_msg(char **buffer, uint32_t *backup_size,
			char *new_char, unsigned int *i);
void	server_handler(int signo, siginfo_t *info, void *other);
bool	build_8bits(int signo, uint32_t *binary_char,
			uint32_t *string_size, int *bit_count);
bool	build_32bits(int signo, int *client_pid, uint32_t *string_size,
			int *bit_count);

// ⚪ Functions signatures - Client
void	client_handler(int signo);
void	send_32bits(int server_pid, uint32_t size);
void	send_8bits(int server_pid, unsigned char c);

#endif
