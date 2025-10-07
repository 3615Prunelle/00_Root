/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 00:41:28 by schappuy          #+#    #+#             */
/*   Updated: 2025/10/08 00:58:18 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_chopsticks_and_eat(t_yaks *yakuza, t_mutex *chopstick_1,
		t_mutex *chopstick_2)
{
	while (yakuza->priority == LOW)
	{
		set_priority(yakuza);
		usleep(10);
	}
	pthread_mutex_lock(chopstick_1);
	if (!is_yakuza_alive(yakuza))
	{
		pthread_mutex_unlock(chopstick_1);
		return ;
	}
	print_and_change_status(TOOK_CHOPSTICK, yakuza);
	pthread_mutex_lock(chopstick_2);
	if (!is_yakuza_alive(yakuza))
	{
		free_both_chopsticks(chopstick_1, chopstick_2);
		return ;
	}
	print_and_change_status(TOOK_CHOPSTICK, yakuza);
	print_and_change_status(EATING, yakuza);
	yakuza->meals_count = copy_meal_count(yakuza, true);
	get_timestamp(yakuza, true);
	usleep(yakuza->trd.time_to_eat * 1000);
	free_both_chopsticks(chopstick_1, chopstick_2);
}

void	sleep_till_think(t_yaks *yakuza)
{
	if (!is_yakuza_alive(yakuza))
		return ;
	print_and_change_status(SLEEPING, yakuza);
	usleep(yakuza->trd.time_to_sleep * 1000);
	if (!is_yakuza_alive(yakuza))
		return ;
	print_and_change_status(THINKING, yakuza);
	yakuza->priority = LOW;
}

void	print_and_change_status(t_state state, t_yaks *yakuza)
{
	struct timeval	time_stamp;
	unsigned long	timestamp;

	gettimeofday(&time_stamp, NULL);
	timestamp = (time_stamp.tv_sec * 1000) + (time_stamp.tv_usec / 1000);
	pthread_mutex_lock(yakuza->you_shall_not_pass);
	if (state == TOOK_CHOPSTICK)
		printf("%lu %d has taken a chopstick\n", timestamp, yakuza->position);
	else if (state == EATING)
	{
		printf("%s%lu %d is eating\n%s", S_GREEN, timestamp, yakuza->position,
			NC);
		yakuza->current_state = EATING;
	}
	else if (state == SLEEPING)
	{
		printf("%lu %d is sleeping\n", timestamp, yakuza->position);
		yakuza->current_state = SLEEPING;
	}
	else if (state == THINKING)
	{
		printf("%lu %d is thinking\n", timestamp, yakuza->position);
		yakuza->current_state = THINKING;
	}
	pthread_mutex_unlock(yakuza->you_shall_not_pass);
}
