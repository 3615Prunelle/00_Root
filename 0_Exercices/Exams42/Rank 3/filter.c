#include <unistd.h>	// Read
#include <string.h>
#include <stdlib.h>	// Malloc
#include <stdio.h>
#include <errno.h>

int	main(int argc, char **argv)
{
	char *s;
	char *to_read;

	if(argc != 2)
	{
		printf("1\n");
		return(1);
	}
	s = malloc(strlen(argv[1]));
	if(!s)
	{
		perror("Malloc Fail\n");
	}
	printf("Ok\n");
		
	// read(0, 

}

