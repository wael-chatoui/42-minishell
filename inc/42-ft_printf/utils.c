/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 18:30:11 by wael              #+#    #+#             */
/*   Updated: 2026/01/20 17:50:15 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_char(char c)
{
	return (write(1, &c, 1));
}

int	print_str(char *str)
{
	if (!str)
		return (write(1, "(null)", 6));
	return (write(STDOUT_FILENO, str, ft_strlen(str)));
}

int	print_unsigned_base(unsigned long long nbr, char *base)
{
	int					count;
	int					lbase;

	lbase = 0;
	while (base[lbase])
		lbase++;
	count = 0;
	if (nbr >= (unsigned long long)lbase)
		count += print_unsigned_base(nbr / lbase, base);
	print_char(base[nbr % lbase]);
	count++;
	return (count);
}

int	print_nbr_base(long long n, char *base)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		write(1, "-", 1);
		count++;
		n = -n;
	}
	count += print_unsigned_base((unsigned long long)n, base);
	return (count);
}

int	print_ptr(void *ptr)
{
	int	count;

	if (!ptr)
		return (print_str("(nil)"));
	count = 0;
	count += print_str("0x");
	count += print_unsigned_base((uintptr_t)ptr, "0123456789abcdef");
	return (count);
}
