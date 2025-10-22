/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_server.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 20:07:07 by sophie            #+#    #+#             */
/*   Updated: 2025/09/17 19:21:29 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_size_or_char = 0;

// SA_SIGINFO permet de récupérer le pid du client
int	main(void)
{
	char				*buffer;
	char				new_char;
	unsigned int		i;
	uint32_t			backup_size;
	struct sigaction	signal_from_client;

	new_char = '\0';
	i = 0;
	ft_printf("\n\t\t  PID server : [%d]\n", getpid());
	ft_printf("\t... Waiting for message from client ...\n");
	signal_from_client.sa_sigaction = server_handler;
	sigemptyset(&signal_from_client.sa_mask);
	sigaddset(&signal_from_client.sa_mask, SIGUSR1);
	sigaddset(&signal_from_client.sa_mask, SIGUSR2);
	signal_from_client.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &signal_from_client, NULL);
	sigaction(SIGUSR2, &signal_from_client, NULL);
	while (1)
	{
		receive_and_print_msg(&buffer, &backup_size, &new_char, &i);
	}
	return (0);
}

// Sortie du 2nd while quand le dernier char a été mis dans le buffer
void	receive_and_print_msg(char **buffer, uint32_t *backup_size,
			char *new_char, unsigned int *i)
{
	while (g_size_or_char == 0)
	{
		usleep(2000);
	}
	*buffer = ft_calloc(sizeof(char), g_size_or_char + 1);
	*backup_size = g_size_or_char;
	g_size_or_char = 0;
	while (*i < *backup_size)
	{
		while (g_size_or_char == 0)
		{
			usleep(2000);
		}
		*new_char = (char)g_size_or_char;
		(*buffer)[*i] = *new_char;
		(*i)++;
		g_size_or_char = 0;
	}
	ft_printf("%s\n", *buffer);
	free(*buffer);
	*buffer = NULL;
	*i = 0;
}

// Handler = can't change signature
// A chaque signal reçu, feu vert à client pour en envoyer un autre
// On recoit 32 bits (size) puis 8 bits (char)
void	server_handler(int signo, siginfo_t *info, void *other)
{
	static int		client_pid;
	static int		bit_count;
	static uint32_t	string_size;
	static uint32_t	binary_char;
	static bool		got_size;

	(void)other;
	if (client_pid)
		kill(client_pid, SIGUSR1);
	if ((got_size == YES) && (bit_count < BYTE_SIZE))
	{
		got_size = build_8bits(signo, &binary_char, &string_size, &bit_count);
		if (string_size == 0)
			client_pid = 0;
	}
	else if ((got_size == NO) && (bit_count < INT_SIZE))
	{
		if (client_pid == 0)
		{
			client_pid = info->si_pid;
			write(1, "\n\tNew client detected - Printing message :\n\n", 44);
			kill(client_pid, SIGUSR2);
		}
		got_size = build_32bits(signo, &client_pid, &string_size, &bit_count);
	}
}

// Step 1 : Faire de la place pour le bit qui arrive
// Step 2 : Mettre un 1 en dernière position
bool	build_32bits(int signo, int *client_pid, uint32_t *string_size,
		int *bit_count)
{
	if (signo == SIGUSR1)
	{
		*string_size = *string_size << 1;
		kill(*client_pid, SIGUSR1);
	}
	else if (signo == SIGUSR2)
	{
		*string_size = *string_size << 1;
		*string_size |= 1;
		kill(*client_pid, SIGUSR1);
	}
	(*bit_count)++;
	if ((*bit_count) == INT_SIZE)
	{
		g_size_or_char = *string_size;
		*bit_count = 0;
		if (*string_size == 0)
		{
			*client_pid = 0;
			write(1, "Error - Received an empty string\n", 33);
			return (NO);
		}
		return (YES);
	}
	return (NO);
}

bool	build_8bits(int signo, uint32_t *binary_char,
		uint32_t *string_size, int *bit_count)
{
	*binary_char = *binary_char << 1;
	if (signo == SIGUSR2)
		*binary_char |= 1;
	(*bit_count)++;
	if (*bit_count == BYTE_SIZE)
	{
		(*string_size)--;
		g_size_or_char = *binary_char;
		*binary_char = 0;
		*bit_count = 0;
		if (*string_size == 0)
		{
			*binary_char = 0;
			return (NO);
		}
	}
	return (YES);
}
