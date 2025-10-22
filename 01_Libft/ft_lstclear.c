/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sophie <sophie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:25:46 by schappuy          #+#    #+#             */
/*   Updated: 2025/08/20 17:43:32 by sophie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
lst: The address of a pointer to a node.
del: The address of the function used to delete the content of the node.
Return : None
Use : free
Deletes and frees the given node and all its successors,
	using the function ’del’ and free.
Finally, set the pointer to the list to NULL.
*/

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*loop_ptr;
	t_list	*backup_next;

	if (!lst || !del)
		return ;
	loop_ptr = *lst;
	while (loop_ptr != NULL)
	{
		// Backup of the next node address before it gets deleted
		backup_next = loop_ptr->next;
		ft_lstdelone(loop_ptr, del);
		loop_ptr = backup_next;
	}
	// No need to free all nodes because lstclear takes care of it
	*lst = NULL;
}

/* int	main(void)
{
	int *a = malloc(sizeof(int));
	// Je declare un ptr vers un int, que je malloc pour y mettre un int
	int *b = malloc(sizeof(int));
	int *c = malloc(sizeof(int));
	int *d = malloc(sizeof(int));

	*a = 40;
	// Je dereference ce pointeur pour y mettre une valeur
	*b = 41;
	*c = 42;
	*d = 43;

	t_list *node1;
	// Je declare un ptr vers un node
	t_list *node2;
	t_list *node3;
	t_list *node4;

	node1 = ft_lstnew(a);
	// J'attribue un int a ce node, en lui communiquant son adresse
	// (RAPPEL : 'a' est un pointeur, donc une adresse)
	// NB : il est normal qu'on ne voie pas l'int dans la memoire,
	// car a/b/c/d sont des pointeurs, et pas les ints
	// On peut cependant voir la donnee en hexadecimal
	node2 = ft_lstnew(b);
	node3 = ft_lstnew(c);
	node4 = ft_lstnew(d);

	ft_lstadd_back(&node1, node2);
	// Je fais correspondre les 4 nodes pour qu'ils soient
	// les uns a la suite des autres
	ft_lstadd_back(&node1, node3);
	ft_lstadd_back(&node1, node4);

	t_list *num_trip;
	// formule classique pour looper entre les nodes
	// et checker si tout est correct
	num_trip = node1;
	int i = 1;
	while ((num_trip != NULL))
	// Et non pas num_trip->next, car sinon on n'affichera pas le dernier node
	{
		printf("Node [%d] - [%d]\n", i, *((int *)(num_trip->content)));
		// Il faut caster ET derefencer l'int pour qu'il s'affiche
		i++;
		num_trip = num_trip->next;
	}

	// Let's free all nodes from 2
	// like for lstdelone, need to change the next address of the previous node
	node1->next = NULL;
	ft_lstclear(&node2, del);
	printf ("\n˳.⋅ॱ˙˙ॱᐧ.˳˳.⋅Pass in lstclear from node 2˳.⋅ॱ˙˙ॱᐧ.˳˳.⋅\n\n");
	num_trip = node1;
	i = 1;
	while ((num_trip != NULL))
	{
		printf("Node [%d] - [%d]\n", i, *((int *)(num_trip->content)));
		i++;
		num_trip = num_trip->next;
	}
	printf ("\n");
	free(node1);
	return(0);
} */
