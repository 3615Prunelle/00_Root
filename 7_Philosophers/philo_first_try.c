/* Notes random
🔴 Philosophers = Processes (NB : Processes are composed of one or multiple threads, and treads are composed of instructions). But NB : One thread = one process
🟠 Chopsticks = Ressources that have to be shared between processes (but one at a time)
🟡 Your program(s) must take the following arguments:
			◦ number_of_philosophers: The number of philosophers and also the number of chopsticks.
			◦ time_to_die (in milliseconds): If a philosopher has not started eating within time_to_die milliseconds since
						the start of their last meal or the start of the simulation, they die.
			◦ time_to_eat (in milliseconds): The time it takes for a philosopher to eat.
						During that time, they will need to hold two chopsticks.
			◦ time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.
			◦ number_of_times_each_philosopher_must_eat (optional argument): If all philosophers
						have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops.
						If not specified, the simulation stops when a philosopher dies.
🟢 One chopstick = One lock
🔵 pthread_join = equivalent of 'wait'
🟣 Les threads ne sont pas hiérarchisés. Pas de concept de parent/child comme pour les processes
🟤
⚫
⚪

⬇️✅‼️⁉️❓❌Ⓜ️🆓
*/

# include "philosophers.h"

void	*chopsticks_party(void *arg)
{
	struct one_bro	*this_yakuza = arg;
	pthread_t		current_thread = pthread_self();	// Useless, as we can access it via struct - Keep for debug ?
	// ATTENTION : 1 thread = 1 yakuza
	// At some point, deal with the time related stuff



	return(NULL);
}

// Quand je tiens un truc fonctionnel, faire les verif d'inputs
int	main(int argc, char **argv)
{
	int				amount_of_yakuzas = atoi(argv[1]);							// Fonction pas autorisee, c/c celle de ma libft later
	unsigned long	time_2_die = atoi(argv[2]);
	unsigned long	time_2_eat = atoi(argv[3]);
	unsigned long	time_2_sleep= atoi(argv[4]);
	int				number_of_times_each_philosopher_must_eat= atoi(argv[5]);	// Optional argument
	int 			i = 0;

	one_bro		*this_yakuza;			// Array of profiles
	this_yakuza = malloc(sizeof(one_bro) * amount_of_yakuzas);
	one_bro		*backup_first_yakuza = this_yakuza;

	pthread_mutex_t	*all_chopsticks;	// Array of mutex
	while (i < amount_of_yakuzas)
	{
		pthread_mutex_init(&all_chopsticks[i], NULL);
		i++;
	}
	i = 0;

	pthread_t		*all_threads;		// Array of threads
	while (i < amount_of_yakuzas)
	{
		pthread_create(&this_yakuza->thread_ID, NULL, chopsticks_party, this_yakuza);
		printf("%sYakuza %d has ID [%lu]\n%s", BLUE, i + 1, this_yakuza->thread_ID, NC);
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

	while (i < amount_of_yakuzas)					// For testing only
	{
		pthread_mutex_destroy(&all_chopsticks[i]);	// move this line to the place/fonction I'll use each mutex
		i++;
	}
	return(0);
}
