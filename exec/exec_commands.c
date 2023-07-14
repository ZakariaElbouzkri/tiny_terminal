/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 22:15:47 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/07/13 23:14:47 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_puterr(char *err, char *s)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(":", 2);
	ft_putstr_fd(err, 2);
	exit(EXIT_FAILURE);
}

void	convert_cmd_list(t_cmd *cmd)
{
	int i;

	while (cmd)
	{
		cmd->cmd = NULL;
		if (cmd->args)
		{
			i = 0;
			cmd->cmd = ft_calloc(sizeof(char *), ft_lstsize(cmd->args) + 1);
			while (cmd->args)
			{
				cmd->cmd[i++] = cmd->args->content;
				cmd->args = cmd->args;
			}
		}
		cmd = cmd->next;
	}
}

char	**get_path(t_env *env)
{
	char	**path;
	char	*p;
	int		idx;

	p = get_env("PATH", env);
	if (!p)
		return (NULL);
	path = ft_split(p, ':');
	idx = -1;
	while (path && path[++idx])
	{
		if (path[idx][ft_strlen(path[idx]) - 1] != '/')
			path[idx] = ft_strjoin(path[idx], "/");
	}
	return (path);
}

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
		free(p);
		p = NULL;		
	}
	return (free(cmd), NULL);
}

int	t_env_size(t_env *env)
{
	if (env)
		return (0);
	return (env->flag != 2) + t_env_size(env->next);
}

char	**convert_env_list(t_env *env)
{
	int		idx;
	int		len;
	char	**envp;
	char	*var;


	len = t_env_size(env);
	envp = ft_calloc(sizeof(char *), len + 1);
	idx = -1;
	while (env)
	{
		if (env->flag != 2)
		{
			var = ft_strjoin(ft_strdup(env->value), "=");
			envp[++idx] =  ft_strjoin(var, env->value);
		}
		env = env->next;
	}
	return (envp);
}

void	exec_commands(t_cmd **cmd, t_env **env)
{
	int		fd[2];
	int		pid;
	char	**path;
	char	**envp;

	convert_cmd_list(*cmd);
	envp = convert_env_list(*env);
	path = get_path(*env);
	while (*cmd)
	{
		if ((*cmd)->next)
		{
			if (pipe(fd) == -1)
				ft_perror("minishell:");
			pid = fork();
			if (pid == -1)
				ft_perror("minishell:");
			if (!pid)
			{
				if ((*cmd)->next)
				{
					dup2(fd[1], 1);
					close(fd[0]);
					close(fd[1]);
				}
				(*cmd)->cmd[0] = find_cmd((*cmd)->cmd[0], path);
				if (!((*cmd)->cmd[0]))
					ft_puterr("command not found\n", (*cmd)->cmd[0]);
				execve((*cmd)->cmd[0], (*cmd)->cmd, envp);
				ft_perror("minishell: ");
			}
			if ((*cmd)->next)
			{
				close(fd[1]);
				dup2(fd[0], 0);
				close(fd[0]);
			}
		}
	}
	int status;

	waitpid(-1, &status, 0);
}