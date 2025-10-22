/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sophie <sophie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 21:58:40 by schappuy          #+#    #+#             */
/*   Updated: 2025/08/20 17:52:57 by sophie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* NOTES :
**lst is declared in the parameters of that function.
That means, from from now on :
lst = pointer to the pointer to the first node (t_list **)
*lst = pointer to the current first node (t_list *), aka "head"
	- After the pass in this function,
	it will point to another node (the updated first one)
**lst = the actual node (t_list struct: content, next)
	- Because dereferencing twice
!! And not the other way around
	- Because it has been declared in the function parameters

same for new, in the function :
new = node to insert before **lst
*new = address of new (dereferencing the node)

What happens in that function : both nodes get linked.
New being placed in front of **lst : new >> **lst,
hence becoming the new head */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	//  Link 'new' node to 'lst' (which is the pointer to the first node)
	new->next = *lst;
	// *lst is on the right (of the = sign) >> we access the value
	//  Make 'new' node the new head of the list
	*lst = new;
	// *lst is on the left >> we access the pointer
}

/* int	main(void)
{
	char *test_string1 = "Dublin";
	char *test_string2 = "London";
	char *test_string3 = "Lisbon";

	t_list	*head;	// This is a ptr to the head (1st node) of the list
// At this point, this pointer is not initialized, so its
// values are random (undefined behavior if I use it)
// I'll use ft_lstnew to add content in it

	head = ft_lstnew(test_string3);
	// NB : ft_lstnew creates a brand new node,
	// and that node receives the content
	printf("Address of a node : [%p] - Address of next
		node (should be NULL): %p\n", head, head->next);
	printf("Content of that node : [%s]\n\n", (char *)head->content);

	t_list	*second_node;
	// This is only a pointer to a node, not the node itself
	// (however, we can access the node by dereferencing it)
	second_node = ft_lstnew(test_string2);
	// This function will put content at the address
	// stored in 'second_node' pointer
	printf("Address of another node : [%p] - Address of next node (should be
		NULL): %p\n", second_node, second_node->next);
	printf("Content of that node : [%s]\n", (char *)second_node->content);
// at this stage, both nodes aren't connected, but they both have content
// and both point to NULL, because it's what ft_lstnew does
// that's what we'll do below : connecting them.
// 'second node' will come in front and become first
	ft_lstadd_front(&head, second_node);
	// &head = address of head, which is a t_list * (pointer to t_list)
	printf ("\n˙ॱᐧ.˳˳.⋅Pass in lstadd_front to place the
		second node in front˙ॱᐧ.˳˳.⋅\n\n");
	printf("Address of 1st node (head) : [%p] - Address of next node: [%p]\n",
		head, head->next);
	printf("Content of 1st node : [%s]\n\n", (char *)head->content);
// now, head and second_node have the exact same address,
// because it's what ft_lstadd_front does.
// to access the second node, we need to go through the head and go next :
	printf("Address of 2nd node : [%p] - Address of next node: [%p]\n",
		 head->next, head->next->next);
	printf("Content of 2nd node : [%s]\n", (char *)head->next->content);
// Add a third node in front of everything
	t_list *third_node;
	third_node = ft_lstnew(test_string1);
	ft_lstadd_front(&head, third_node);
	printf ("\n˙ॱᐧ.˳˳.⋅Another pass in lstadd_front to place a
		new node in front˙ॱᐧ.˳˳.⋅\n\n");
	printf("New address of 1st node (head) : [%p] - Address of next node:
		[%p]\n", head, head->next);
	printf("New content of 1st node : [%s]\n", (char *)head->content);
// Creating a loop that will walk the linked list node by node
	printf ("\n˙ॱᐧ.˳˳.⋅Clean list of all nodes in order˙ॱᐧ.˳˳.⋅\n\n");
	t_list *ptr = head;
	int i = 1;
	while (ptr != NULL)
	{
		printf("Node [%d] - Address [%p] - Content [%s] - Next [%p]\n", i, ptr,
			(char *)ptr->content, ptr->next);
		i++;
		ptr = ptr->next;
		// ptr++ doesn't work, because it's a pointer to a struct/node,
		// not a regular variable I can increment
	}
	printf ("\n");
	free(third_node);
	free(second_node);
	//free(head);
	// solution to free node without malloc'd content : free all nodes exept
	// the last one (because it's freed via the 'next' address of the previous one)
	return (0);
} */
