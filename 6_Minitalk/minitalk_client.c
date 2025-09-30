/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_client.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 23:46:04 by sophie            #+#    #+#             */
/*   Updated: 2025/09/30 22:19:05 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_ready_to_send = YES;

// Cast de size_t vers uint32 ok tant que size_t ≤ UINT32_MAX (4294967295)
int	main(int argc, char **argv)
{
	int					server_pid;
	uint32_t			string_size;
	int					i;
	struct sigaction	signal_from_server;

	i = 0;
	signal_from_server.sa_handler = client_handler;
	signal_from_server.sa_flags = 0;
	sigemptyset(&signal_from_server.sa_mask);
	sigaddset(&signal_from_server.sa_mask, SIGUSR1);
	sigaddset(&signal_from_server.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &signal_from_server, NULL);
	sigaction(SIGUSR2, &signal_from_server, NULL);
	if (argc == 3)
	{
		server_pid = ft_atoi(argv[1]);
		string_size = (uint32_t)ft_strlen(argv[2]);
		send_32bits(server_pid, string_size);
		while (argv[2][i] != '\0')
		{
			send_8bits(server_pid, argv[2][i]);
			i++;
		}
	}
	return (0);
}

void	send_32bits(int server_pid, uint32_t size)
{
	int			i;
	uint32_t	bitmask;

	i = 0;
	bitmask = 2147483648;
	while ((g_ready_to_send == YES) && (i < INT_SIZE))
	{
		if (size & bitmask)
		{
			g_ready_to_send = NO;
			kill(server_pid, SIGUSR2);
			usleep(2000);
		}
		else
		{
			g_ready_to_send = NO;
			kill(server_pid, SIGUSR1);
			usleep(2000);
		}
		bitmask /= 2;
		i++;
	}
}

void	send_8bits(int server_pid, unsigned char c)
{
	int				i;
	unsigned char	bitmask;

	i = 0;
	bitmask = 128;
	while ((g_ready_to_send == YES) && (i < BYTE_SIZE))
	{
		if (c & bitmask)
		{
			g_ready_to_send = NO;
			kill(server_pid, SIGUSR2);
			usleep(2000);
		}
		else
		{
			g_ready_to_send = NO;
			kill(server_pid, SIGUSR1);
			usleep(2000);
		}
		bitmask /= 2;
		i++;
	}
}

void	client_handler(int signo)
{
	if (signo == SIGUSR1)
	{
		g_ready_to_send = YES;
	}
	if (signo == SIGUSR2)
	{
		write(1, "\t\tConnexion established with Server !\n\n", 39);
	}
}
