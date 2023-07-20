/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 05:12:18 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/07/20 05:15:03 by zel-bouz         ###   ########.fr       */
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

void	ft_dup2(int fdin, int fdout)
{
	if (fdout != NO_OUT)
	{
		dup2(fdout, 1);
		close(fdout);
	}
	if (fdin != NO_INP)
	{
		dup2(fdin, 0);
		close(fdin);
	}
}

void	init_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	execute_child(t_exec *exec, t_cmd *itr)
{
	init_child_signals();
	close_all_next_fds(itr);
	if (itr->next)
	{
		dup2(exec->fd[1], 1);
		(close(exec->fd[1]), close(exec->fd[0]));
	}
	send_to_exec(exec, itr);
}
