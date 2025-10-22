/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 00:41:08 by schappuy          #+#    #+#             */
/*   Updated: 2025/10/08 18:03:37 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Had to return monitor_san thread otherwise I couldn't free it later
int	main(int ac, char **av)
{
	t_input		input;
	t_yaks		*yakuza;
	t_mutex		*all_mutex;
	pthread_t	monitor_san;
	bool		party_on;

	if ((ac < 5) || (ac > 6))
	{
		printf("%s", ERROR_MSG);
		return (0);
	}
	party_on = true;
	input = input_setup(ac, av, &input, get_timestamp(NULL, false));
	if (input.amount_of_yakuzas == 1)
		return (0);
	all_mutex = malloc(sizeof(t_mutex) * (input.amount_of_yakuzas + 2));
	mutex_init(all_mutex, &input);
	yakuza = malloc(sizeof(t_yaks) * input.amount_of_yakuzas);
	yakuza_array_setup(yakuza, &input, &party_on, get_timestamp(NULL, false));
	mutex_setup(yakuza, &input, all_mutex);
	monitor_san = threads_setup(yakuza, &input);
	join_destroy_free(yakuza, all_mutex, &monitor_san);
	return (0);
}
