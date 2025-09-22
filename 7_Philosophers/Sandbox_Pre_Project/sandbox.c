#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

# define NC "\e[0m"
# define YELLOW "\e[1;33m"
# define GREEN "\e[1;32m"
# define BLUE "\e[1;34m"
# define MAGENTA "\e[1;35m"
# define RED "\e[1;31m"
# define CYAN "\e[1;36m"
// int j = 0;
	pthread_mutex_t	mutex;

// A thread function takes a void pointer, and returns a void pointer
void *sandbox_thread(void *data)
{
	int	*int_to_incr = data;
	pthread_t	which_ID_is_curently_here;
	which_ID_is_curently_here = pthread_self();			// Pour savoir quel ID est rentré cette fois

	printf("%sValue is [%d]\tID [%lu] - About to enter the loop\n%s", MAGENTA, *int_to_incr, which_ID_is_curently_here, NC);
	for (size_t i = 0; i < 10000000; i++)
	{
		pthread_mutex_lock(&mutex);		// Does 3 things : checks if the lock has been locked (but another thread), if so, it waits until it's unlocked, and set it to 'lock' once unlocked
		(*int_to_incr)++;				// NB : cette variable sera incrémentée sur 2 threads one and off, même si on utilise mutex. Seul le resultat compte
		pthread_mutex_unlock(&mutex);	// goes with pthread_mutex_lock
	}
	printf("%sValue is [%d]\tID [%lu] - Out of loop\n%s", MAGENTA, *int_to_incr, which_ID_is_curently_here, NC);

	// printf("%sj is [%d]\tID [%lu] - About to sleep for 2 secs\n%s", MAGENTA, j, which_ID_is_curently_here, NC);
	// sleep(2);
	// j++;
	// printf("%sj is [%d]\tID [%lu] - Slept for 2 secs\n%s", MAGENTA, j, which_ID_is_curently_here, NC);
	// printf("%sID [%lu] found j at this value : [%d] - About to enter a loop\n%s", MAGENTA, which_ID_is_curently_here, j, NC);
	// // Process A peut entrer avant Process B, mais en sortir apres
	// for (size_t i = 0; i < 1000000; i++)
	// {
	// 	j++;
	// }
	// printf("%sID [%lu] left j at this value : [%d] - Out of the loop\n%s", MAGENTA, which_ID_is_curently_here, j, NC);
	return (NULL);
}

int main(void)
{
	pthread_t	ID_1;
	pthread_t	ID_2;
	int			integer_to_increment = 1;
	pthread_mutex_init(&mutex, NULL);			// Make the mutex possibility available. Useless if used alone, has to be completed by other mutex functions

	printf("%sFirst value is [%d]\n%s", YELLOW, integer_to_increment, NC);

	// A partir de la, l'ensemble forme un tout execute' randomly
	// Le 1er thread s'executera toujous en 1er, donc il se terminera également en 1er. L'impact de pthread_join sur ce thread ne sera pas visible car ce thread finira avant les autres, qu'on le join ou non
	pthread_create(&ID_1, NULL, &sandbox_thread, &integer_to_increment);		// Lui passer la fonction sandbox_thread ou un pointeur (&sandbox_thread) revient au meme
	pthread_create(&ID_2, NULL, &sandbox_thread, &integer_to_increment);
	printf("%s(In Main) Value right after threads creation is [%d]\n%s", CYAN, integer_to_increment, NC);
	printf("%sID_1 is [%lu]\tID_2 is [%lu]\n%s", RED, ID_1, ID_2, NC);

	pthread_join(ID_1, NULL);	// Bloque la thread appelant (ici : main) tant que ID_1 n'est pas fini
	pthread_join(ID_2, NULL);

	printf("%sValue is [%d]\n%s", GREEN, integer_to_increment, NC);
	printf("%sValue is [%d]\n%s", BLUE, integer_to_increment, NC);

	// The 2 threads have been joined (= they finished their execution), nothing else can happen from here
	pthread_mutex_destroy(&mutex);
	printf("%sValue is [%d]\n%s", YELLOW, integer_to_increment, NC);

	return (0);
}
//  -------- Test pour connaitre le temps écoulé entre 2 actions -------------------------------------------------------------------------- |
	// struct timeval tv;
	// gettimeofday(&tv, NULL);
	// printf("Seconds: %ld, Microseconds: %ld\n", tv.tv_sec, tv.tv_usec);
	// sleep(1);
	// gettimeofday(&tv, NULL);
	// printf("Seconds: %ld, Microseconds: %ld\n", tv.tv_sec, tv.tv_usec);
//  --------------------------------------------------------------------------------------------------------------------------------------- |
// //  -------- Test pour connaitre l'ID du thread principal (celui qui execute main), et demonstration qu'on ne peut pas le join --------- |
// 	pthread_t main_thread = pthread_self();
// 	printf("Main thread id = %lu\n", main_thread);
// 	int ret = pthread_join(main_thread, NULL);
// 	if (ret != 0)
// 		printf("pthread_join failed with code %d\n", ret);
// //  ------------------------------------------------------------------------------------------------------------------------------------ |
