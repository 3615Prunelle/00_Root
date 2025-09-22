#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

// ‼️ Global variables are forbidden

// ⚪ #define
# define NC "\e[0m"
# define YELLOW "\e[1;33m"
# define GREEN "\e[1;32m"
# define BLUE "\e[1;34m"
# define MAGENTA "\e[1;35m"
# define RED "\e[1;31m"
# define CYAN "\e[1;36m"

# define AVAILABLE 1
# define TAKEN 0
# define EATING 'E'
# define THINKING 'T'
# define SLEEPING 'S'

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

// ⚪ Structs
typedef struct	one_bro
{
	pthread_t		thread_ID;
	int				position;
	char			current_state;
	pthread_mutex_t	right_chopstick;
	pthread_mutex_t	left_chopstick;
	int				total_yakuzas;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned long	time_to_die;
	int				how_many_meals;					// Optional argument
}				one_bro;

// ⚪ Functions signatures - Part 1
void	*chopsticks_party(void *arg);
one_bro	*previous_bro(one_bro *this_yakuza, one_bro	*previous_yakuza);
one_bro	*next_bro(one_bro *this_yakuza, one_bro	*next_yakuza);
bool	can_yakuza_eat(one_bro *this_yakuza);

// ⚪ Functions signatures - Part 2
// ⚪ Clean up functions

// ⚪ Test functions
void	print_yakuzas_status(one_bro *this_yakuza);

# endif
