# include "philosophers.h"

// timeval structs dans struct one_bro plutot que TDR & calculs ?
prio	set_priority(one_bro *yakuza)
{
	struct timeval time_stamp;
	gettimeofday(&time_stamp, NULL);
	unsigned long	millisec_timestamp = (time_stamp.tv_sec * 1000) + (time_stamp.tv_usec / 1000);

	yakuza->TRD.elapsed_since_last_meal = millisec_timestamp - (yakuza->TRD.last_meal);

	if ((yakuza->TRD.elapsed_since_last_meal - yakuza->TRD.eat_plus_sleep) > yakuza->TRD.mid_thinking_time)
	{
		yakuza->priority = HIGH;
		return(HIGH);
	}
	return(LOW);
}

// FYI - Max useconds is 999 999 (so almost 1 sec)
void	update_timestamp_last_meal(one_bro *yakuza)
{
	struct timeval time_stamp;
	gettimeofday(&time_stamp, NULL);
	unsigned long	millisec_timestamp = (time_stamp.tv_sec * 1000) + (time_stamp.tv_usec / 1000);

	yakuza->TRD.last_meal = millisec_timestamp;
}

bool	is_yakuza_alive(one_bro *yakuza)
{
	if(!is_party_on(yakuza))
		return(false);
	struct timeval time_stamp;
	gettimeofday(&time_stamp, NULL);
	unsigned long	millisec_timestamp = (time_stamp.tv_sec * 1000) + (time_stamp.tv_usec / 1000);

	yakuza->TRD.now = millisec_timestamp;
	yakuza->TRD.elapsed_since_last_meal = millisec_timestamp - (yakuza->TRD.last_meal);

	if(millisec_timestamp >= (yakuza->TRD.last_meal + yakuza->TRD.time_to_die))
	{
		pthread_mutex_lock(yakuza->dead_flag);
		*yakuza->party_is_on = false;
		printf("%s%lu %d died\n%s", S_RED, millisec_timestamp, yakuza->position, NC);
		yakuza->current_state = DEAD;
		pthread_mutex_unlock(yakuza->dead_flag);
		return(false);
	}
	return(true);
}
void	free_both_chopsticks(mutex_t *chopstick_1, mutex_t *chopstick_2)
{
	pthread_mutex_unlock(chopstick_1);
	pthread_mutex_unlock(chopstick_2);
}

// Saving value locally
bool	is_party_on(one_bro *yakuza)
{
	bool	check;
	pthread_mutex_lock(yakuza->dead_flag);
	check = *yakuza->party_is_on;
	pthread_mutex_unlock(yakuza->dead_flag);

	if(check)
		return (true);
	return (false);
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
