#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

// ‼️ Global variables are forbidden

// ⚪ #define
# define NC "\e[0m"
# define BLUE "\e[1;34m"
# define MAGENTA "\e[1;35m"
# define YELLOW "\e[1;33m"
# define RED "\e[1;31m"
# define GREEN "\e[1;32m"
# define CYAN "\e[1;36m"

# define LEFT 'l'
# define RIGHT 'r'
# define BOTH 'b'
# define NONE '-'

// Later : use ASCII Values otherwise Norminette gives a false positive :
// "Preprocessor statement must only contain constant defines"
# define EATING 'E'
# define THINKING 'T'
# define SLEEPING 'S'
# define DEAD 'D'

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
#include <sys/time.h>								// For timeval struct

// ⚪ Structs
typedef struct	one_bro
{
	int				position;
	pthread_t		thread_ID;
	char			current_state;
	pthread_mutex_t	*left_chopstick;
	pthread_mutex_t	*right_chopstick;
	int				total_yakuzas;
	unsigned long	timestamp_start_dinner_in_millisec;
	unsigned long	timestamp_last_meal;
	bool			has_right_chopstick;
	bool			has_left_chopstick;
	unsigned long	time_to_eat_in_ms;
	unsigned long	time_to_sleep_in_ms;
	unsigned long	time_to_die_in_ms;
	int				how_many_meals;					// Optional argument
}				one_bro;

// ⚪ Functions signatures - Part 1
void			*itadakimasu(void *arg);
struct timeval	get_time_print_action_set_status(one_bro *this_yakuza, char chopstick, char current_status);

one_bro	*previous_bro(one_bro *this_yakuza, one_bro	*previous_yakuza);
one_bro	*next_bro(one_bro *this_yakuza, one_bro	*next_yakuza);

// ⚪ Functions signatures - Part 2
// ⚪ Clean up functions

// ⚪ Test functions
void	print_yakuzas_status(one_bro *this_yakuza);

# endif
