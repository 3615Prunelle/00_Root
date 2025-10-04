# include "philosophers.h"

// Quand je tiens un truc fonctionnel, faire les verif d'inputs
// If no optional argument is provided (amount of meals), the simulation stops when a philosopher dies
// ⁉️ Idea : use linked list (round) instead of arrays ?
int		main(int argc, char **argv)
{
	int				amount_of_yakuzas = atoi(argv[1]);				// Fonction pas autorisee, c/c celle de ma libft later
	unsigned long	time_to_die_input = atoi(argv[2]);
	unsigned long	time_to_eat_input = atoi(argv[3]);
	unsigned long	time_to_sleep_input = atoi(argv[4]);
	int				number_of_times_each_philosopher_must_eat;		// Optional argument - Deal with both cases (provided or not)

	struct timeval now;
	gettimeofday(&now, NULL);
	unsigned long	now_in_millisec = (now.tv_sec * 1000) + (now.tv_usec / 1000);

	if (amount_of_yakuzas == 1)
	{
		printf("%lu\t1 died\n", now_in_millisec);
		// Anything to free ?
		return(0);
	}

	if (argc == 6)
		number_of_times_each_philosopher_must_eat= atoi(argv[5]);
	else
		number_of_times_each_philosopher_must_eat = 100;				// Nope - Simulation should never stop if this arg is not provided

	int 			i = 0;

	one_bro		*this_yakuza;										// Array of profiles
	this_yakuza = malloc(sizeof(one_bro) * amount_of_yakuzas);
	one_bro		*backup_first_yakuza = this_yakuza;

	mutex_t	*all_chopsticks;										// Array of mutex
	all_chopsticks = malloc(sizeof(mutex_t) * amount_of_yakuzas);
	while (i < amount_of_yakuzas)
	{
		pthread_mutex_init(&all_chopsticks[i], NULL);
		// printf("%sMutex %d has address %p\n%s", GREEN, i + 1, &all_chopsticks[i], NC);
		i++;
	}
	i = 0;

	mutex_t flag;
	pthread_mutex_init(&flag, NULL);
	bool	party_on = true;

	while (i < amount_of_yakuzas)
	{
		this_yakuza->position = i + 1;
		// this_yakuza->thread_ID = ;		// Will be done below, I need to create the rest first, otherwise fail
		this_yakuza->current_state = THINKING;
		this_yakuza->priority = HIGH;
		if(this_yakuza->position == amount_of_yakuzas)
		{
			this_yakuza->left_chopstick = &all_chopsticks[i];
			this_yakuza->right_chopstick = backup_first_yakuza->left_chopstick;
		}
		else
		{
			this_yakuza->left_chopstick = &all_chopsticks[i];
			this_yakuza->right_chopstick = &all_chopsticks[i + 1];
		}
		this_yakuza->dead_flag = &flag;
		this_yakuza->party_is_on = &party_on;
		this_yakuza->total_yakuzas = amount_of_yakuzas;
		this_yakuza->how_many_meals = number_of_times_each_philosopher_must_eat;

		this_yakuza->TRD.millisec_timestamp_start_dinner = now_in_millisec;
		this_yakuza->TRD.millisec_cropped_start_dinner = now_in_millisec % 10000;		// Variable a supp quand je tiens un truc fonctionnel

		this_yakuza->TRD.millisec_timestamp_now = now_in_millisec;
		this_yakuza->TRD.millisec_cropped_now = now_in_millisec % 10000;				// Variable a supp quand je tiens un truc fonctionnel

		this_yakuza->TRD.millisec_timestamp_last_meal = now_in_millisec;
		this_yakuza->TRD.millisec_cropped_last_meal = now_in_millisec % 10000;			// Variable a supp quand je tiens un truc fonctionnel

		this_yakuza->TRD.millisec_elapsed_since_last_meal = 0;

		this_yakuza->TRD.time_to_eat_in_ms = time_to_eat_input;
		this_yakuza->TRD.time_to_sleep_in_ms = time_to_sleep_input;
		this_yakuza->TRD.time_to_die_in_ms = time_to_die_input;
		this_yakuza->TRD.eat_plus_sleep_in_ms = time_to_eat_input + time_to_sleep_input;
		this_yakuza->TRD.max_thinking_time_in_ms = time_to_die_input - (time_to_eat_input + time_to_sleep_input);
		this_yakuza->TRD.half_max_thinking_time_in_ms = (time_to_die_input - (time_to_eat_input + time_to_sleep_input)) / 2;
		this_yakuza++;
		i++;
	}
	i = 0;
	this_yakuza = backup_first_yakuza;

	pthread_t		*all_threads;		// Array of threads
	while (i < amount_of_yakuzas)
	{
		pthread_create(&this_yakuza->thread_ID, NULL, itadakimasu, (void *) this_yakuza);
		// printf("%sYakuza %d has ID [%lu]\n%s", BLUE, i + 1, this_yakuza->thread_ID, NC);
		this_yakuza++;
		i++;
	}
	i = 0;
	this_yakuza = backup_first_yakuza;

	pthread_t		monitor_san;			// Pas sure que ca aille ici - Le mettre dans le tableau de threads instead ?
	pthread_create(&monitor_san, NULL, monitor, (void *) this_yakuza);

	// garder a la fin ?
	while (i < amount_of_yakuzas)
	{
		pthread_join(this_yakuza->thread_ID, NULL);
		this_yakuza++;
		i++;
	}
	i = 0;
	this_yakuza = backup_first_yakuza;

	while (i < amount_of_yakuzas)					// For testing only
	{
		pthread_mutex_destroy(&all_chopsticks[i]);	// move this line to the place/fonction I'll use each mutex
		i++;
	}
	pthread_mutex_destroy(&flag);
	return(0);
}
