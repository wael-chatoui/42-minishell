/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchatoui <wchatoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:02:23 by wchatoui          #+#    #+#             */
/*   Updated: 2025/11/04 17:36:33 by wchatoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_index_base(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (c == base[i])
			return (i);
		i++;
	}
	return (-1);
}

int	ft_atoi_base(char *nbr, char *base)
{
	int				sign;
	int				lbase;
	unsigned int	nb;

	sign = 1;
	lbase = ft_strlen(base);
	while (ft_isspace(*nbr))
		nbr++;
	while (*nbr == '-' || *nbr == '+')
	{
		if (*nbr == '-')
			sign = -sign;
		nbr++;
	}
	nb = 0;
	while (*nbr && ft_index_base(*nbr, base) != -1)
	{
		nb = nb * lbase + ft_index_base(*nbr, base);
		nbr++;
	}
	return (nb * sign);
}
