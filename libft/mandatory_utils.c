/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandatory_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asettar <asettar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:19:57 by asettar           #+#    #+#             */
/*   Updated: 2022/11/20 07:01:18 by asettar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	check_type(va_list args, char c, int *len)
{
	if (c == 'c')
		ft_print_char(va_arg(args, int), len);
	else if (c == 's')
		ft_print_string(va_arg(args, char *), len);
	else if (c == 'd' || c == 'i')
		ft_print_num(va_arg(args, int), len);
	else if (c == 'u')
		ft_print_num(va_arg(args, unsigned int), len);
	else if (c == 'x')
		dec_to_hex(va_arg(args, unsigned int), "0123456789abcdef", len);
	else if (c == 'X')
		dec_to_hex(va_arg(args, unsigned int), "0123456789ABCDEF", len);
	else if (c == '%')
		ft_print_char('%', len);
	else if (c == 'p')
	{
		*len += write(1, "0x", 2);
		dec_to_hex(va_arg(args, unsigned long), "0123456789abcdef", len);
	}
}

void	ft_print_char(char c, int *len)
{
	write(1, &c, 1);
	*len += 1;
}

void	ft_print_string(char *str, int *len)
{
	if (!str)
		*len += write(1, "(null)", 6);
	else
	{
		while (*str)
			*len += write(1, str++, 1);
	}
}

void	ft_print_num(long n, int *len)
{
	if (n >= 0 && n <= 9)
		ft_print_char(n + '0', len);
	else if (n < 0)
	{
		ft_print_char('-', len);
		ft_print_num(-n, len);
	}
	else
	{
		ft_print_num(n / 10, len);
		ft_print_char(n % 10 + '0', len);
	}
}

void	dec_to_hex(unsigned long n, const char *str, int *len)
{
	if (n < 16)
		ft_print_char(str[n % 16], len);
	else
	{
		dec_to_hex(n / 16, str, len);
		ft_print_char(str[n % 16], len);
	}
}
