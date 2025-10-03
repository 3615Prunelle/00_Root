#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

// ‼️ Global variables are forbidden

// ⚪ #define
# define NC "\e[0m"
# define BLUE "\e[1;34m"
# define S_BLUE "\e[34m"
# define MAGENTA "\e[1;35m"
# define YELLOW "\e[1;33m"
# define RED "\e[1;31m"
# define GREEN "\e[1;32m"
# define CYAN "\e[1;36m"

# define ERROR_MESSSAGE_01	"TBD\n"

// ‼️ Si je mets des paths, mettre le chemin RELATIF depuis le dossier d'ou sera lancée la commande. Ce chemin est différent selon si je suis :
// - Sur mon PC perso
// - Sur l'ordi du campus
// ET selon si je :
// - Fais 'make' depuis le dossier du projet (path from projet folder)
// - Compile via VSCode (path from workspaceFolder)

// ⚪ #include
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <limits.h>
# include <string.h>
# include <pthread.h>
#include <sys/time.h>								// For struct timeval struct

// ⚪ Enums
typedef enum e_states
{
	EATING,
	THINKING,
	SLEEPING,
	DEAD
}			state;

typedef enum e_prio
{
	HIGH,
	LOW
}			prio;

typedef pthread_mutex_t mutex_t;

// ⚪ Structs
typedef struct	time_related_data
{
	unsigned long	millisec_timestamp_start_dinner;
	unsigned long	millisec_cropped_start_dinner;

	unsigned long	millisec_timestamp_now;
	unsigned long	millisec_cropped_now;

	unsigned long	millisec_timestamp_last_meal;
	unsigned long	millisec_cropped_last_meal;

	unsigned long	millisec_elapsed_since_last_meal;

	unsigned long	time_to_eat_in_ms;
	unsigned long	time_to_sleep_in_ms;
	unsigned long	time_to_die_in_ms;
}				time_related_data;

// typedef struct	one_bro;

typedef struct	one_bro
{
	int					position;
	pthread_t			thread_ID;
	state				current_state;
	prio				priority;
	mutex_t				*left_chopstick;
	mutex_t				*right_chopstick;
	mutex_t				*dead_flag;
	bool				*party_is_on;
	int					total_yakuzas;
	int					how_many_meals;					// Optional argument
	time_related_data	TRD;
}				one_bro;

// ⚪ Functions signatures - Actions
void	*itadakimasu(void *arg);
void	take_chopsticks_and_eat(one_bro *this_yakuza, mutex_t *first_chopstick_to_take, mutex_t *second_chopstick_to_take);
void	sleep_till_think(one_bro *this_yakuza);

// ⚪ Functions signatures - Helpers
bool	is_yakuza_alive(one_bro *this_yakuza);
prio	set_priority(one_bro *this_yakuza);
void	update_timestamp_last_meal(one_bro *this_yakuza);
bool	dead_mutex(mutex_t *death_verif);
bool	is_party_on(one_bro *this_yakuza);

// ⚪ Clean up functions

# endif
