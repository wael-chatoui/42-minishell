/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 17:26:47 by wael              #+#    #+#             */
/*   Updated: 2025/11/17 01:43:13 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*tail;
	t_list	*node;

	head = NULL;
	node = NULL;
	while (lst)
	{
		tail = node;
		node = ft_calloc(1, sizeof(t_list));
		if (!node)
		{
			ft_lstclear(&head, del);
			return (NULL);
		}
		node->content = f(lst->content);
		node->next = NULL;
		if (!head)
			head = node;
		else
			tail->next = node;
		lst = lst->next;
	}
	return (head);
}
