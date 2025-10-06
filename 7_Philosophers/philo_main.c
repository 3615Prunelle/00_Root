#include "philosophers.h"

// TO DO : see last convo w/ Claude
// remove backups 1st ptr yakuzas et work with index instead

int	main(int ac, char **av)
{
	t_input			data_to_conv;
	struct timeval	now;
	unsigned long	now_in_millisec;
	t_yaks			*yakuza;
	t_mutex			*all_chopsticks;
	t_mutex			*flag;
	pthread_t		monitor_san;
	bool			party_on;

	party_on = true;
	gettimeofday(&now, NULL);
	now_in_millisec = (now.tv_sec * 1000) + (now.tv_usec / 1000);
	data_to_conv = input_setup(ac, av, &data_to_conv, now_in_millisec);			// Ⓜ️ Je dois lui passer un ptr de data_to_conv otherwise complains (not initialized)
	if (data_to_conv.amount_of_yakuzas == 1)
		return (0);
	all_chopsticks = malloc(sizeof(t_mutex) * data_to_conv.amount_of_yakuzas);	// Ⓜ️
	flag = malloc(sizeof(t_mutex));												// Ⓜ️
	mutex_init(all_chopsticks, flag, &data_to_conv);
	yakuza = malloc(sizeof(t_yaks) * data_to_conv.amount_of_yakuzas);			// Ⓜ️
	yakuza_array_set_up(yakuza, &data_to_conv, &party_on, now_in_millisec);
	mutex_setup(yakuza, &data_to_conv, all_chopsticks, flag);
	monitor_san = threads_setup(yakuza, &data_to_conv); 	// Had to return thread otherwise I couldn't free it later
	join_destroy_free(yakuza, all_chopsticks, flag, &monitor_san);
	// free(&data_to_conv);									// No need to free anymore (no malloc done)
	return (0);
}

t_input	input_setup(int ac, char **av, t_input *data_to_conv, unsigned long now_in_millisec)
{
	// data_to_conv = malloc(sizeof(t_input));				// Malloc prob no necessary as this struct doesn't exist passed main
	data_to_conv->amount_of_yakuzas = ft_atoi(av[1]);
	data_to_conv->time_to_die = ft_atoi(av[2]);
	data_to_conv->time_to_eat = ft_atoi(av[3]);
	data_to_conv->time_to_sleep = ft_atoi(av[4]);
	data_to_conv->eat_plus_sleep = ft_atoi(av[3]) + ft_atoi(av[4]);
	data_to_conv->mid_thinking_time = (ft_atoi(av[2]) - ft_atoi(av[3]) + ft_atoi(av[4])) / 2;
	if (data_to_conv->amount_of_yakuzas == 1)
	{
		printf("%s%lu\t1 died\n%s", S_RED, now_in_millisec, NC);
		return (*data_to_conv);
	}
	if (ac == 6)
		data_to_conv->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	else
		data_to_conv->number_of_times_each_philosopher_must_eat = 200;
	return (*data_to_conv);
}

void	mutex_init(t_mutex *all_chopsticks, t_mutex *flag, t_input *data_to_conv)
{
	int	i;

	i = 0;
	// all_chopsticks = malloc(sizeof(t_mutex) * data_to_conv->amount_of_yakuzas); //done in main
	while (i < data_to_conv->amount_of_yakuzas)
	{
		pthread_mutex_init(&all_chopsticks[i], NULL);
		i++;
	}
	pthread_mutex_init(flag, NULL);
	// return (all_chopsticks);
}

void	yakuza_array_set_up(t_yaks *yakuza, t_input *data_to_conv, bool *party_on, unsigned long now_in_millisec)
{
	t_yaks	*backup_first_yakuza;
	int		i;

	backup_first_yakuza = yakuza;
	i = 0;
	// yakuza = malloc(sizeof(t_yaks) * data_to_conv->amount_of_yakuzas);
	while (i < data_to_conv->amount_of_yakuzas)
	{
		yakuza->position = i + 1;
		yakuza->current_state = THINKING;
		yakuza->priority = HIGH;
		yakuza->party_is_on = party_on;
		yakuza->total_yakuzas = data_to_conv->amount_of_yakuzas;
		yakuza->meals_count = data_to_conv->number_of_times_each_philosopher_must_eat;
		yakuza->trd.last_meal = now_in_millisec;
		yakuza->trd.elapsed_since_last_meal = 0;
		yakuza->trd.time_to_eat = data_to_conv->time_to_eat;
		yakuza->trd.time_to_sleep = data_to_conv->time_to_sleep;
		yakuza->trd.time_to_die = data_to_conv->time_to_die;
		yakuza->trd.eat_plus_sleep = data_to_conv->eat_plus_sleep;
		yakuza->trd.mid_thinking_time = data_to_conv->mid_thinking_time;
		yakuza++;
		i++;
	}
	yakuza = backup_first_yakuza;		// Prob useless
}

void	mutex_setup(t_yaks *yakuza, t_input *data_to_conv, t_mutex *all_chopsticks, t_mutex *flag)
{
	t_yaks	*backup_first_yakuza;
	int		i;

	backup_first_yakuza = yakuza;
	i = 0;
	while (i < data_to_conv->amount_of_yakuzas)
	{
		if (yakuza->position == data_to_conv->amount_of_yakuzas)
		{
			yakuza->left_chpstk = &all_chopsticks[i];
			yakuza->right_chpstk = &all_chopsticks[0];
		}
		else
		{
			yakuza->left_chpstk = &all_chopsticks[i];
			yakuza->right_chpstk = &all_chopsticks[i + 1];
		}
		yakuza->dead_flag = flag;
		yakuza++;
		i++;
	}
	yakuza = backup_first_yakuza;
}

pthread_t	threads_setup(t_yaks *yakuza, t_input *data_to_conv)
{
	t_yaks		*backup_first_yakuza;
	pthread_t	monitor_san;
	int			i;

	backup_first_yakuza = yakuza;
	i = 0;
	while (i < data_to_conv->amount_of_yakuzas)
	{
		pthread_create(&yakuza->thread_id, NULL, itadakimasu, (void *)yakuza);
		yakuza++;
		i++;
	}
	yakuza = backup_first_yakuza;
	pthread_create(&monitor_san, NULL, monitor, (void *)yakuza);	// Keep here because the yakuza's thread IDs are needed
	return (monitor_san);
}

void	join_destroy_free(t_yaks *yakuza, t_mutex *all_chopsticks, t_mutex *flag, pthread_t *monitor_san)
{
	t_yaks	*backup_first_yakuza;
	int		i;

	backup_first_yakuza = yakuza;
	i = 0;
	while (i < yakuza->total_yakuzas)
	{
		pthread_join(yakuza->thread_id, NULL);
		// pthread_mutex_destroy(&all_chopsticks[i]);
		yakuza++;
		i++;
	}
	pthread_join(*monitor_san, NULL);
	yakuza = backup_first_yakuza;
	i = 0;
	while (i < yakuza->total_yakuzas)		// Join THEN destroy (was also working before the split)
	{
		pthread_mutex_destroy(&all_chopsticks[i]);
		i++;
	}
	pthread_mutex_destroy(flag);
	free(all_chopsticks);
	free(yakuza);
}
