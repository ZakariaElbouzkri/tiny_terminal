/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asettar <asettar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 04:12:12 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/07/16 07:11:10 by asettar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_cmd(char *cmd, char **path)
{
	int		idx;
	char 	*p;

	idx = -1;
	if (!access(cmd, X_OK))
		return (cmd);
	while (path[++idx])
	{
		p = ft_strjoin(ft_strdup(path[idx]), cmd);
		if (!access(p, X_OK))
			return (free(cmd), p);
		// free(p);
		p = NULL;
	}
	return (NULL);
}

void	err_cmd_404(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found", 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

bool	command_exist(char **cmd, char **path)
{
	char	*p;
	int		idx;

	p  = NULL;
	idx = -1;
	if (!access(*cmd, X_OK))
		return (true);
	if (!path)
		return (false);
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
	return (false);
}

bool	is_builtin(char *s)
{
	if (!ft_strcmp("pwd", s) || !ft_strcmp("export", s) || !ft_strcmp("unset", s)
		|| !ft_strcmp("echo", s) || !ft_strcmp("env", s) || !ft_strcmp("cd", s) || !ft_strcmp("exit", s))
			return (1);
	return (0);
}

void	exec_builtins(t_exec *exec, int p)
{
	if (!ft_strcmp("cd", (*exec->cmd)->cmd[0]))
		ft_cd(exec, p);
	if (!ft_strcmp("pwd", (*exec->cmd)->cmd[0]))
		ft_pwd(exec, p);
	if (!ft_strcmp("export", (*exec->cmd)->cmd[0]))
		ft_export(exec, p);
	else if (!ft_strcmp("unset", (*exec->cmd)->cmd[0]))
		ft_unset(exec, p);
	else if (!ft_strcmp("env", (*exec->cmd)->cmd[0]))
		ft_env(exec, p);
	else if (!ft_strcmp("exit", (*exec->cmd)->cmd[0]))
		ft_exit(exec);
}

void	exec_cmd(t_cmd	*cmd, t_exec *exec)
{
	if (cmd->triger == -1)
		exit(127);
	if (*(char *)cmd->args->content == 0)
		exit(0);
	if (!is_builtin(cmd->cmd[0]) && !command_exist(&cmd->cmd[0], exec->path))
		err_cmd_404(cmd->cmd[0]);
	if (cmd->inp != NO_INP)
	{
		dup2(cmd->inp, 0);
		close(cmd->inp);
	}
	if (cmd->out != NO_OUT)
	{
		dup2(cmd->out, 1);
		close(cmd->out);
	}
	if (is_builtin(cmd->cmd[0]))
		exec_builtins(exec, 0);
	else
	{
		execve(cmd->cmd[0], cmd->cmd, exec->envp);
		perror("minishell: ");
	}
}

void	exec_pipes(t_exec *exec)
{
	t_cmd	*cmd;
	int		status;
	pid_t	pid;

	cmd = *exec->cmd;
	if (!cmd->next && is_builtin(cmd->cmd[0]))
	{
		exec_builtins(exec, 1); // in main
		cmd = cmd->next;
	}
	while (cmd)
	{
		if (cmd->next && pipe(cmd->fd) == -1)
			ft_put_error(1, strerror(errno));
		pid = fork();
		if (pid == -1)
			ft_put_error(1, strerror(errno));
		if (pid == 0)
		{
			if (cmd->next)
			{
				dup2(cmd->fd[1], 1);
				close(cmd->fd[0]);
				close(cmd->fd[1]);
			}
			exec_cmd(cmd, exec);
		}
		if (cmd->out != NO_OUT)
			close(cmd->out);
		if (cmd->inp != NO_INP)
			close(cmd->inp);
		if (cmd->next)
		{
			dup2(cmd->fd[0], 0);
			close(cmd->fd[0]);
			close(cmd->fd[1]);
		}
		if(cmd->next == NULL)
			close(0);
		cmd = cmd->next;
	}
	while ((pid = waitpid(-1, &status, 0)) > 0) {
		
    }
}
