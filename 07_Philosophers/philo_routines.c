/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 00:41:20 by schappuy          #+#    #+#             */
/*   Updated: 2025/10/08 00:58:34 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*itadakimasu(void *arg)
{
	t_yaks	*yakuza;

	yakuza = arg;
	while ((!is_dead(yakuza, false)) && (copy_meal_count(yakuza, false) > 0))
	{
		if (!is_yakuza_alive(yakuza))
			return (NULL);
		if (yakuza->position % 2 == 0)
		{
			take_chopsticks_and_eat(yakuza, yakuza->left_chpstk,
				yakuza->right_chpstk);
			if (yakuza->current_state == EATING)
				sleep_till_think(yakuza);
		}
		else
		{
			take_chopsticks_and_eat(yakuza, yakuza->right_chpstk,
				yakuza->left_chpstk);
			if (yakuza->current_state == EATING)
				sleep_till_think(yakuza);
		}
	}
	return (NULL);
}

void	*monitor(void *arg)
{
	t_yaks	*yakuzas;
	int		i;

	yakuzas = (t_yaks *)arg;
	i = 0;
	while (is_party_on(yakuzas) && (copy_meal_count(yakuzas, false) > 0))
	{
		i = 0;
		while (i < yakuzas->total_yakuzas)
		{
			if (!is_yakuza_alive(&yakuzas[i]))
			{
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}
