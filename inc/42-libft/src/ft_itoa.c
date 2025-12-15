/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 19:10:55 by wael              #+#    #+#             */
/*   Updated: 2025/11/17 01:50:25 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	ft_nblen(long n)
{
	long	len;

	len = 0;
	if (n <= 0)
		len = 1;
	if (n < 0)
		n = -n;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	nb;
	long	len;

	nb = (long)n;
	len = ft_nblen(nb);
	str = ft_calloc((len + 1), sizeof(char));
	if (!str)
		return (NULL);
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	if (nb == 0)
		str[0] = '0';
	while (nb)
	{
		str[--len] = (nb % 10) + '0';
		nb /= 10;
	}
	return (str);
}
