/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael <wael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 18:33:51 by wael              #+#    #+#             */
/*   Updated: 2025/11/23 15:46:20 by wael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>

int	ft_printf(const char *input, ...);
int	print_char(char c);
int	print_str(char *str);
int	print_nbr_base(long long nbr, char *base);
int	print_unsigned_base(unsigned long long nbr, char *base);
int	print_ptr(void *ptr);
int	select_format(va_list *input, char t);

#endif
