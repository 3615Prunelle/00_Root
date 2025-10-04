# include "philosophers.h"

void	*itadakimasu(void *arg)
{
	one_bro	*yakuza = arg;

	while ((yakuza->current_state != DEAD) && (yakuza->meals_count > 0))
	{
		if(!is_yakuza_alive(yakuza))
			return(NULL);
		if (yakuza->position % 2 == 0)
		{
			take_chopsticks_and_eat(yakuza, yakuza->left_chpstk, yakuza->right_chpstk);
			if(yakuza->current_state == EATING)
			{
				sleep_till_think(yakuza);
			}
		}
		else
		{
			take_chopsticks_and_eat(yakuza, yakuza->right_chpstk, yakuza->left_chpstk);
			if(yakuza->current_state == EATING)
			{
				sleep_till_think(yakuza);
			}
		}
	}
	return(NULL);
}

void	*monitor(void *arg)
{
	one_bro	*yakuzas = (one_bro*)arg;
	int		i = 0;

	while (is_party_on(yakuzas) && (yakuzas->meals_count > 0))
	{
		i = 0;
		while (i < yakuzas->total_yakuzas)
		{
			if (!is_yakuza_alive(&yakuzas[i]))
			{
				return(NULL);
			}
			i++;
		}
	}
	return(NULL);
}
