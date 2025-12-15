/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 21:21:57 by wael              #+#    #+#             */
/*   Updated: 2025/11/11 15:37:11 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_len;
	size_t	src_len;

	dest_len = 0;
	while (dest[dest_len] && dest_len < size)
		dest_len++;
	src_len = 0;
	while (src[src_len])
		src_len++;
	if (dest_len == size)
		return (size + src_len);
	i = 0;
	while (src[i] && dest_len + i < size - 1)
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	if (dest_len < size)
		dest[dest_len + i] = '\0';
	return (dest_len + src_len);
}
// int	main(void)
// {
// 	char dest[] = "ipsum ";
// 	printf("%ld", ft_strlcat(dest, "lorem", 15));
// 	printf("\n%s\n", dest);
// 	return (0);
// }
