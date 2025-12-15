/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 17:44:23 by wchatoui          #+#    #+#             */
/*   Updated: 2025/11/11 15:38:52 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t siz)
{
	size_t	i;

	i = 0;
	if (siz != 0)
	{
		while (src[i] && i < siz - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	while (src[i])
		i++;
	return (i);
}
// int	main(void)
// {
// 	char dest[15];
// 	printf("%d", ft_strlcpy(dest, "lorem", 15));
// 	printf("\n%s\n", dest);
// 	return (0);
// }
