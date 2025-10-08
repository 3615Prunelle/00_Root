#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <ctype.h>

/*
*/

#include "list.h"

int		compare(void *a, void *b)
{
	char	conv1 = *(char*)a;
	char	conv2 = *(char*)b;
	return(conv1 != conv2);
}

void	ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
	t_list	*backup = *begin_list;
	t_list	*backup_previous = NULL;
	t_list	*backup_next = NULL;

	while(backup != NULL)
	{
		if(!cmp(backup->data, data_ref))
		{
			if(backup_previous == NULL)										// Cas où le 1er node est à supprimer
			{
				*begin_list = backup->next;
				backup = backup->next;
			}
			else if((backup_previous != NULL) && (backup->next != NULL))	// Cas où on est au millieu
			{
				backup_previous->next = backup->next;
				backup = backup->next;
			}
			else if(backup->next == NULL)									// Cas où on est à la fin
			{
				backup_previous->next = NULL;
				backup = NULL;
			}
		}
		else
		{
			backup_previous = backup;
			backup = backup->next;
		}
	}
}

int		main(void)
{
	char	c1 = 'j';
	char	c2 = 's';
	char	c3 = 'm';
	char	c4 = 'z';

	t_list	pink = {NULL, &c1};
	t_list	blue = {&pink, &c2};
	t_list	green = {&blue, &c3};
	t_list	red = {&green, &c4};

	t_list	*head = &red;

	t_list *loop = head;
	while(loop != NULL)
	{
		printf("Before - Letter : %c\n", *(char*)loop->data);
		loop = loop->next;
	}

	char	to_remove = 's';
	ft_list_remove_if(&head, &to_remove, compare);
	loop = head;
	while(loop != NULL)
	{
		printf("After - Letter : %c\n", *(char*)loop->data);
		loop = loop->next;
	}
	return(0);
}

/*
// MAIN BY CHAT GPT

t_list *new_node(char c)
{
    t_list *node = malloc(sizeof(t_list));
    node->data = malloc(sizeof(char));
    *(char*)node->data = c;
    node->next = NULL;
    return node;
}

void print_list(t_list *lst)
{
    while (lst)
    {
        printf("%c -> ", *(char*)lst->data);
        lst = lst->next;
    }
    printf("NULL\n");
}

// --- Main ---
int main(void)
{
    // Création de la liste: A -> B -> C -> B -> D -> NULL
    t_list *head = new_node('A');
    head->next = new_node('B');
    head->next->next = new_node('C');
    head->next->next->next = new_node('B');
    head->next->next->next->next = new_node('D');

    printf("Liste avant suppression:\n");
    print_list(head);

    char target = 'Q';
    ft_list_remove_if(&head, &target, compare);

    printf("Liste après suppression de '%c':\n", target);
    print_list(head);

    return 0;
}
*/
