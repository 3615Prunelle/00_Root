/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sophie <sophie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:25:46 by schappuy          #+#    #+#             */
/*   Updated: 2025/08/20 17:23:38 by sophie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
lst: The address of a pointer to a node.
f: The address of the function to apply to each node’s content.
Iterates through the list ’lst’ and applies the function ’f’ to the content of each node.
*/

#include "libft.h"

void	f(void *param);

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*yolo_ptr;

	if (!lst || !f)
		return ;
	yolo_ptr = lst;
	while (yolo_ptr != NULL)
	{
		f(yolo_ptr->content);
		yolo_ptr = yolo_ptr->next;
	}
}

/* void	f(void *param)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *)param;
	while(str[i] != '\0')
	{
		str[i] = ft_toupper(str[i]);
		i++;
	}
}
int	main(void)
{
	char *zucchine = ft_strdup("Pluton");
		//strdup (copie modifiable) sinon c'est une chaîne en read-only (pas le droit d’écrire dessus
		/comportement indéfini) - Penser a free !
	char *melanzane = ft_strdup("Jupiter");
	char *pomodori = ft_strdup("Saturn");

	t_list *alix;
	t_list *cleo;
	t_list *mira;

	alix = ft_lstnew(zucchine);
	cleo = ft_lstnew(melanzane);
	mira = ft_lstnew(pomodori);

	ft_lstadd_front(&alix, cleo);
	ft_lstadd_front(&alix, mira);

	t_list *loop_ptr = alix;
	int node = 1;
	while (loop_ptr != NULL)
	{
		printf("Node [%d]	Address [%p]	Content [%s]	Next	[%p]\n",
							node, loop_ptr, (char *)loop_ptr->content,
							loop_ptr->next);
		node++;
		loop_ptr = loop_ptr->next;
	}
// Every content goes uppercase WHOOHOOOOOO
	ft_lstiter(alix, f);
	printf ("\n⋅.˳˳.⋅ॱ˙˙ॱ⋅.˳˳.⋅ॱ˙˙ॱᐧ.˳˳.⋅Pass in lstiter
		- Every content goes uppercase WHOOHOOOOOO⋅.˳˳.⋅ॱ˙˙ॱ⋅.˳˳.⋅ॱ˙˙ॱᐧ.˳˳.⋅\n\n");
	loop_ptr = alix;
	node = 1;
	while (loop_ptr != NULL)
	{
		printf("Node [%d]	Address [%p]	Content [%s]\n", node, loop_ptr,
					(char *)loop_ptr->content, loop_ptr->next);
		node++;
		loop_ptr = loop_ptr->next;
	}
	printf ("\n");
	ft_lstclear(&alix, del);
		//using this instead of free(node) to free also the content of each node,
		because I used malloc on them
	return(0);
} */
