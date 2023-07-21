/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 04:12:12 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/07/21 02:58:19 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clear_and_exit(t_cmd **cmd, t_env **env)
{
	free_cmd(cmd);
	free_env(env);
	ft_putstr_fd("minishell: maximum here-document count exceeded\n", 2);
	exit(EXIT_FAILURE);
}

bool	check_in_dir(char *cmd)
{
	if (!access(cmd, F_OK))
	{
		if (!access(cmd, X_OK))
			return (true);
		return (ft_put_error(2, cmd, "Permission denied"),
			g_glob.status = 126, false);
	}
	return (ft_put_error(2, cmd, "No such file or directory"),
		g_glob.status = 127, false);
}

bool	command_exist(char **cmd, char **path)
{
	char	*p;
	int		idx;

	if (ft_strchr(*cmd, '/'))
		return (check_in_dir(*cmd));
	if (!path)
		return (ft_put_error(2, *cmd, "command not found"),
			g_glob.status = 127, false);
	idx = -1;
	while (path[++idx])
	{
		p = ft_strjoin(ft_strdup(path[idx]), *cmd);
		if (!access(p, X_OK))
		{
			free(*cmd);
			*cmd = p;
			return (true);
		}
		free(p);
		p = NULL;
	}
	return (ft_put_error(2, *cmd, "command not found"),
		g_glob.status = 127, false);
}

bool	is_builtin(char *s)
{
	if (!ft_strcmp("pwd", s) || !ft_strcmp("export", s)
		|| !ft_strcmp("unset", s) || !ft_strcmp("echo", s)
		|| !ft_strcmp("env", s) || !ft_strcmp("cd", s) || !ft_strcmp("exit", s))
		return (1);
	return (0);
}
