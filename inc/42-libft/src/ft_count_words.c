/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchatoui <wchatoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 22:07:52 by wael              #+#    #+#             */
/*   Updated: 2025/11/28 16:09:01 by wchatoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_words(const char *str, const char c)
{
	size_t	i;
	size_t	trigger;
	size_t	j;

	if (!str)
		return (0);
	i = 0;
	trigger = 0;
	j = 0;
	while (str[j])
	{
		if (!(str[j] == c) && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (str[j] == c)
			trigger = 0;
		j++;
	}
	return (i);
}
