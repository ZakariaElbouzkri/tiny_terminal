/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 04:12:12 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/07/15 04:42:26 by zel-bouz         ###   ########.fr       */
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

void	exec_cmd(t_cmd	*cmd, t_exec *exec)
{
	if (cmd->triger == -1)
		exit(127);
	if (*(char *)cmd->args->content == 0)
		exit(0);
	if (!command_exist(&cmd->cmd[0], exec->path))
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
	execve(cmd->cmd[0], cmd->cmd, exec->envp);
	perror("minishell: ");
}

void	exec_pipes(t_exec *exec)
{
	int		fd[2];
	pid_t	pid;
	t_cmd	*cmd;
	int		status;

	cmd = *exec->cmd;
	while (cmd)
	{
		if (cmd->next && pipe(fd) == -1)
			ft_perror("minishell: ");
		pid = fork();
		if (pid == -1)
			ft_perror("minishell: ");
		if (pid == 0)
		{
			if (cmd->next)
			{
				dup2(fd[1], 1);
				close(fd[0]);
				close(fd[1]);
			}
			exec_cmd(cmd, exec);
		}
		
		if (cmd->out != NO_OUT)
			close(cmd->out);
		if (cmd->inp != NO_INP)
			close(cmd->inp);
		if (cmd->next)
		{
			dup2(fd[0], 0);
			close(fd[0]);
			close(fd[1]);
		}
		cmd = cmd->next;
	}
	while ((pid = waitpid(-1, &status, 0)) > 0) {
		
    }
}
