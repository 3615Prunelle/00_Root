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
	int		index_newline;
	int		index_eof;
	struct node	*next;
} 		node;

char    *get_next_line(int fd);
void    setup_indexes(node *n);
void    setup_node(node *n);
void    add_node_move_chars(node *head, node *dest);

#endif
