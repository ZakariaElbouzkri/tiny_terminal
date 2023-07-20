/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asettar <asettar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 23:33:34 by asettar           #+#    #+#             */
/*   Updated: 2023/07/19 23:33:35 by asettar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_digits_string(char *s)
{
	if (*s == '-' || *s == '+')
		s++;
	if (!*s)
		return (0);
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}

bool	greater_than_long(char *s)
{
	int	start;
	int	len;

	start = 0;
	len = ft_strlen(s);
	if (s[start] == '-' || s[start] == '+')
		start++;
	while (s[start] == '0')
		start++;
	if (len - start < 19)
		return (0);
	if (len - start > 19)
		return (1);
	if ((*s == '+' || ft_isdigit(s[0]))
		&& ft_strcmp("9223372036854775807", s + start) < 0)
		return (1);
	if (*s == '-' && ft_strcmp("9223372036854775808", s + start) < 0)
		return (1);
	return (0);
}

int	ft_exit(t_exec *exec, t_cmd *cmd)
{
	t_list	*args;

	args = cmd->args;
	(void)exec;
	if (!args->next)
		exit(0);
	if (args && args->next && (!is_digits_string(args->next->content)
			|| greater_than_long(args->next->content)))
	{
		ft_put_error(3, "exit", args->next->content,
			"numeric argument required");
		exit(255);
	}
	if (ft_lstsize(args) >= 3)
	{
		ft_put_error(2, "exit", "too many arguments");
		exit(1);
	}
	exit(ft_atoi(args->next->content));
}
