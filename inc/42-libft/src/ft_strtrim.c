/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 17:06:37 by wael              #+#    #+#             */
/*   Updated: 2025/11/11 16:11:32 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*res;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_is_in(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_is_in(s1[end - 1], set))
		end--;
	res = ft_substr(s1, start, end - start);
	return (res);
}
