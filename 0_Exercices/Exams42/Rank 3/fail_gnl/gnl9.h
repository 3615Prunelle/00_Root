#ifndef GNL_H
#define GNL_H

#include <unistd.h>	// read
//#include <string.h>	// strlen
#include <stdlib.h>	// malloc free
#include <stdio.h>	// printf perror
//#include <errno.h>	// perror
#include <stdbool.h>

// For open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 30
#endif

typedef struct node
{
	char		*buff;
	bool		newline_found;
	bool		eof_found;
	struct node	*next;
} 		node;

char    *get_next_line(int fd);
int	count_n(char s);
char	*copy_sz_chars(char *fin, char *s, int sz);
int	search_n_or_eof(node *n);	// Attention, return seulement index \n, pas \0
node	*add_buff(node *head);

#endif
