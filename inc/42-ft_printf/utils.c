/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 18:30:11 by wael              #+#    #+#             */
/*   Updated: 2025/11/23 15:48:13 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_char(char c)
{
	return (write(1, &c, 1));
}

int	print_str(char *str)
{
	int	len;

	if (!str)
		return (write(1, "(null)", 6));
	while (str[len])
		write(STDOUT_FILENO, &str[len++], 1);
	return (len);
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
