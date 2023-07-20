/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 22:15:47 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/07/20 05:11:00 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	update_exit_status(int pid)
{
	int	status;

	if (waitpid(pid, &status, 0) > 0)
	{
		if (WIFSTOPPED(status))
			g_glob.status = FSIGNAL + WSTOPSIG(status);
		else if (WIFSIGNALED(status))
		{
			g_glob.status = FSIGNAL + WTERMSIG(status);
			if (g_glob.status == 130)
				ft_putstr_fd("\n", 2);
			else if (g_glob.status == 131)
				ft_putstr_fd("Quit: 3\n", 2);
			else if (g_glob.status == 139)
			{
				ft_putstr_fd(ft_itoa(pid), 2);
				ft_putstr_fd(" segmentation fault\n", 2);
			}
		}
		else if (WIFEXITED(status))
			g_glob.status = WEXITSTATUS(status);
	}
	while (wait(NULL) != -1)
		;
}

void	exec_commands(t_cmd **cmd, t_env **env)
{
	t_exec	exec;
	int		pid;

	ft_memset(&exec, 0, sizeof(t_exec));
	exec.path = get_path(*env);
	exec.envp = extract_envp(*env);
	exec.env = env;
	exec.cmd = cmd;
	extract_args(*cmd);
	exec_pipes(&exec, &pid, *cmd);
	update_exit_status(pid);
	free_dubptr(exec.path);
	free_dubptr(exec.envp);
}