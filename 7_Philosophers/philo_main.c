# include "philosophers.h"

int		main(int argc, char **argv)
{
	int				amount_of_yakuzas = ft_atoi(argv[1]);
	unsigned long	time_to_die_input = ft_atoi(argv[2]);
	unsigned long	time_to_eat_input = ft_atoi(argv[3]);
	unsigned long	time_to_sleep_input = ft_atoi(argv[4]);
	int				number_of_times_each_philosopher_must_eat;
	struct timeval now;
	gettimeofday(&now, NULL);
	unsigned long	now_in_millisec = (now.tv_sec * 1000) + (now.tv_usec / 1000);
	if (amount_of_yakuzas == 1)
	{
		printf("%s%lu\t1 died\n%s", S_RED, now_in_millisec, NC);
		return(0);
	}
	if (argc == 6)
		number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		number_of_times_each_philosopher_must_eat = 200;

	int 		i = 0;
	one_bro		*yakuza;
	yakuza = malloc(sizeof(one_bro) * amount_of_yakuzas);
	one_bro		*backup_first_yakuza = yakuza;
	mutex_t	*all_chopsticks;
	all_chopsticks = malloc(sizeof(mutex_t) * amount_of_yakuzas);
	while (i < amount_of_yakuzas)
	{
		pthread_mutex_init(&all_chopsticks[i], NULL);
		i++;
	}
	i = 0;
	mutex_t flag;
	pthread_mutex_init(&flag, NULL);
	bool	party_on = true;
	while (i < amount_of_yakuzas)
	{
		yakuza->position = i + 1;
		yakuza->current_state = THINKING;
		yakuza->priority = HIGH;
		if(yakuza->position == amount_of_yakuzas)
		{
			yakuza->left_chpstk = &all_chopsticks[i];
			yakuza->right_chpstk = backup_first_yakuza->left_chpstk;
		}
		else
		{
			yakuza->left_chpstk = &all_chopsticks[i];
			yakuza->right_chpstk = &all_chopsticks[i + 1];
		}
		yakuza->dead_flag = &flag;
		yakuza->party_is_on = &party_on;
		yakuza->total_yakuzas = amount_of_yakuzas;
		yakuza->meals_count = number_of_times_each_philosopher_must_eat;
		yakuza->TRD.last_meal = now_in_millisec;
		yakuza->TRD.elapsed_since_last_meal = 0;
		yakuza->TRD.time_to_eat = time_to_eat_input;
		yakuza->TRD.time_to_sleep = time_to_sleep_input;
		yakuza->TRD.time_to_die = time_to_die_input;
		yakuza->TRD.eat_plus_sleep = time_to_eat_input + time_to_sleep_input;
		yakuza->TRD.mid_thinking_time = (time_to_die_input - (time_to_eat_input + time_to_sleep_input)) / 2; // too long, put in variable
		yakuza++;
		i++;
	}
	i = 0;
	yakuza = backup_first_yakuza;
	while (i < amount_of_yakuzas)
	{
		pthread_create(&yakuza->thread_ID, NULL, itadakimasu, (void *) yakuza);
		yakuza++;
		i++;
	}
	i = 0;
	yakuza = backup_first_yakuza;

	pthread_t		monitor_san;
	pthread_create(&monitor_san, NULL, monitor, (void *) yakuza);

	while (i < amount_of_yakuzas)
	{
		pthread_join(yakuza->thread_ID, NULL);
		pthread_mutex_destroy(&all_chopsticks[i]);
		yakuza++;
		i++;
	}
	pthread_join(monitor_san, NULL);
	pthread_mutex_destroy(&flag);
	free(backup_first_yakuza);			// Free arrays
	free(all_chopsticks);
	return(0);
}
