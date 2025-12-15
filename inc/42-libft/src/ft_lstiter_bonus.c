/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 16:58:17 by wael              #+#    #+#             */
/*   Updated: 2025/11/14 17:25:46 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*tmp;
	t_list	*next;

	if (!lst || !f)
		return ;
	tmp = lst;
	while (tmp)
	{
		next = tmp->next;
		f(tmp->content);
		tmp = next;
	}
}
