/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:23:45 by wchatoui          #+#    #+#             */
/*   Updated: 2025/11/10 18:38:30 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*ptr;
	unsigned char	*ptr2;
	unsigned int	i;

	i = 0;
	ptr = (unsigned char *)dst;
	ptr2 = (unsigned char *)src;
	if (ptr == NULL && ptr2 == NULL)
		return (NULL);
	while (i < n)
	{
		ptr[i] = ptr2[i];
		i++;
	}
	return (dst);
}
