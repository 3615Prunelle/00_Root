/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sophie <sophie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:25:46 by schappuy          #+#    #+#             */
/*   Updated: 2025/08/20 17:21:18 by sophie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
lst: The address of a pointer to a node.
f: The address of the function applied to each node’s content.
del: The address of the function used to delete a node’s content if needed.
Return : The new list. NULL if the allocation fails.
Use : Malloc / Free
Iterates through the list ’lst’,
	applies the function ’f’ to each node’s content,
	and creates a new list resulting of the successive applications of the function ’f’.
The ’del’ function is used to delete the content of a node if needed.
*/

#include "libft.h"

void	*f(void *param);

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*list_copy;
	t_list	*new_node;
	void	*malloc_check;

	// Creating a pointer to the new list (also its first node)
	if (lst == NULL || *f == NULL || del == NULL)
		return (NULL);
	// malloc du node + contenu (via f) dans new_node
	// FREE : in main avec lstclear
	malloc_check = f(lst->content);
	list_copy = ft_lstnew(malloc_check);
	if (!list_copy)
	{
		del(malloc_check);
		return (NULL);
	}
	lst = lst->next;
	// Now that the 1st node has been copied (+ pass in f function),
	// I can loop from node 2
	while (lst != NULL)
	{
		// Je creee un ptr vers le return de f(lst->content) au cas ou
		// besoin de liberer le malloc si soucis avec ft_lstnew
		malloc_check = f(lst->content);
		new_node = ft_lstnew(malloc_check);
		if (!new_node)
		{
			// Clear the whole list (node + content) if node issue
			del(malloc_check);
			ft_lstclear(&list_copy, del);
			return (NULL);
		}
		// Linker les nodes dans la nouvelle liste
		ft_lstadd_back(&list_copy, new_node);
		lst = lst->next;
	}
	return (list_copy);
}

/* void *f(void *param)
{
	int	*mod;

	mod = malloc(sizeof(int));
		// ne pas utiliser sur la list d'origine sinon je perds le pointeur d’origine
		// (celui que j'ai malloc plus tôt dans main) = ne peux plus free proprement
		// les anciens x, y, z
	if (!mod)
		return (NULL);
	*mod = *((int *)param);
	*mod += 1;
	return((void *)(mod));
}

int	main(void)
{
	int *x = malloc(sizeof(int)); // FREE : End of main (ft_lstclear)
	int *y = malloc(sizeof(int));
	int *z = malloc(sizeof(int));

	*x = 100;
	*y = 200;
	*z = 300;

	t_list *node1;
	t_list *node2;
	t_list *node3;

	node1 = ft_lstnew(x);  // FREE : End of main (ft_lstclear)
	node2 = ft_lstnew(y);
	node3 = ft_lstnew(z);

	ft_lstadd_back(&node1, node2);
	ft_lstadd_back(&node1, node3);

	t_list	*loop_ptr;
	int i = 1;
	loop_ptr = node1;
	while (loop_ptr != NULL)
	{
		printf("Node[%d] : %d - Address [%p] Next [%p]\n", i,
			*((int*)loop_ptr->content), loop_ptr, loop_ptr->next);
		loop_ptr = loop_ptr->next;
		i++;
	}
	// Creating a new list with updated content
	t_list *new_list;
	new_list = ft_lstmap(node1, f, del);
	printf ("\n⋅.˳˳.⋅ॱ˙˙ॱ⋅.˳˳.⋅ॱ˙˙ॱᐧ.˳˳.⋅Pass in lstmap⋅.˳˳.⋅ॱ˙˙ॱ⋅.˳˳.⋅ॱ˙˙ॱᐧ.˳˳.⋅\n\n");
	i = 1;
	loop_ptr = node1;
	while (loop_ptr != NULL)
	{
		printf("Initial list (unchanged) :	Node[%d] : %d - Address [%p] Next
			[%p]\n", i, *((int*)loop_ptr->content), loop_ptr, loop_ptr->next);
		loop_ptr = loop_ptr->next;
		i++;
	}
	printf ("\n");
	i = 1;
	loop_ptr = new_list;
	while (loop_ptr != NULL)
	{
		printf("Copy with f function applied :	Node[%d] : %d - Address [%p]
			Next [%p]\n", i, *((int*)loop_ptr->content), loop_ptr, loop_ptr->next);
		loop_ptr = loop_ptr->next;
		i++;
	}
	printf ("\n");
	ft_lstclear(&node1, del);
	ft_lstclear(&new_list, del);

	return(0);
} */
