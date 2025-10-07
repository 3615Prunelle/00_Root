/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 00:41:35 by schappuy          #+#    #+#             */
/*   Updated: 2025/10/08 00:56:56 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// timeval structs dans struct yaks plutot que TDR & calculs ?
t_prio	set_priority(t_yaks *yakuza)
{
	struct timeval	time_stamp;
	unsigned long	timestamp;

	gettimeofday(&time_stamp, NULL);
	timestamp = (time_stamp.tv_sec * 1000) + (time_stamp.tv_usec / 1000);
	yakuza->trd.now = timestamp;
	yakuza->trd.elapsed_since_meal = timestamp
		- (yakuza->trd.timestamp_last_meal);
	if ((yakuza->trd.elapsed_since_meal
			- yakuza->trd.eat_plus_sleep) > yakuza->trd.mid_thinking_time)
	{
		yakuza->priority = HIGH;
		return (HIGH);
	}
	return (LOW);
}

// FYI - Max useconds is 999 999 (so almost 1 sec)
unsigned long	get_timestamp(t_yaks *yakuza, bool update_last_meal)
{
	struct timeval	time_stamp;
	unsigned long	timestamp;

	gettimeofday(&time_stamp, NULL);
	timestamp = (time_stamp.tv_sec * 1000) + (time_stamp.tv_usec / 1000);
	if (update_last_meal)
	{
		pthread_mutex_lock(yakuza->you_shall_not_pass);
		yakuza->trd.now = timestamp;
		yakuza->trd.timestamp_last_meal = timestamp;
		pthread_mutex_unlock(yakuza->you_shall_not_pass);
	}
	return (timestamp);
}

bool	is_yakuza_alive(t_yaks *yakuza)
{
	struct timeval	time_stamp;
	unsigned long	timestamp;

	if (!is_party_on(yakuza))
		return (false);
	gettimeofday(&time_stamp, NULL);
	pthread_mutex_lock(yakuza->you_shall_not_pass);
	timestamp = (time_stamp.tv_sec * 1000) + (time_stamp.tv_usec / 1000);
	yakuza->trd.now = timestamp;
	yakuza->trd.elapsed_since_meal = timestamp
		- (yakuza->trd.timestamp_last_meal);
	pthread_mutex_unlock(yakuza->you_shall_not_pass);
	if (timestamp >= (yakuza->trd.timestamp_last_meal
			+ yakuza->trd.time_to_die))
	{
		pthread_mutex_lock(yakuza->dead_flag);
		*yakuza->party_is_on = false;
		printf("%s%lu %d died\n%s", S_RED, timestamp, yakuza->position, NC);
		yakuza->current_state = is_dead(yakuza, true);
		pthread_mutex_unlock(yakuza->dead_flag);
		return (false);
	}
	return (true);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	tot;
	int	sign;

	i = 0;
	tot = 0;
	sign = 1;
	while (((nptr[i] >= 9) && (nptr[i] <= 13)) || (nptr[i] == ' '))
	{
		i++;
	}
	if ((nptr[i] == '+') || (nptr[i] == '-'))
	{
		if (nptr[i] == '-')
		{
			sign = -1;
		}
		i++;
	}
	while ((nptr[i] >= '0') && (nptr[i] <= '9'))
	{
		tot = tot * 10 + nptr[i] - '0';
		i++;
	}
	return (tot * sign);
}

// Separate join & destroy to avoid data races
void	join_destroy_free(t_yaks *yakuza, t_mutex *all_chopsticks,
		t_mutex *flag, t_mutex *lock, pthread_t *monitor_san)
{
	t_yaks	*backup_first_yakuza;
	int		backup_total_yakuzas;
	int		i;

	backup_total_yakuzas = yakuza->total_yakuzas;
	backup_first_yakuza = yakuza;
	i = 0;
	while (i < backup_total_yakuzas)
	{
		pthread_join(yakuza->thread_id, NULL);
		yakuza++;
		i++;
	}
	i = 0;
	pthread_join(*monitor_san, NULL);
	while (i < backup_total_yakuzas)
	{
		pthread_mutex_destroy(&all_chopsticks[i]);
		i++;
	}
	pthread_mutex_destroy(flag);
	pthread_mutex_destroy(lock);
	free(all_chopsticks);
	yakuza = backup_first_yakuza;
	free(yakuza);
}
