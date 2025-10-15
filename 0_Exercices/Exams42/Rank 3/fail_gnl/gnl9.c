#include "gnl.h"

char    *get_next_line(int fd)
{
	char	*final;

	int	read_ret;
	int	index_backup;

	static node	new_node;
	node		*backup_head = &new_node;
	new_node.next = NULL;
	new_node.buff = malloc(sizeof(char) * BUFFER_SIZE);
	read_ret = read(fd, new_node.buff, BUFFER_SIZE);	// reminder - reads regardless of \n
	printf("Init : %s", new_node.buff);

	if((read_ret <= 0) || (fd <= 0))
	{
		free(new_node.buff);
		printf("Nope\n");
		return(NULL);
	}
	if(read_ret < BUFFER_SIZE)	// Attention, il peut y avoir plusieurs \n + \0 anyway
	{
		// identifier combien de /n
		if(count_n(new_node.buff) < 1)	// EOF
		{
			return(new_node.buff);	// Memory is ok because ptr will be freed by main, regardless of the size
		}
		else if(count_n(new_node.buff) == 1)	// Attention, il peut etre suivi d'un \0
		{
			index_backup = search_n_or_eof(new_node.buff);
			final = malloc(sizeof(char) * (index_backup + 2));	// Car /0 pas compté
			final = copy_sz_chars(final, new_node.buff, index_backup + 2);
		}
		if(count_n(new_node.buff) > 1)
		{
			// Faire une fonction pour separer avant et apres \n dans 2 nodes
			// une fois le reste mis dans le 2eme node, il doit etre gardé en mémoire pour le prochain passage
			// mettre la linked list en static ?
			index_backup = search_n_or_eof(new_node.buff);
			final = malloc(sizeof(char) * (index_backup + 2));	// Car /0 pas compté
			final = copy_sz_chars(final, new_node.buff, index_backup + 2);
		}




		final = malloc(sizeof(char) * (read_ret + 1));	// Car /0 pas compté
		final = smaller_than_buffer(new_node.buff, read_ret);
		free(new_node.buff);
	}
	
	else if(read_ret == BUFFER_SIZE)		// soit on est a la fin, soit il y a + a lire
	{
		index_backup = search_n_or_eof(&new_node);
		if(index_backup == BUFFER_SIZE - 1)	// on est pile a la fin d'une ligne OU du doc
		{
			if(new_node.newline_found == true)
			{
				final = malloc(sizeof(char) * read_ret + 1);
				
			}
						// malloc + 1 de final si \n ou garder size si \0, duplicate puis return

			
		}
		else if(index_backup == -1)
		{
			while(search_n_or_eof(&new_node) == -1)
			{
				// + à lire = rajouter node etc
				// update adresse du node a la fin de la boucle
			}
		
		}
		else
		{
			// on a un \n ou \0 au millieu du buffer, mettre la suite dans un new node
		}
	}

// qwerty\n = read 7
// buffer_size = 7

	// fonction final = joindre tous les buffers a la suite de head à last
	return(final);
}
/*
node	*add_buff(node *head)
{
	// 
}
*/

int	search_n_or_eof(node *n)	// Attention, return seulement index \n, pas \0
{
	int	i = 0;
	int	index_to_return = -1;
	bool	first_found = false;
	n->newline_found = false;
	n->eof_found = false;

	while(i < BUFFER_SIZE)
	{
		if(n->buff[i] == '\n')
		{
			n->newline_found = true;
			if(first_found == false)
			{
				index_to_return = i;
				first_found = true;
			}
		}
		else if(n->buff[i] == '\0')
		{
			if(first_found == false)
			{
				index_to_return = i;
				n->eof_found = true;
				return(index_to_return);
			}
		}
		i++;
	}
	return(index_to_return);
}

int	count_n(char s)
{
	int	i = 0;
	int	counter = 0;
	while(s[i] != '\0')
	{
		if((s[i] >= ' ') && (s[i] <= '~'))
		{
			i++;
		}
		else if(s[i] == '\n')
		{
			i++;
			counter++;
		}
	}
	return(counter);
}

char	*copy_sz_chars(char *fin, char *s, int sz)
{
	// Normalement, la bonne quantité de mémoire a été allouée à 'fin'
	int i = 0;

	while(i < sz)
	{
		if((s[i] >= ' ') && (s[i] <= '~'))
		{
			fin[i] = s[i];
			i++;
		}
		else if(s[i] == '\n')
		{
			fin[i] = s[i];
			fin[i+1] = '\0';
			return(fin);
		}
		else if(s[i] == '\0')
		{
			fin[i] = s[i];
		}
	}
	return(fin);
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
	printf("Final : %s", buffer);
	fflush(stdout);
	return(0);
}

