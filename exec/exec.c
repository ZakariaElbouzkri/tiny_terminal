/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 01:47:51 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/07/18 06:34:06 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_all_next_fds(t_cmd *itr)
{
	while (itr->next)
	{
		if (itr->next->inp != NO_INP)
			close(itr->next->inp);
		if (itr->next->out != NO_INP)
			close(itr->next->out);
		itr = itr->next;
	}
}

void	clear_and_exit_with_status(t_exec *exec, int status)
{
	free_cmd(exec->cmd);
	free_env(exec->env);
	free_dubptr(exec->envp);
	free_dubptr(exec->path);
	exit(status);
}

int	exec_builtins(t_exec *exec, t_cmd *node)
{
	char	*s;

	s = node->cmd[0];
	if (!ft_strcmp(s, "cd"))
		return (ft_cd(exec, node));
	else if (!ft_strcmp(s, "pwd"))
		return (ft_pwd(exec, node));
	else if (!ft_strcmp(s, "export"))
		return (ft_export(exec, node));
	else if (!ft_strcmp(s, "exit"))
		return (ft_exit(exec, node));
	else if (!ft_strcmp(s, "env"))
		return (ft_env(exec, node));
	else if (!ft_strcmp(s, "echo"))
		return (ft_echo(exec, node));
	else if (!ft_strcmp(s, "unset"))
		return (ft_unset(exec, node));
	return (0);
}

void	exec_child(t_exec *exec, t_cmd	*node)
{
	if (node->triger == -1)
		clear_and_exit_with_status(exec, 127);
	if (!node->cmd || !*node->cmd[0])
		clear_and_exit_with_status(exec, 0);
	if (node->inp != NO_INP)
	{
		dup2(node->inp, 0);
		close(node->inp);
	}
	if (node->out != NO_OUT)
	{
		dup2(node->out, 1);
		close(node->out);
	}
	if (is_builtin(node->cmd[0]))
		clear_and_exit_with_status(exec, exec_builtins(exec, node));
	if (!command_exist(&node->cmd[0], exec->path))
	{
		ft_put_error(2, node->cmd[0], "command not found");
		clear_and_exit_with_status(exec, 127);
	}
	execve(node->cmd[0], node->cmd, exec->envp);
	ft_put_error(2, node->cmd[0], strerror(errno));
	exit(errno);
}

int	exec_pipes(t_exec *exec)
{
	pid_t	pid;
	int		fd[2];
	t_cmd	*itr;
	int		status;

	itr = *exec->cmd;
	if (itr->cmd && !itr->next && is_builtin(itr->cmd[0]))
	{
		if (itr->inp != NO_INP)
		{
			dup2(itr->inp, 0);
			close(itr->inp);
		}
		if (itr->out != NO_OUT)
		{
			dup2(itr->out, 1);
			close(itr->out);
		}
		return (exec_builtins(exec, itr));
	}
	while (itr)
	{
		if (itr->next && pipe(fd) == -1)
			return (ft_put_error(2, "pipe", strerror(errno)), 1);
		pid = fork();
		if (pid == -1)
		{
			ft_put_error(2, "fork", strerror(errno));
			break;
		}
		if (pid == 0)
		{
			close_all_next_fds(itr);
			if (itr->next)
			{
				dup2(fd[1], 1);
				close(fd[1]);
				close(fd[0]);
			}
			exec_child(exec, itr);
		}
		if (itr->inp != NO_INP)
			close(itr->inp);
		if (itr->out != NO_INP)
			close(itr->inp);
		if (itr->next)
		{
			dup2(fd[0], 0);
			close(fd[0]);
			close(fd[1]);
		}
		if (itr->next == NULL)
			close(0);
		itr = itr->next;
	}
	while ((pid = waitpid(-1, &status, 0)) > 0)
		g_status =  WEXITSTATUS(status);
	return (g_status);
}
