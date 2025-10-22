/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sophie <sophie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:25:46 by schappuy          #+#    #+#             */
/*   Updated: 2025/08/20 17:23:01 by sophie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
lst: The beginning of the list
Return : Last node of the list
*/

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*last;

	// Creating a ptr to the node I'll return (aka last one)
	if (!lst)
		return (NULL);
	// Giving 'last' the same address as the head node,
	// so it starts the loop at the right place
	last = lst;
	// Leaving the loop at the node before the last node
	while (last->next != NULL)
	{
		last = last->next;
	}
	// When 'last.next' is NULL, means 'last' is the last node,
	// so I return a pointer to it
	return (last);
}
