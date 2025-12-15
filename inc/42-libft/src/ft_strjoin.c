/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 14:32:46 by wael              #+#    #+#             */
/*   Updated: 2025/11/17 01:47:25 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		i;
	int		len1;
	int		len2;

	if (!(s1 && s2))
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	res = ft_calloc((len1 + len2 + 1), sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		res[i] = s1[i];
		i++;
	}
	while (i < len1 + len2)
	{
		res[i] = s2[i - len1];
		i++;
	}
	return (res);
}
