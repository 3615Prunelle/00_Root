# include "philosophers.h"

// TO DO - Bool local a updater avec le bool dans struct (check last convo Claude)
// Utiliser le mutex avant de lire le bool, et le bloquer direct apres

void	*itadakimasu(void *arg)
{
	struct one_bro	*this_yakuza = arg;

	while ((this_yakuza->current_state != DEAD) && (this_yakuza->how_many_meals > 0))
	{
		if(!is_yakuza_alive(this_yakuza))
			return(NULL);
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
	return(NULL);				// Change arg in calling function if a return value ptr is needed
}
// FYI - Max useconds is 999 999 (so almost 1 sec)
// Cropped = ne garder que les 5 derniers chiffres des millisecondes sinon relou pour debug

// 3411 2 done eating (3211 + 200)
// 3321 1 dies (3011 + 310)
// 1 dies while 2 is eating
// time stamp of 1 dying is way after its actual death

void	take_chopsticks_and_eat(one_bro *this_yakuza, mutex_t *first_chopstick_to_take, mutex_t *second_chopstick_to_take)
{
	// while (this_yakuza->priority == LOW)
	// {
	// 	printf("%s%d is here\n%s", BLUE, this_yakuza->position, NC);
	// 	usleep(10);
	// 	set_priority(this_yakuza);
	// 	printf("%s%d is here\n%s", CYAN, this_yakuza->position, NC);
	// }
	if(!is_yakuza_alive(this_yakuza))
	{
		return;
	}
	pthread_mutex_lock(first_chopstick_to_take);
	if (!is_yakuza_alive(this_yakuza))
	{
		pthread_mutex_unlock(first_chopstick_to_take);					// Check si possible de liberer plus haut 01/10
		return;
	}
	// printf("Yakuza %d took first chopstick [%p] %lu milliseconds after her last meal\t\tCropped TS : %lu\n", this_yakuza->position, first_chopstick_to_take, this_yakuza->TRD.millisec_elapsed_since_last_meal, this_yakuza->TRD.millisec_cropped_now);
	printf("%lu %d is has taken a chopstick\n", this_yakuza->TRD.millisec_cropped_now, this_yakuza->position);

	pthread_mutex_lock(second_chopstick_to_take);
	if (!is_yakuza_alive(this_yakuza))		// Keep, as Yak sometimes waits before that chopstick is available
	{
		pthread_mutex_unlock(first_chopstick_to_take);					// Check si possible de liberer plus haut 01/10
		pthread_mutex_unlock(second_chopstick_to_take);
		return;
	}
	// printf("Yakuza %d took second chopstick [%p] %lu milliseconds after her last meal\t\tCropped TS : %lu\n", this_yakuza->position, second_chopstick_to_take, this_yakuza->TRD.millisec_elapsed_since_last_meal, this_yakuza->TRD.millisec_cropped_now);
	printf("%lu %d is has taken a chopstick\n", this_yakuza->TRD.millisec_cropped_now, this_yakuza->position);

	this_yakuza->current_state = EATING;
	// printf("%sYakuza %d started eating %lu milliseconds after her last meal\t\t\t\tCropped TS : %lu\n%s", GREEN, this_yakuza->position, this_yakuza->TRD.millisec_elapsed_since_last_meal, this_yakuza->TRD.millisec_cropped_now, NC);
	printf("%lu %d is eating\n", this_yakuza->TRD.millisec_cropped_now, this_yakuza->position);
	update_timestamp_last_meal(this_yakuza);
	this_yakuza->how_many_meals--;
	usleep(this_yakuza->TRD.time_to_eat_in_ms * 1000);

	if (!is_yakuza_alive(this_yakuza))									// Update TS + Check death flag. If death, release chopsticks
	{
		pthread_mutex_unlock(first_chopstick_to_take);					// Check si possible de liberer plus haut 01/10
		pthread_mutex_unlock(second_chopstick_to_take);
		return;
	}

	// printf("%sYakuza %d is about to release chopsticks [%p] & [%p] - %d meals left\t\tCropped TS : %lu\n%s", YELLOW, this_yakuza->position, first_chopstick_to_take, second_chopstick_to_take, this_yakuza->how_many_meals, this_yakuza->TRD.millisec_cropped_now, NC);
	pthread_mutex_unlock(first_chopstick_to_take);
	pthread_mutex_unlock(second_chopstick_to_take);
}

void	sleep_till_think(one_bro *this_yakuza)
{
	if (!is_yakuza_alive(this_yakuza))
	{
		return;
	}
	this_yakuza->current_state = SLEEPING;
	// printf("%sYakuza %d started sleeping %lu milliseconds after her last meal\t\t\t\tCropped TS : %lu\n%s", BLUE, this_yakuza->position, this_yakuza->TRD.millisec_elapsed_since_last_meal, this_yakuza->TRD.millisec_cropped_now, NC);
	printf("%lu %d is sleeping\n", this_yakuza->TRD.millisec_cropped_now, this_yakuza->position);
	usleep(this_yakuza->TRD.time_to_sleep_in_ms * 1000);

	if (!is_yakuza_alive(this_yakuza))
	{
		return;
	}
	this_yakuza->current_state = THINKING;
	// printf("%sYakuza %d started thinking %lu milliseconds after her last meal\t\t\t\tCropped TS : %lu\n%s", CYAN, this_yakuza->position, this_yakuza->TRD.millisec_elapsed_since_last_meal, this_yakuza->TRD.millisec_cropped_now, NC);
	printf("%lu %d is thinking\n", this_yakuza->TRD.millisec_cropped_now, this_yakuza->position);
	this_yakuza->priority = LOW;
}
