/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 23:05:08 by wael              #+#    #+#             */
/*   Updated: 2025/11/17 02:07:06 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t elCount, size_t elSize)
{
	unsigned char	*res;
	size_t			i;

	res = malloc(elCount * elSize);
	if (!res)
		return (NULL);
	i = 0;
	while (i < elCount * elSize)
	{
		res[i] = 0;
		i++;
	}
	return ((void *)res);
}
