/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asettar <asettar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 06:12:15 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/07/24 07:23:47 by asettar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_with_failure(void)
{
	free_env(g_glob.env);
	free_lex(g_glob.lex);
	free_cmd(g_glob.cmd);
	free(g_glob.pwd);
	ft_putstr_fd("minishell: malloc: allocation error\n", 2);
	exit(EXIT_FAILURE);
}

void	create_new_cmd(t_cmd **cmd, t_cmd **last, bool *new_cmd)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		exit_with_failure();
	ft_memset(new, 0, sizeof(t_cmd));
	new->inp = NO_INP;
	new->out = NO_OUT;
	*new_cmd = false;
	ft_cmd_add_back(cmd, new);
	*last = new;
}

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

char	*ft_strrcat(char *s, char c)
{
	char	*ret;
	int		i;

	ret = malloc(ft_strlen(s) + 2);
	if (!ret)
		exit_with_failure();
	i = -1;
	while (s[++i])
		ret[i] = s[i];
	ret[i++] = c;
	ret[i] = 0;
	free(s);
	return (ret);
}
