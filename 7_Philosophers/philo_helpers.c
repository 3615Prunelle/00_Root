# include "philosophers.h"

prio	set_priority(one_bro *this_yakuza)
{
	struct timeval time_stamp;
	gettimeofday(&time_stamp, NULL);
	unsigned long	millisec_timestamp = (time_stamp.tv_sec * 1000) + (time_stamp.tv_usec / 1000);

	this_yakuza->TRD.millisec_cropped_now = millisec_timestamp % 10000;
	this_yakuza->TRD.millisec_elapsed_since_last_meal = millisec_timestamp - (this_yakuza->TRD.millisec_timestamp_last_meal);

	if (this_yakuza->TRD.millisec_elapsed_since_last_meal > this_yakuza->TRD.time_to_eat_in_ms)
	{
		this_yakuza->priority = HIGH;
		return(HIGH);
	}
	this_yakuza->priority = LOW;
	return(LOW);
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
	if(!is_party_on(this_yakuza))
		return(false);
	struct timeval time_stamp;
	gettimeofday(&time_stamp, NULL);
	unsigned long	millisec_timestamp = (time_stamp.tv_sec * 1000) + (time_stamp.tv_usec / 1000);

	this_yakuza->TRD.millisec_cropped_now = millisec_timestamp % 10000;
	this_yakuza->TRD.millisec_elapsed_since_last_meal = millisec_timestamp - (this_yakuza->TRD.millisec_timestamp_last_meal);
	printf("%sTime Stamp Test : Yak %d - %lu\n%s", RED, this_yakuza->position, this_yakuza->TRD.millisec_elapsed_since_last_meal, NC);

	if(millisec_timestamp >= (this_yakuza->TRD.millisec_timestamp_last_meal + this_yakuza->TRD.time_to_die_in_ms))
	{
		pthread_mutex_lock(this_yakuza->dead_flag);
		// printf("%sYakuza %d died because she hasn't eaten since %lu milliseconds\t\t\t\tCropped TS : %lu\n%s", RED, this_yakuza->position, this_yakuza->TRD.millisec_elapsed_since_last_meal, this_yakuza->TRD.millisec_cropped_now, NC);
		*this_yakuza->party_is_on = false;
		printf("%lu %d died\n", this_yakuza->TRD.millisec_cropped_now, this_yakuza->position);
		this_yakuza->current_state = DEAD;
		pthread_mutex_unlock(this_yakuza->dead_flag);
		return(false);
	}
	// if ((this_yakuza->current_state != DEAD) && ((this_yakuza->TRD.millisec_elapsed_since_last_meal) >= this_yakuza->TRD.time_to_die_in_ms))
	// {
	// 	pthread_mutex_lock(this_yakuza->dead_flag);
	// 	// printf("%sYakuza %d died because she hasn't eaten since %lu milliseconds\t\t\t\tCropped TS : %lu\n%s", RED, this_yakuza->position, this_yakuza->TRD.millisec_elapsed_since_last_meal, this_yakuza->TRD.millisec_cropped_now, NC);
	// 	*this_yakuza->party_is_on = false;
	// 	printf("%lu %d died\n", this_yakuza->TRD.millisec_cropped_now, this_yakuza->position);
	// 	this_yakuza->current_state = DEAD;
	// 	pthread_mutex_unlock(this_yakuza->dead_flag);
	// 	return(false);
	// }
	return(true);
}
// Or monitor =  extra thread that checks if a yakuza is dead
bool	is_party_on(one_bro *this_yakuza)
{
	bool	check;
	pthread_mutex_lock(this_yakuza->dead_flag);
	check = *this_yakuza->party_is_on;				// Saving value locally
	pthread_mutex_unlock(this_yakuza->dead_flag);

	if(check)
		return (true);
	return (false);
}

/* // Bad idea - Function to delete at some point if no use is found
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
} */
