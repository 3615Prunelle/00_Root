# include "philosophers.h"

void	*itadakimasu(void *arg)
{
	struct one_bro	*this_yakuza = arg;
	// is_yakuza_alive(this_yakuza);					// To update time diff between start & meal for the ones who doesn't eat

// Add priority for the cases there are lots of philosophers ?

	while ((this_yakuza->how_many_meals > 0) && (this_yakuza->current_state != DEAD))
	{
		if (this_yakuza->position % 2 == 0)										// Pairs prennent gauche en 1er
		{
			take_chopsticks_and_eat(this_yakuza, this_yakuza->left_chopstick, this_yakuza->right_chopstick);
			if(this_yakuza->current_state == EATING)							// Deadlock check
			{
				sleep_till_think(this_yakuza);
			}
		}
		else
		{
			take_chopsticks_and_eat(this_yakuza, this_yakuza->right_chopstick, this_yakuza->left_chopstick);
			if(this_yakuza->current_state == EATING)							// Deadlock check
			{
				sleep_till_think(this_yakuza);
			}
		}
	}
	return(NULL);				// Change arg in calling function if a return ptr is needed
}
// FYI - Max useconds is 999 999 (so almost 1 sec)
// Cropped = ne garder que les 5 derniers chiffres des millisecondes sinon relou pour debug
void	update_timestamp_last_meal(one_bro *this_yakuza)
{
	struct timeval time_stamp;
	gettimeofday(&time_stamp, NULL);
	unsigned long	millisec_timestamp = (time_stamp.tv_sec * 1000) + (time_stamp.tv_usec / 1000);

	this_yakuza->TRD.millisec_cropped_now = millisec_timestamp % 10000;
	this_yakuza->TRD.millisec_timestamp_last_meal = millisec_timestamp;
	// this_yakuza->TRD.millisec_cropped_last_meal = millisec_timestamp % 10000;
}

bool	is_yakuza_alive(one_bro *this_yakuza)
{
	struct timeval time_stamp;
	gettimeofday(&time_stamp, NULL);
	unsigned long	millisec_timestamp = (time_stamp.tv_sec * 1000) + (time_stamp.tv_usec / 1000);

	this_yakuza->TRD.millisec_cropped_now = millisec_timestamp % 10000;
	this_yakuza->TRD.millisec_elapsed_since_last_meal = millisec_timestamp - (this_yakuza->TRD.millisec_timestamp_last_meal);

	if ((this_yakuza->current_state != DEAD) && ((this_yakuza->TRD.millisec_elapsed_since_last_meal) > this_yakuza->TRD.time_to_die_in_ms))
	{
		pthread_mutex_lock(this_yakuza->dead_flag);
		printf("%sYakuza %d died because she hasn't eaten since %lu milliseconds\t\t\t\tCropped TS : %lu\n%s", RED, this_yakuza->position, this_yakuza->TRD.millisec_elapsed_since_last_meal, this_yakuza->TRD.millisec_cropped_now, NC);
		// printf("%lu %d died\n", this_yakuza->TRD.millisec_cropped_now, this_yakuza->position);
		this_yakuza->current_state = DEAD;
		return(false);
	}
	return(true);
}

void	take_chopsticks_and_eat(one_bro *this_yakuza, mutex_t *first_chopstick_to_take, mutex_t *second_chopstick_to_take)
{
	dead_mutex(this_yakuza, this_yakuza->dead_flag);

	pthread_mutex_lock(first_chopstick_to_take);
	if (!is_yakuza_alive(this_yakuza))
	{
		pthread_mutex_unlock(first_chopstick_to_take);				// Check si possible de liberer plus haut 01/10
		return;
	}
	printf("Yakuza %d took first chopstick [%p] %lu milliseconds after her last meal\t\tCropped TS : %lu\n", this_yakuza->position, first_chopstick_to_take, this_yakuza->TRD.millisec_elapsed_since_last_meal, this_yakuza->TRD.millisec_cropped_now);
	// printf("%lu %d is has taken a chopstick\n", this_yakuza->TRD.millisec_cropped_now, this_yakuza->position);

	pthread_mutex_lock(second_chopstick_to_take);
	if (!is_yakuza_alive(this_yakuza))		// Keep, as Yak sometimes waits before that chopstick is available
	{
		pthread_mutex_unlock(first_chopstick_to_take);					// Check si possible de liberer plus haut 01/10
		pthread_mutex_unlock(second_chopstick_to_take);
		return;
	}
	printf("Yakuza %d took second chopstick [%p] %lu milliseconds after her last meal\t\tCropped TS : %lu\n", this_yakuza->position, second_chopstick_to_take, this_yakuza->TRD.millisec_elapsed_since_last_meal, this_yakuza->TRD.millisec_cropped_now);
	// printf("%lu %d is has taken a chopstick\n", this_yakuza->TRD.millisec_cropped_now, this_yakuza->position);

	this_yakuza->current_state = EATING;
	printf("%sYakuza %d started eating %lu milliseconds after her last meal\t\t\t\tCropped TS : %lu\n%s", GREEN, this_yakuza->position, this_yakuza->TRD.millisec_elapsed_since_last_meal, this_yakuza->TRD.millisec_cropped_now, NC);
	// printf("%lu %d is eating\n", this_yakuza->TRD.millisec_cropped_now, this_yakuza->position);
	update_timestamp_last_meal(this_yakuza);

	this_yakuza->how_many_meals--;
	usleep(this_yakuza->TRD.time_to_eat_in_ms * 1000);

	is_yakuza_alive(this_yakuza);
	printf("%sYakuza %d is about to release chopsticks [%p] & [%p] - %d meals left\t\tCropped TS : %lu\n%s", YELLOW, this_yakuza->position, first_chopstick_to_take, second_chopstick_to_take, this_yakuza->how_many_meals, this_yakuza->TRD.millisec_cropped_now, NC);
	pthread_mutex_unlock(first_chopstick_to_take);
	pthread_mutex_unlock(second_chopstick_to_take);
}

void	sleep_till_think(one_bro *this_yakuza)
{
	dead_mutex(this_yakuza, this_yakuza->dead_flag);

	if (!is_yakuza_alive(this_yakuza))
	{
		return;
	}
	this_yakuza->current_state = SLEEPING;
	printf("%sYakuza %d started sleeping %lu milliseconds after her last meal\t\t\t\tCropped TS : %lu\n%s", BLUE, this_yakuza->position, this_yakuza->TRD.millisec_elapsed_since_last_meal, this_yakuza->TRD.millisec_cropped_now, NC);
	// printf("%lu %d is sleeping\n", this_yakuza->TRD.millisec_cropped_now, this_yakuza->position);
	usleep(this_yakuza->TRD.time_to_sleep_in_ms * 1000);
	if (!is_yakuza_alive(this_yakuza))
	{
		return;
	}
	this_yakuza->current_state = THINKING;
	printf("%sYakuza %d started thinking %lu milliseconds after her last meal\t\t\t\tCropped TS : %lu\n%s", CYAN, this_yakuza->position, this_yakuza->TRD.millisec_elapsed_since_last_meal, this_yakuza->TRD.millisec_cropped_now, NC);
	// printf("%lu %d is thinking\n", this_yakuza->TRD.millisec_cropped_now, this_yakuza->position);
}

void	dead_mutex(one_bro *this_yakuza, mutex_t *death_verif)
{
	pthread_mutex_lock(death_verif);								// piste a explorer : mutex en plus ?
	pthread_mutex_unlock(death_verif);
}

// Quand je tiens un truc fonctionnel, faire les verif d'inputs
// si un seul philo, erreur ou le faire mourrir direct ?
// victory msg "no one died ! \o/ " ?
// If no optional argument is provided (amount of meals), the simulation stops when a philosopher dies
// ⁉️ Idea : use linked list (round) instead of arrays ?
int		main(int argc, char **argv)
{
	int				amount_of_yakuzas = atoi(argv[1]);							// Fonction pas autorisee, c/c celle de ma libft later
	unsigned long	time_to_die_input = atoi(argv[2]);
	unsigned long	time_to_eat_input = atoi(argv[3]);
	unsigned long	time_to_sleep_input = atoi(argv[4]);
	int				number_of_times_each_philosopher_must_eat;	// Optional argument

	if (argc == 6)
		number_of_times_each_philosopher_must_eat= atoi(argv[5]);
	else
		number_of_times_each_philosopher_must_eat = 99;

	int 			i = 0;

	one_bro		*this_yakuza;			// Array of profiles
	this_yakuza = malloc(sizeof(one_bro) * amount_of_yakuzas);
	one_bro		*backup_first_yakuza = this_yakuza;

	mutex_t	*all_chopsticks;	// Array of mutex
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

	struct timeval now;
	gettimeofday(&now, NULL);
	unsigned long	now_in_millisec = (now.tv_sec * 1000) + (now.tv_usec / 1000);

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
		this_yakuza->dead_flag = &flag;
		this_yakuza->total_yakuzas = amount_of_yakuzas;
		this_yakuza->how_many_meals = number_of_times_each_philosopher_must_eat;

		this_yakuza->TRD.millisec_timestamp_start_dinner = now_in_millisec;
		this_yakuza->TRD.millisec_cropped_start_dinner = now_in_millisec % 10000;

		this_yakuza->TRD.millisec_timestamp_now = now_in_millisec;
		this_yakuza->TRD.millisec_cropped_now = now_in_millisec % 10000;

		this_yakuza->TRD.millisec_timestamp_last_meal = now_in_millisec;
		this_yakuza->TRD.millisec_cropped_last_meal = now_in_millisec % 10000;

		this_yakuza->TRD.millisec_elapsed_since_last_meal = 0;

		this_yakuza->TRD.time_to_eat_in_ms = time_to_eat_input;
		this_yakuza->TRD.time_to_sleep_in_ms = time_to_sleep_input;
		this_yakuza->TRD.time_to_die_in_ms = time_to_die_input;
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

// Bad idea - Function to delete at some point
void	detach_all_threads(one_bro *this_yakuza)
{
	int	i = 0;
	int	index_yak = this_yakuza->position;

	if ((index_yak == 0) || (index_yak > this_yakuza->total_yakuzas))
	{
		printf("%sWoopsies, can't detach, plz provide a valid Yakuza pointer\n%s", RED, NC);
	}
	else if(index_yak != 1)
	{
		this_yakuza -= index_yak - 1;		// On se repositionne sur le 1er pour les <whatev's> dans le bon ordre
	}

	while (i < this_yakuza->total_yakuzas)
	{
		pthread_detach(this_yakuza->thread_ID);
		this_yakuza++;
		i++;
	}
}
