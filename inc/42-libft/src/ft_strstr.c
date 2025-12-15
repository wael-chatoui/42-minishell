/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 23:44:26 by wael              #+#    #+#             */
/*   Updated: 2025/11/08 15:17:20 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	size_t	i;
	size_t	j;
	size_t	len;
	size_t	blen;

	if (!big || !little)
		return (NULL);
	i = 0;
	len = ft_strlen(little);
	blen = ft_strlen(big);
	if (!len)
		return ((char *)big);
	while (i + len <= blen)
	{
		j = 0;
		while (j < len && big[i + j] == little[j])
			j++;
		if (j == len)
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
// int	main(int ac, char **av)
// {
// 	if (ac == 3)
// 	{
// 		printf("%s\n", ft_strstr(av[1], av[2]));
// 	}
// 	return (0);
// }
