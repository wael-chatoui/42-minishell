/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 23:50:01 by wael              #+#    #+#             */
/*   Updated: 2025/11/17 02:12:50 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strdivide(char const *str, char **res, const char c)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		start = i;
		while (str[i] && str[i] != c)
			i++;
		if (i > start)
		{
			res[j] = ft_substr(str, start, i - start);
			if (!res[j])
				return (ft_free_split(res, j), 0);
			j++;
		}
	}
	res[j] = NULL;
	return (1);
}

char	**ft_split(const char *str, char charset)
{
	char	**res;
	int		words;

	if (!str)
		return (NULL);
	words = ft_count_words(str, charset);
	res = ft_calloc(words + 1, sizeof(char *));
	if (!res)
		return (NULL);
	if (!ft_strdivide(str, res, charset))
		return (NULL);
	return (res);
}
