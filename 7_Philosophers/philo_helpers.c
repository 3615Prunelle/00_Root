#include "philosophers.h"

// timeval structs dans struct yaks plutot que TDR & calculs ?
t_prio	set_priority(t_yaks *yakuza)
{
	struct timeval	time_stamp;
	unsigned long	timestamp_ms;

	gettimeofday(&time_stamp, NULL);
	timestamp_ms = (time_stamp.tv_sec * 1000) + (time_stamp.tv_usec / 1000);
	yakuza->trd.now = timestamp_ms;
	yakuza->trd.elapsed_since_meal = timestamp_ms - (yakuza->trd.timestamp_last_meal);
	if ((yakuza->trd.elapsed_since_meal - yakuza->trd.eat_plus_sleep) > yakuza->trd.mid_thinking_time)
	{
		yakuza->priority = HIGH;
		return (HIGH);
	}
	return (LOW);
}

// FYI - Max useconds is 999 999 (so almost 1 sec)
void	update_timestamp_last_meal(t_yaks *yakuza)
{
	struct timeval	time_stamp;
	unsigned long	timestamp_ms;

	gettimeofday(&time_stamp, NULL);
	timestamp_ms = (time_stamp.tv_sec * 1000) + (time_stamp.tv_usec / 1000);
	yakuza->trd.now = timestamp_ms;
	yakuza->trd.timestamp_last_meal = timestamp_ms;
}

bool	is_yakuza_alive(t_yaks *yakuza)
{
	struct timeval	time_stamp;
	unsigned long	timestamp_ms;

	if (!is_party_on(yakuza))
		return (false);
	gettimeofday(&time_stamp, NULL);
	timestamp_ms = (time_stamp.tv_sec * 1000) + (time_stamp.tv_usec / 1000);
	yakuza->trd.now = timestamp_ms;
	yakuza->trd.elapsed_since_meal = timestamp_ms - (yakuza->trd.timestamp_last_meal);
	if (timestamp_ms >= (yakuza->trd.timestamp_last_meal + yakuza->trd.time_to_die))
	{
		pthread_mutex_lock(yakuza->dead_flag);
		*yakuza->party_is_on = false;
		printf("%s%lu %d died\n%s", S_RED, timestamp_ms, yakuza->position, NC);
		yakuza->current_state = DEAD;
		pthread_mutex_unlock(yakuza->dead_flag);
		return (false);
	}
	return (true);
}
void	free_both_chopsticks(t_mutex *chopstick_1, t_mutex *chopstick_2)
{
	pthread_mutex_unlock(chopstick_1);
	pthread_mutex_unlock(chopstick_2);
}

// Saving value locally
bool	is_party_on(t_yaks *yakuza)
{
	bool	check;

	pthread_mutex_lock(yakuza->dead_flag);
	check = *yakuza->party_is_on;
	pthread_mutex_unlock(yakuza->dead_flag);
	if (check)
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
