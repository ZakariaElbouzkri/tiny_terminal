/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 22:15:47 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/07/15 20:58:27 by zel-bouz         ###   ########.fr       */
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

void	extract_args(t_cmd *cmd)
{
	t_list	*itr;
	int		i;

	while (cmd)
	{
		if (cmd->args)
		{
			itr = cmd->args;
			cmd->cmd = (char **)malloc(sizeof(char *) * (ft_lstsize(itr) + 1));
			i = 0;
			while (itr)
			{
				cmd->cmd[i++] = itr->content;
				itr = itr->next;
			}
			cmd->cmd[i] = NULL;
		}
		cmd = cmd->next;
	}
}

void	clean_all(char **path, char **envp)
{
	free_dubptr(path);
	free_dubptr(envp);
}

void	fget(int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		printf("%s", line);
	}
}

void	exec_commands(t_cmd **cmd, t_env **env)
{
	t_exec	exec;

	ft_memset(&exec, 0, sizeof(t_exec));
	exec.path = get_path(*env);
	exec.envp = extract_envp(*env);
	exec.env = env;
	exec.cmd = cmd;
	extract_args(*cmd);
	exec_pipes(&exec);
	clean_all(exec.path, exec.envp);
}