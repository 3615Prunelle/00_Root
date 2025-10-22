/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sophie <sophie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:25:46 by schappuy          #+#    #+#             */
/*   Updated: 2025/08/20 17:38:02 by sophie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* NOTES :
void	(*del)(void *) = Un pointeur vers une fonction qui prend un void*
	en paramètre et ne retourne rien, donc un pointeur vers la
	fonction void	del(void *)
(*del) = variable appelée del qui pointe vers une fonction.
'int *ptr;' >> ptr est un pointeur vers un int
	|| 'void (*del)(...);' >> del est un pointeur vers une fonction
(void *) = pointeur générique en parametre, donc n’importe quel type de donnée.

Concept des callbacks. C’est comme dire : “Voici du contenu à détruire (node)
et la méthode (del) pour effacer son contenu.Peu importe ce que c’est, utilise
ce que je t’ai donné pour le gérer. ”ft_lstdelone n’a pas besoin de savoir
comment on détruit le contenu. Elle dit juste :“Passe-moi une fonction qui
sait le faire, et je l’appellerai quand il faudra.”

Step 1 : Fetch the data to erase (using 'node.content') - In this case,
	it would be ```lst->content``` because lst is a pointer, so I use the ->
Step 2 : Call the del function,
	giving the data to erase (Step 1) as a parameter.
!!! Make sure I'm not trying to free something that wasn't
dynamically allocated (crash).
Check if a malloc has been done on the actual content (not just the pointer) */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	// Free the pointer to the node, as it's been malloc'd in ft_lstnew
	if (lst)
	{
		//  Fetch the data to erase : `lst->content` (lst is a pointer,
		// so I use the -> instead of the .)
		del(lst->content);
		free(lst);
		//  Adding this to avoid dangling pointer
		lst = NULL;
		// this is actually useless, because it doesn't affect the original
		// pointer (because I'm changing a local copy of it).
		// A double ptr would work though
	}
}

// del function takes any kind of data as a parameter, and frees this data
void	del(void *param)
{
	if (param)
		free(param);
}

/* int	main(void)
{
	char *zucchine = "Zucchine";
	// no malloc here -> don't use lstclear at the end
	char *melanzane = "Melanzane";
	char *pomodori = "Pomodori";

	t_list *alix;
	// designating this pointer for the head
	t_list *cleo;
	t_list *mira;

	alix = ft_lstnew(zucchine);				// FREE : end of main
	cleo = ft_lstnew(melanzane);
	mira = ft_lstnew(pomodori);

	ft_lstadd_back(&alix, cleo);
	ft_lstadd_back(&alix, mira);

// Adding a last node that will be deleted
	t_list *isidor;
	char *fagioli = ft_strdup("Fagioli");
	// malloc (through strdup) on that string,
	// otherwise it will give problem when using free
	isidor = ft_lstnew(fagioli);
	ft_lstadd_back(&alix, isidor);

	t_list *loop_ptr = alix;
	int node = 1;
	while (loop_ptr != NULL)
	{
		printf("Node [%d] - Address [%p] - Content [%s] - Next [%p]\n", node,
			loop_ptr, (char *)loop_ptr->content, loop_ptr->next);
		node++;
		loop_ptr = loop_ptr->next;
	}
// Freeing the last created node
	mira->next = isidor->next;
	// Updating the previous node's next address to the next address
	// of the node we're about to delete (otherwise errors)
	ft_lstdelone(isidor, del);
	printf ("\n˙ॱᐧ.˳˳.⋅Pass in lstdelone to erase the last node˙ॱᐧ.˳˳.⋅\n\n");
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
	free(alix);
	free(cleo);
	free(mira); // if double free issue, comment out the last node
	return(0);
} */
