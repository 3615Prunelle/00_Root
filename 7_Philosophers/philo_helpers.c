# include "philosophers.h"

// timeval structs dans struct one_bro plutot que TDR & calculs ?
prio	set_priority(one_bro *this_yakuza)
{
	struct timeval time_stamp;
	gettimeofday(&time_stamp, NULL);
	unsigned long	millisec_timestamp = (time_stamp.tv_sec * 1000) + (time_stamp.tv_usec / 1000);

	this_yakuza->TRD.millisec_cropped_now = millisec_timestamp % 10000;
	this_yakuza->TRD.millisec_elapsed_since_last_meal = millisec_timestamp - (this_yakuza->TRD.millisec_timestamp_last_meal);

	if ((this_yakuza->TRD.millisec_elapsed_since_last_meal - this_yakuza->TRD.eat_plus_sleep_in_ms) > this_yakuza->TRD.half_max_thinking_time_in_ms)
	{
		this_yakuza->priority = HIGH;
		return(HIGH);
	}
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
	// printf("%sTime Elap Watch : Yak %d - %lu\t\t\t\t\t\t\t\tCropped TS : %lu\n%s", S_MAGENTA, this_yakuza->position, this_yakuza->TRD.millisec_elapsed_since_last_meal, this_yakuza->TRD.millisec_cropped_now, NC);

	if(millisec_timestamp >= (this_yakuza->TRD.millisec_timestamp_last_meal + this_yakuza->TRD.time_to_die_in_ms))
	{
		pthread_mutex_lock(this_yakuza->dead_flag);
		*this_yakuza->party_is_on = false;
		printf("%sYakuza %d died because he hasn't eaten since %lu milliseconds\t\t\t\tCropped TS : %lu\n%s", RED, this_yakuza->position, this_yakuza->TRD.millisec_elapsed_since_last_meal, this_yakuza->TRD.millisec_cropped_now, NC);
		// printf("%lu %d died\n", this_yakuza->TRD.millisec_cropped_now, this_yakuza->position);
		this_yakuza->current_state = DEAD;
		pthread_mutex_unlock(this_yakuza->dead_flag);
		return(false);
	}
	return(true);
}

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

void	*monitor(void *arg)
{
	one_bro	*yakuzas = (one_bro*)arg;
	int		i = 0;

	while (is_party_on(yakuzas) && (yakuzas->how_many_meals > 0))
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

int	ft_atoi(const char *nptr)
{
	int	i;
	int	tot;
	int	sign;

	i = 0;
	tot = 0;
	sign = 1;
	while (((nptr[i] >= 9) && (nptr[i] <= 13)) || (nptr[i] == ' '))
	{
		i++;
	}
	if ((nptr[i] == '+') || (nptr[i] == '-'))
	{
		if (nptr[i] == '-')
		{
			sign = -1;
		}
		i++;
	}
	while ((nptr[i] >= '0') && (nptr[i] <= '9'))
	{
		tot = tot * 10 + nptr[i] - '0';
		i++;
	}
	return (tot * sign);
}
