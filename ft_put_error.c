/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asettar <asettar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 06:12:15 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/07/20 01:14:45 by asettar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_put_error(int n, ...)
{
	va_list	args;

	va_start(args, n);
	ft_putstr_fd("minishell", 2);
	while (n)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(va_arg(args, char *), 2);
		n--;
	}
	ft_putstr_fd("\n", 2);
	va_end(args);
}
