#include "gnl.h"

char    *get_next_line(int fd)
{
	int		read_ret;
	static bool	reset = true;

	static node	head;
	node		*backup_head = &head;

	if(reset)
	{
		setup_node(&head);
		read_ret = read(fd, head.buff, BUFFER_SIZE);		// reminder - reads regardless of \n
		if((read_ret <= 0) || (fd <= 0))
		{
			free(head.buff);
			printf("Nope\n");
			return(NULL);
		}
		printf("C'est parti : %s", head.buff);
		reset = false;						// set to true when need to read more
		setup_indexes(&head);
	}
	if(!reset)
	{
		// One node/line has been returned
		// Delete that node(and change head ptr address), or move contents (what happens with the last node ?)
		free(head.buff);
		backup_head = head.next;				// par defaut, indexes a -1, update that
		setup_indexes(backup_head);

	// Check si pas de faux \0 ou \n detecté en passant dans les if en dessous, puis set up la loop de read + new node tant qu'on a pas trouvé de \n ou \0
		/*
		node	new;
		setup_node(&new);
		head.next = &new;
		read_ret = read(fd, new.buff, BUFFER_SIZE);	// trouver une autre solution car le node analysé en dessous n'est plus le bon
		*/
	}

	// creer une boucle pour ne pas louper eof s'il arrive apres n read
	// verif \0 te \0 au debut/a la fin de la boucle

	if(head.index_eof >= 0)						// eof found
	{
		if(head.index_newline >= 0)
		{
			if(head.index_newline == head.index_eof-1)
			{
				return(head.buff);
			}
			else
			{
				node	new;
				setup_node(&new);
				add_node_move_chars(backup_head, &new);
				return(head.buff);			// Need to delete that node, or shift the content of next nodes to head
			}

		}
		else							// eof + no \n
		{
			return(head.buff);
		}
	}

	if(head.index_eof == -1)					// eof not found
	{
		if(head.index_newline >= 0)
		{
			node	new;
			setup_node(&new);
			add_node_move_chars(backup_head, &new);
			return(head.buff);			// Need to delete that node, or shift the content of next nodes to head
		}
		else
		{
			// read more - create new node and read
		}
	}
	return(NULL);	// Delete after debug
}

void	add_node_move_chars(node *head, node *dest)
{
	node	*last_node_ptr;
	last_node_ptr = head;
	while(last_node_ptr->next != NULL)
	{
		last_node_ptr = last_node_ptr->next;
	}
	// on est theoriquement au last node
	int	i = 0;
	int	backup = last_node_ptr->index_newline;
	last_node_ptr->next = dest;

	while(backup < BUFFER_SIZE)
	{
		dest->buff[i] = head->buff[backup+1];
		head->buff[backup+1] = '\0';
		backup++;
		i++;
	}
	// head will be the return string + as many \0 as necessary
	// dest will be a new string with potentially many \n and eof, or none, or only EOF
}

void	setup_indexes(node *n)
{
	int i = 0;
	while(i < BUFFER_SIZE)
	{
		if(n->buff[i] == '\n')
		{
			n->index_newline = i;
		}
		else if(n->buff[i] == '\0')
		{
			n->index_eof = i;
		}
		i++;
	}
}

void	setup_node(node *n)
{
	n->buff = malloc(sizeof(char) * BUFFER_SIZE + 1);	// Pour mettre le \0 si le dernier char read est un \n
	n->buff[BUFFER_SIZE] = '\0';
	n->index_newline = -1;
	n->index_eof = -1;
	n->next = NULL;
}

int	main(int argc, char **argv)
{
	int	fd;
	if((argc != 2) || argv[1][0] == '\0')
	{
		return(1);
	}
	// fd = argv[1]; // comment out when done
	fd = open("./test_gnl.txt", 0);
	
	char	*buffer;
	buffer = get_next_line(fd);
	printf("\n\nFinal :\t\t%s", buffer);
	fflush(stdout);

	while(buffer != NULL)
	{
		// free(buffer); // maybe no need because the node will be freed in gnl function ?
		buffer = get_next_line(fd);
		printf("\n\nNext line :\t%s", buffer);
		fflush(stdout);
	}
	return(0);
}

