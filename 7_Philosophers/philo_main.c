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
🟢 Study pthread_mutex_lock & pthread_mutex_unlock
🔵 pthread_join = equivalent of 'wait'
🟣 Les threads ne sont pas hiérarchisés. Pas de concept de parent/child comme pour les processes
🟤
⚫
⚪

⬇️✅‼️⁉️❓❌Ⓜ️🆓
*/

# include "philosophers.h"

void	print_yakuzas_status(one_bro *this_yakuza)
{
	int	i = 0;
	while (i < this_yakuza->total_yakuzas)
	{
		printf("%sYakuza number %d is in state %c - Chopstick right : %d | Chopstick left : %d\n%s", YELLOW,
		this_yakuza->position, this_yakuza->current_state, this_yakuza->has_chopstick_right, this_yakuza->has_chopstick_left, NC);
		this_yakuza++;
		i++;
	}
}

one_bro	*previous_bro(one_bro *this_yakuza, one_bro *previous_yakuza)
{
	one_bro	*backup = this_yakuza;

	if (this_yakuza->position == 1)
	{
		previous_yakuza = backup + 5;		// ou 5 * sizeof(one_bro) is issues
	}
	else
	{
		previous_yakuza = backup--;
	}
	return (previous_yakuza);
}

one_bro	*next_bro(one_bro *this_yakuza, one_bro *next_yakuza)
{
	one_bro	*backup = this_yakuza;

	if (this_yakuza->position == this_yakuza->total_yakuzas)
	{
		next_yakuza = backup - 5;			// ou 5 * sizeof(one_bro) is issues
	}
	else
	{
		next_yakuza = backup++;
	}
	return (next_yakuza);
}

bool	can_yakuza_eat(one_bro *this_yakuza, one_bro *previous_yakuza, one_bro *next_yakuza)
{
	if ((*this_yakuza->chopsticks_available >= 1) && (this_yakuza->current_state == 'E') &&
			previous_yakuza->has_chopstick_right && next_yakuza->has_chopstick_left)
	{
		return(true);
	}
	return(false);
}
void	take_chopsticks_and_eat(one_bro *this_yakuza, one_bro *previous_yakuza, one_bro *next_yakuza)
{
	this_yakuza->has_chopstick_left = true;
	this_yakuza->has_chopstick_right = true;
	previous_yakuza->has_chopstick_right = false;
	next_yakuza->has_chopstick_left = false;
	this_yakuza->current_state = 'E';
	(*this_yakuza->chopsticks_available)--;				// attention, ca ne fait la MAJ que sur ce yak, pas global, find solution
}

void	return_chopsticks_and_sleep(one_bro *this_yakuza, one_bro *previous_yakuza, one_bro *next_yakuza)
{
	this_yakuza->current_state = 'S';
	(*this_yakuza->chopsticks_available)++;				// attention, ca ne fait la MAJ que sur ce yak, pas global, find solution
	this_yakuza->has_chopstick_left = false;
	this_yakuza->has_chopstick_right = false;
	previous_yakuza->has_chopstick_right = true;
	next_yakuza->has_chopstick_left = true;
}

void	*chopsticks_party(void *arg)
{
	struct one_bro	*this_yakuza = arg;
	pthread_t		current_thread = pthread_self();	// Useless, as we can access it via struct - Keep for debug ?
	// ATTENTION : 1 thread = 1 yakuza

	one_bro	*previous_yakuza;
	one_bro	*next_yakuza;

	previous_yakuza = previous_bro(this_yakuza, previous_bro);
	next_yakuza = next_bro(this_yakuza, next_bro);

	printf("%sCurrent Yakuza in thread function : Position : %d | ID [%lu] Debug [%lu]\n%s", GREEN,
		this_yakuza->position, this_yakuza->thread_ID, current_thread, NC);

	pthread_mutex_lock(&this_yakuza->mutual_exclusion);
	if (can_yakuza_eat(this_yakuza, previous_yakuza, next_yakuza))
	{
		take_chopsticks_and_eat(this_yakuza, previous_yakuza, next_yakuza);
		usleep(2000);				// Update avec valeurs en input when ok
		return_chopsticks_and_sleep(this_yakuza, previous_yakuza, next_yakuza);
	}
	else
	{
		// ??
	}
	pthread_mutex_unlock(&this_yakuza->mutual_exclusion);

	// lock
	// faire fonction 'check if chopsticks available' - check right/left inside
	// faire fonction 'take right chopstick' & take left - appel : if_right_chopstick_missing, take it + update variables Chopstick right : 1 | Chopstick left 1
	// unlock
	// once I have something fonctional, deal with the time related stuff

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

	one_bro		*this_yakuza;	// Array of profiles
	this_yakuza = malloc(sizeof(one_bro) * amount_of_yakuzas);

	pthread_mutex_t	mut_ex;
	pthread_mutex_init(&mut_ex, NULL);

	one_bro	*backup_first_yakuza = this_yakuza;
	while (i < amount_of_yakuzas)
	{
		this_yakuza->position = i + 1;
		this_yakuza->current_state = 'T';			// strdup intead (dans tous) + deal with malloc/free. Back to int ou char si trop relou
		this_yakuza->has_chopstick_left = false;
		this_yakuza->has_chopstick_right = false;			// personne n'a de chopstick pour commencer
		this_yakuza->total_yakuzas = amount_of_yakuzas;
		this_yakuza->chopsticks_available = &amount_of_yakuzas;
		this_yakuza->time_to_eat = time_2_eat;
		this_yakuza->time_to_sleep = time_2_sleep;
		this_yakuza->time_to_die = time_2_die;
		this_yakuza->how_many_meals = number_of_times_each_philosopher_must_eat;
		this_yakuza->mutual_exclusion = mut_ex;
		pthread_create(&this_yakuza->thread_ID, NULL, chopsticks_party, this_yakuza);
		printf("%sYakuza %d has ID [%lu]\n%s", BLUE, i + 1, this_yakuza->thread_ID, NC);
		this_yakuza++;
		i++;
	}
	this_yakuza = backup_first_yakuza;

	print_yakuzas_status(this_yakuza);

	// garder a fin ?
	i = 0;
	while (i < amount_of_yakuzas)
	{
		pthread_join(this_yakuza->thread_ID, NULL);
		this_yakuza++;
		i++;
	}
	pthread_mutex_destroy(&mut_ex);
	return(0);
}
