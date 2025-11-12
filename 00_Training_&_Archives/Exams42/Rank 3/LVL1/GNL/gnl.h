#ifndef GNL_H
#define GNL_H

#include <unistd.h>		// read
//#include <string.h>	// strlen
#include <stdlib.h>		// malloc free
#include <stdio.h>		// printf perror
//#include <errno.h>	// perror
#include <stdbool.h>

// For open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 10
#endif

char	*get_next_line(int fd);

#endif
