/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 01:47:51 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/07/21 01:34:14 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_builtins(t_exec *exec, t_cmd *node)
{
	char	*s;

	s = node->cmd[0];
	if (!ft_strcmp(s, "cd"))
		g_glob.status = ft_cd(exec, node);
	else if (!ft_strcmp(s, "pwd"))
		g_glob.status = ft_pwd(exec, node);
	else if (!ft_strcmp(s, "export"))
		g_glob.status = ft_export(exec, node);
	else if (!ft_strcmp(s, "exit"))
		g_glob.status = ft_exit(exec, node);
	else if (!ft_strcmp(s, "env"))
		g_glob.status = ft_env(exec, node);
	else if (!ft_strcmp(s, "echo"))
		g_glob.status = ft_echo(exec, node);
	else if (!ft_strcmp(s, "unset"))
		g_glob.status = ft_unset(exec, node);
}

void	catch_error(char *s)
{
	ft_put_error(2, s, strerror(errno));
	if (errno == 2 || errno == 13)
		exit(127 - (errno == 13));
	exit(1);
}

void	send_to_exec(t_exec *exec, t_cmd	*node)
{
	if (node->triger == -1)
		clear_and_exit_with_status(exec, 1);
	if (!node->cmd || !*node->cmd[0])
		clear_and_exit_with_status(exec, 0);
	if (node->inp != NO_INP)
		dup2(node->inp, 0);
	if (node->out != NO_OUT)
		dup2(node->out, 1);
	(close(node->inp), close(node->out));
	if (is_builtin(node->cmd[0]))
	{
		exec_builtins(exec, node);
		clear_and_exit_with_status(exec, g_glob.status);
	}
	if (!command_exist(&node->cmd[0], exec->path))
	{
		if (errno == 2)
			ft_put_error(2, node->cmd[0], "command not found");
		else
			ft_put_error(2, node->cmd[0], strerror(errno));
		clear_and_exit_with_status(exec, 127 - (errno == 13));
	}
	execve(node->cmd[0], node->cmd, exec->envp);
	catch_error(node->cmd[0]);
}

void	exec_pipes(t_exec *exec, int *pid, t_cmd *itr)
{
	if (itr->cmd && !itr->next && is_builtin(itr->cmd[0]))
	{
		if (itr->triger == -1)
		{
			g_glob.status = 1;
			return ;
		}
		return (ft_dup2(itr->inp, itr->out), exec_builtins(exec, itr));
	}	
	while (itr)
	{
		if (itr->next && pipe(exec->fd) == -1)
			return (g_glob.status = 1,
				ft_put_error(2, "pipe", strerror(errno)));
		*pid = fork();
		if (*pid == -1)
			return (g_glob.status = 1,
				ft_put_error(2, "fork", strerror(errno)));
		if (*pid == 0)
			execute_child(exec, itr);
		(close(itr->inp), close(itr->out));
		if (itr->next)
		{
			dup2(exec->fd[0], 0);
			(close(exec->fd[0]), close(exec->fd[1]));
		}
		else
			close(0);
		itr = itr->next;
	}
}
