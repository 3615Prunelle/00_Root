/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 16:13:16 by sophie            #+#    #+#             */
/*   Updated: 2025/10/08 17:55:44 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

// ⚪ #define
# define NC "\e[0m"
# define BLUE "\e[1;34m"
# define S_BLUE "\e[34m"
# define MAGENTA "\e[1;35m"
# define S_MAGENTA "\e[35m"
# define YELLOW "\e[1;33m"
# define S_YELLOW "\e[33m"
# define RED "\e[1;31m"
# define S_RED "\e[31m"
# define GREEN "\e[1;32m"
# define S_GREEN "\e[32m"
# define CYAN "\e[1;36m"
# define S_CYAN "\e[36m"

# define ERROR_MSG "Wrong Input - Please provide valid arguments\n"

// ⚪ #include
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

// ⚪ Enums
typedef enum t_states
{
	TOOK_CHOPSTICK,
	EATING,
	THINKING,
	SLEEPING,
	DEAD
}						t_state;

typedef enum t_prio
{
	HIGH,
	LOW
}						t_prio;

typedef pthread_mutex_t	t_mutex;

// ⚪ Structs

typedef struct t_input
{
	int					amount_of_yakuzas;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					eat_plus_sleep;
	int					mid_thinking_time;
	int					number_of_times_each_philosopher_must_eat;
}						t_input;

typedef struct t_time_related_data
{
	unsigned long		now;
	unsigned long		timestamp_last_meal;
	int					elapsed_since_meal;
	int					time_to_eat;
	int					time_to_sleep;
	int					time_to_die;
	int					eat_plus_sleep;
	int					mid_thinking_time;
}						t_time_related_data;

typedef struct t_yaks
{
	int					position;
	pthread_t			thread_id;
	t_state				current_state;
	t_prio				priority;
	t_mutex				*left_chpstk;
	t_mutex				*right_chpstk;
	t_mutex				*dead_flag;
	t_mutex				*you_shall_not_pass;
	bool				*party_is_on;
	int					total_yakuzas;
	int					meals_count;
	t_time_related_data	trd;
}						t_yaks;

// ⚪ Functions signatures - Setup
t_input					input_setup(int ac, char **av, t_input *input,
							unsigned long now_in_millisec);
void					mutex_init(t_mutex *all_mutex, t_input *input);
void					yakuza_array_setup(t_yaks *yakuza,
							t_input *input, bool *party_on,
							unsigned long now_in_millisec);
void					mutex_setup(t_yaks *yakuza, t_input *input,
							t_mutex *all_mutex);
pthread_t				threads_setup(t_yaks *yakuza, t_input *input);

// ⚪ Functions signatures - Routines & Actions
void					*itadakimasu(void *arg);
void					*monitor(void *arg);
void					take_chopsticks_and_eat(t_yaks *yakuza,
							t_mutex *chopstick_1, t_mutex *chopstick_2);
void					sleep_till_think(t_yaks *yakuza);
void					print_and_change_status(t_state state, t_yaks *yakuza);

// ⚪ Functions signatures - Helpers
int						ft_atoi(const char *nptr);
unsigned long			get_timestamp(t_yaks *yakuza, bool update_last_meal);
t_prio					set_priority(t_yaks *yakuza);
int						copy_meal_count(t_yaks *yakuza, bool remove_one);
bool					is_party_on(t_yaks *yakuza);
bool					is_yakuza_alive(t_yaks *yakuza);
bool					is_dead(t_yaks *yakuza, bool death_confirmed);

// ⚪ Free Functions
void					free_both_chopsticks(t_mutex *chopstick_1,
							t_mutex *chopstick_2);
void					join_destroy_free(t_yaks *yakuza, t_mutex *all_mutex,
							pthread_t *monitor_san);

#endif
