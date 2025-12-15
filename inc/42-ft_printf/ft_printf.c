/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 18:30:11 by wael              #+#    #+#             */
/*   Updated: 2025/11/23 15:52:06 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	select_format(va_list *input, char t)
{
	if (t == 'c')
		return (print_char(va_arg(*input, int)));
	else if (t == 's')
		return (print_str(va_arg(*input, char *)));
	else if (t == 'p')
		return (print_ptr(va_arg(*input, void *)));
	else if (t == 'd' || t == 'i')
		return (print_nbr_base(va_arg(*input, int), "0123456789"));
	else if (t == 'u')
		return (print_unsigned_base(va_arg(*input, unsigned int), \
"0123456789"));
	else if (t == 'x')
		return (print_unsigned_base(va_arg(*input, unsigned int), \
"0123456789abcdef"));
	else if (t == 'X')
		return (print_unsigned_base(va_arg(*input, unsigned int), \
"0123456789ABCDEF"));
	else if (t == '%')
		return (print_char('%'));
	return (0);
}

int	ft_printf(const char *input, ...)
{
	va_list	args;
	int		count;
	int		i;

	if (!input)
		return (-1);
	va_start(args, input);
	count = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '%' && input[i + 1])
		{
			count += select_format(&args, input[i + 1]);
			i++;
		}
		else
			count += print_char(input[i]);
		i++;
	}
	va_end(args);
	return (count);
}
