/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 00:41:04 by schappuy          #+#    #+#             */
/*   Updated: 2025/10/08 17:46:29 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_input	input_setup(int ac, char **av, t_input *input,
		unsigned long now_in_millisec)
{
	input->amount_of_yakuzas = ft_atoi(av[1]);
	input->time_to_die = ft_atoi(av[2]);
	input->time_to_eat = ft_atoi(av[3]);
	input->time_to_sleep = ft_atoi(av[4]);
	input->eat_plus_sleep = ft_atoi(av[3]) + ft_atoi(av[4]);
	input->mid_thinking_time = (ft_atoi(av[2]) - (ft_atoi(av[3])
				+ ft_atoi(av[4]))) / 2;
	if (input->amount_of_yakuzas == 1)
	{
		printf("%s%lu\t1 died\n%s", S_RED, now_in_millisec, NC);
		return (*input);
	}
	if (ac == 6)
		input->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	else
		input->number_of_times_each_philosopher_must_eat = 200;
	return (*input);
}

// One mutex per chopstick + death mutex + multipurpose mutex
void	mutex_init(t_mutex *all_mutex, t_input *input)
{
	int	i;

	i = 0;
	while (i < input->amount_of_yakuzas)
	{
		pthread_mutex_init(&all_mutex[i], NULL);
		i++;
	}
	pthread_mutex_init(&all_mutex[i], NULL);
	pthread_mutex_init(&all_mutex[i + 1], NULL);
}

void	yakuza_array_setup(t_yaks *yakuza, t_input *input, bool *party_on,
		unsigned long now_in_millisec)
{
	int	i;

	i = 0;
	while (i < input->amount_of_yakuzas)
	{
		yakuza->position = i + 1;
		yakuza->current_state = THINKING;
		yakuza->priority = HIGH;
		yakuza->party_is_on = party_on;
		yakuza->total_yakuzas = input->amount_of_yakuzas;
		yakuza->meals_count = input->number_of_times_each_philosopher_must_eat;
		yakuza->trd.timestamp_last_meal = now_in_millisec;
		yakuza->trd.elapsed_since_meal = 0;
		yakuza->trd.time_to_eat = input->time_to_eat;
		yakuza->trd.time_to_sleep = input->time_to_sleep;
		yakuza->trd.time_to_die = input->time_to_die;
		yakuza->trd.eat_plus_sleep = input->eat_plus_sleep;
		yakuza->trd.mid_thinking_time = input->mid_thinking_time;
		yakuza++;
		i++;
	}
}

// Si ca marche faire une struct de mutex ?
void	mutex_setup(t_yaks *yakuza, t_input *input, t_mutex *all_mutex)
{
	int		i;

	i = 0;
	while (i < input->amount_of_yakuzas)
	{
		if (yakuza[i].position == input->amount_of_yakuzas)
		{
			yakuza[i].left_chpstk = &all_mutex[i];
			yakuza[i].right_chpstk = &all_mutex[0];
		}
		else
		{
			yakuza[i].left_chpstk = &all_mutex[i];
			yakuza[i].right_chpstk = &all_mutex[i + 1];
		}
		yakuza[i].dead_flag = &all_mutex[input->amount_of_yakuzas];
		yakuza[i].you_shall_not_pass = &all_mutex[input->amount_of_yakuzas + 1];
		i++;
	}
}

pthread_t	threads_setup(t_yaks *yakuza, t_input *input)
{
	t_yaks		*backup_first_yakuza;
	pthread_t	monitor_san;
	int			i;

	backup_first_yakuza = yakuza;
	i = 0;
	while (i < input->amount_of_yakuzas)
	{
		pthread_create(&yakuza->thread_id, NULL, itadakimasu, (void *)yakuza);
		yakuza++;
		i++;
	}
	yakuza = backup_first_yakuza;
	pthread_create(&monitor_san, NULL, monitor, (void *)yakuza);
	return (monitor_san);
}
