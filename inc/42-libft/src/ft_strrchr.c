/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 22:12:41 by wael              #+#    #+#             */
/*   Updated: 2025/11/04 22:27:52 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	if (!(char)c)
		return ((char *)&str[len]);
	while (len > 0)
	{
		len--;
		if (str[len] == (char)c)
			return ((char *)&str[len]);
	}
	return (NULL);
}
