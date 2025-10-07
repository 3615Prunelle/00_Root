/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 00:41:42 by schappuy          #+#    #+#             */
/*   Updated: 2025/10/08 00:56:29 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_both_chopsticks(t_mutex *chopstick_1, t_mutex *chopstick_2)
{
	pthread_mutex_unlock(chopstick_1);
	pthread_mutex_unlock(chopstick_2);
}

// Saving values locally
int	copy_meal_count(t_yaks *yakuza, bool remove_one)
{
	int	backup;

	pthread_mutex_lock(yakuza->you_shall_not_pass);
	backup = yakuza->meals_count;
	pthread_mutex_unlock(yakuza->you_shall_not_pass);
	if (remove_one)
		return (backup - 1);
	else
		return (backup);
}

bool	is_party_on(t_yaks *yakuza)
{
	bool	check;

	pthread_mutex_lock(yakuza->dead_flag);
	check = *yakuza->party_is_on;
	pthread_mutex_unlock(yakuza->dead_flag);
	if (check)
		return (true);
	return (false);
}

bool	is_dead(t_yaks *yakuza, bool death_confirmed)
{
	t_state	backup;

	pthread_mutex_lock(yakuza->you_shall_not_pass);
	backup = yakuza->current_state;
	pthread_mutex_unlock(yakuza->you_shall_not_pass);
	if ((backup == DEAD) || (death_confirmed))
		return (true);
	return (false);
}
