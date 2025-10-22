/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sophie <sophie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:25:46 by schappuy          #+#    #+#             */
/*   Updated: 2025/08/20 17:53:44 by sophie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
lst: The address of a pointer to the first node of a list.
new: The address of a pointer to the node to be added.
Return : None
Adds the node ’new’ at the end of the list.
*/

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		// new->next = NULL; // NOPE, because 'new' may not be the last node
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
	// new->next = NULL; // NOPE, because 'new' may not be the last node
}
/* int	main(void)
{
	char *zucchine = ft_strdup("Zucchine");
	char *melanzane = ft_strdup("Melanzane");
	char *pomodori = ft_strdup("Pomodori");

	t_list *alix; // designating this pointer for the head
	t_list *cleo;
	t_list *mira;

	alix = ft_lstnew(zucchine);
	cleo = ft_lstnew(melanzane);
	mira = ft_lstnew(pomodori);

	ft_lstadd_back(&alix, cleo);
	ft_lstadd_back(&alix, mira);

	t_list *loop_ptr = alix;
	int node = 1;
	while (loop_ptr != NULL)
	{
		printf("Node [%d] - Address [%p] - Content [%s] - Next [%p]\n", node,
			loop_ptr, (char *)loop_ptr->content, loop_ptr->next);
		node++;
		loop_ptr = loop_ptr->next;
	}

	printf ("\nॱ˙˙ॱᐧ.˳˳.⋅3rd Pass in lstadd_backॱ˙˙ॱᐧ.˳˳.⋅\n\n");

	t_list *isidor;
	isidor = ft_lstnew(ft_strdup("It's the final countdooooooooooown"));
	ft_lstadd_back(&alix, isidor);

	loop_ptr = alix;
	node = 1;
	while (loop_ptr != NULL)
	{
		printf("Node [%d] - Address [%p] - Content [%s] - Next [%p]\n", node,
			loop_ptr, (char *)loop_ptr->content, loop_ptr->next);
		node++;
		loop_ptr = loop_ptr->next;
	}
	printf ("\n");
	ft_lstclear(&alix, del);
	return(0);
} */
