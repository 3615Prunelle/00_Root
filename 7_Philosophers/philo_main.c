/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 00:41:08 by schappuy          #+#    #+#             */
/*   Updated: 2025/10/08 00:51:57 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Had to return monitor_san thread otherwise I couldn't free it later
int	main(int ac, char **av)
{
	t_input		input;
	t_yaks		*yakuza;
	t_mutex		*all_chopsticks;
	t_mutex		*flag;
	t_mutex		*lock;
	pthread_t	monitor_san;
	bool		party_on;

	party_on = true;
	input = input_setup(ac, av, &input, get_timestamp(NULL, false));
	if (input.amount_of_yakuzas == 1)
		return (0);
	all_chopsticks = malloc(sizeof(t_mutex) * input.amount_of_yakuzas);
	flag = malloc(sizeof(t_mutex));
	lock = malloc(sizeof(t_mutex));
	mutex_init(all_chopsticks, flag, lock, &input);
	yakuza = malloc(sizeof(t_yaks) * input.amount_of_yakuzas);
	yakuza_array_setup(yakuza, &input, &party_on, get_timestamp(NULL, false));
	mutex_setup(yakuza, &input, all_chopsticks, flag, lock);
	monitor_san = threads_setup(yakuza, &input);
	join_destroy_free(yakuza, all_chopsticks, flag, lock, &monitor_san);
	free(flag);
	free(lock);
	return (0);
}
