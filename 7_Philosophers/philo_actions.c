#include "philosophers.h"

void	take_chopsticks_and_eat(t_yaks *yakuza, t_mutex *chopstick_1,
		t_mutex *chopstick_2)
{
	while (yakuza->priority == LOW)
	{
		set_priority(yakuza);
		usleep(10);
	}
	pthread_mutex_lock(chopstick_1);
	if (!is_yakuza_alive(yakuza))
	{
		pthread_mutex_unlock(chopstick_1);
		return ;
	}
	printf("%lu %d is has taken a chopstick\n", yakuza->trd.now,
		yakuza->position);
	pthread_mutex_lock(chopstick_2);
	if (!is_yakuza_alive(yakuza))
	{
		free_both_chopsticks(chopstick_1, chopstick_2);
		return ;
	}
	printf("%lu %d is has taken a chopstick\n", yakuza->trd.now,
		yakuza->position);
	yakuza->current_state = EATING;
	printf("%s%lu %d is eating\n%s", S_GREEN, yakuza->trd.now, yakuza->position,
		NC);
	update_timestamp_last_meal(yakuza);
	yakuza->meals_count--;
	usleep(yakuza->trd.time_to_eat * 1000);
	free_both_chopsticks(chopstick_1, chopstick_2);
}

void	sleep_till_think(t_yaks *yakuza)
{
	if (!is_yakuza_alive(yakuza))
		return ;
	yakuza->current_state = SLEEPING;
	printf("%lu %d is sleeping\n", yakuza->trd.now, yakuza->position);
	usleep(yakuza->trd.time_to_sleep * 1000);
	if (!is_yakuza_alive(yakuza))
		return ;
	yakuza->current_state = THINKING;
	printf("%lu %d is thinking\n", yakuza->trd.now, yakuza->position);
	yakuza->priority = LOW;
}
