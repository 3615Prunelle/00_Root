/* Notes random
🔴 Philosophers = Processes (NB : Processes are composed of one or multiple threads, and treads are composed of instructions). But NB : One thread = one process
🟠 Chopsticks = Ressources that have to be shared between processes (but one at a time)
🟡 Your program(s) must take the following arguments:
			◦ number_of_philosophers: The number of philosophers and also the number of chopsticks.
			◦ time_to_die (in milliseconds): If a philosopher has not started eating within time_to_die_in_us milliseconds since
						the start of their last meal or the start of the simulation, they die.
			◦ time_to_eat_in_us (in milliseconds): The time it takes for a philosopher to eat.
						During that time, they will need to hold two chopsticks.
			◦ time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.
			◦ number_of_times_each_philosopher_must_eat (optional argument): If all philosophers
						have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops.
						If not specified, the simulation stops when a philosopher dies.
🟢 One chopstick = One lock
🔵 pthread_join = equivalent of 'wait'
🟣 Les threads ne sont pas hiérarchisés. Pas de concept de parent/child comme pour les processes
🟤 Mutex = Lock&Unlock are right before/after a part of code that I want to protect from other threads executing it at the same time
⚫ 1 thread = 1 yakuza
⚪ 1 mutex = 1 chopstick

⬇️✅‼️⁉️❓❌Ⓜ️🆓
*/

# include "philosophers.h"

void	*chopsticks_party(void *arg)
{
	struct one_bro	*this_yakuza = arg;
	pthread_t		current_thread = pthread_self();	// Useless, as we can access it via struct - Keep for debug ?

	printf("%sCurrent Yakuza in the chopsticks_party function : ID [%lu]\n%s", MAGENTA, current_thread, NC);

	while((this_yakuza->current_state == THINKING) && (this_yakuza->how_many_meals > 0))				// Add && if he's been thinking for less than N time. Otherwise he dies (else condition)
	{
		pthread_mutex_lock(this_yakuza->left_chopstick);
		get_time_print_action_set_status(this_yakuza, LEFT, THINKING);

		pthread_mutex_lock(this_yakuza->right_chopstick);
		get_time_print_action_set_status(this_yakuza, RIGHT, THINKING);

		get_time_print_action_set_status(this_yakuza, '-', EATING);

		pthread_mutex_unlock(this_yakuza->left_chopstick);
		// return time dans get_time_print_action_set_status pour calculer duree des actions
		// print "Yak X has been eating/sleeping/thinking for X milliseconds"
		pthread_mutex_unlock(this_yakuza->right_chopstick);

		get_time_print_action_set_status(this_yakuza, '-', SLEEPING);
		get_time_print_action_set_status(this_yakuza, '-', THINKING);
	}
	usleep(this_yakuza->time_to_sleep_in_us);

	return(NULL);				// Change arg in calling function if a return ptr is needed
}

struct timeval	get_time_print_action_set_status(one_bro *this_yakuza, char chopstick, char status)
{
		struct timeval time_stamp;
		gettimeofday(&time_stamp, NULL);
		long	total_in_microseconds = (time_stamp.tv_sec * 1000) + (time_stamp.tv_usec);

		if((chopstick == LEFT) && (status == THINKING))
		{
			printf("Milliseconds: %lu - Yakuza %d took left chopstick\n", total_in_microseconds / 1000, this_yakuza->position);
		}
		else if((chopstick == RIGHT) && (status == THINKING))
		{
			printf("Milliseconds: %ld - Yakuza %d took right chopstick\n", total_in_microseconds / 1000, this_yakuza->position);
		}
		else if (status == EATING)
		{
			printf("%sMilliseconds: %ld - Yakuza %d is eating\n%s", CYAN, total_in_microseconds / 1000, this_yakuza->position, NC);
			this_yakuza->current_state = EATING;
			this_yakuza->how_many_meals--;
			usleep(this_yakuza->time_to_eat_in_us);
		}
		else if (status == SLEEPING)
		{
			printf("Milliseconds: %ld - Yakuza %d is sleeping\n", total_in_microseconds / 1000, this_yakuza->position);
			this_yakuza->current_state = SLEEPING;
			usleep(this_yakuza->time_to_sleep_in_us);
		}
		else if (status == THINKING)
		{
			printf("Milliseconds: %ld - Yakuza %d is thinking\n", total_in_microseconds / 1000, this_yakuza->position);
			this_yakuza->current_state = THINKING;
		}
		else if (status == DYING)				// Rajouter condition de temps dans la fonction appelante
		{
			printf("Milliseconds: %ld - Yakuza %d is dying\n", total_in_microseconds / 1000, this_yakuza->position);
			this_yakuza->current_state = DYING;
		}
		return(time_stamp);
}

// Quand je tiens un truc fonctionnel, faire les verif d'inputs
// ⁉️ Idea : use linked list (round) instead of arrays ?
int	main(int argc, char **argv)
{
	int				amount_of_yakuzas = atoi(argv[1]);							// Fonction pas autorisee, c/c celle de ma libft later
	unsigned long	time_to_die_in_ms = atoi(argv[2]);
	unsigned long	time_to_eat_in_ms = atoi(argv[3]);
	unsigned long	time_to_sleep_in_ms= atoi(argv[4]);
	int				number_of_times_each_philosopher_must_eat= atoi(argv[5]);	// Optional argument
	int 			i = 0;

	one_bro		*this_yakuza;			// Array of profiles
	this_yakuza = malloc(sizeof(one_bro) * amount_of_yakuzas);
	one_bro		*backup_first_yakuza = this_yakuza;

	pthread_mutex_t	*all_chopsticks;	// Array of mutex
	all_chopsticks = malloc(sizeof(pthread_mutex_t) * amount_of_yakuzas);
	while (i < amount_of_yakuzas)
	{
		pthread_mutex_init(&all_chopsticks[i], NULL);
		// printf("%sMutex %d has address %p\n%s", GREEN, i + 1, &all_chopsticks[i], NC);
		i++;
	}
	i = 0;

	while (i < amount_of_yakuzas)
	{
		this_yakuza->position = i + 1;
		// this_yakuza->thread_ID = ;		// Will be done below, I need to create the rest first, otherwise fail
		this_yakuza->current_state = THINKING;
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
		this_yakuza->total_yakuzas = amount_of_yakuzas;
		this_yakuza->time_to_eat_in_us = time_to_eat_in_ms / 1000;
		this_yakuza->time_to_sleep_in_us = time_to_sleep_in_ms / 1000;
		this_yakuza->time_to_die_in_us = time_to_die_in_ms / 1000;
		this_yakuza->how_many_meals = number_of_times_each_philosopher_must_eat;
		this_yakuza++;
		i++;
	}
	i = 0;
	this_yakuza = backup_first_yakuza;

	pthread_t		*all_threads;		// Array of threads
	while (i < amount_of_yakuzas)
	{
		pthread_create(&this_yakuza->thread_ID, NULL, chopsticks_party, (void *) this_yakuza);
		// printf("%sYakuza %d has ID [%lu]\n%s", BLUE, i + 1, this_yakuza->thread_ID, NC);
		this_yakuza++;
		i++;
	}
	i = 0;
	this_yakuza = backup_first_yakuza;

	print_yakuzas_status(this_yakuza);

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
	return(0);
}

void	print_yakuzas_status(one_bro *this_yakuza)
{
	int	i = 0;
	int	index_yak = this_yakuza->position;

	if ((index_yak == 0) || (index_yak > this_yakuza->total_yakuzas))
	{
		printf("%sWoopsies, can't print this, plz provide a valid Yakuza pointer\n%s", RED, NC);
	}
	else if(index_yak != 1)
	{
		this_yakuza -= index_yak - 1;		// On se repositionne sur le 1er pour les display dans le bon ordre
	}

	while (i < this_yakuza->total_yakuzas)
	{
		printf("%sYakuza number %d ID [%lu] is in state %c - Chopstick left : %p | Chopstick right : %p\n%s", YELLOW,
		this_yakuza->position, this_yakuza->thread_ID, this_yakuza->current_state, this_yakuza->left_chopstick, this_yakuza->right_chopstick, NC);
		this_yakuza++;
		i++;
	}

}
