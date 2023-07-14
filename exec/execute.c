/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 21:32:42 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/07/14 03:26:00 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void	free_dubptr(char **ptr)
{
	int idx;

	if (!ptr)
		return ;
	idx = -1;
	while (ptr[++idx])
	{
		free(ptr[idx]);
		ptr[idx] = NULL;
	}
	free(ptr);
	ptr = NULL;
}

int	count_her(t_cmd *cmd, t_redir *redir)
{
	if (!redir)
	{
		if (!cmd->next)
			return (0);	
		return (count_her(cmd->next, cmd->next->redir));
	}
	return (redir->type == HER) + count_her(cmd, redir->next);
}

void	clear_and_exit(t_cmd **cmd, t_env **env)
{
	free_cmd(cmd);
	free_env(env);
	ft_putstr_fd("minishell: maximum here-document count exceeded\n", 2);
	exit(EXIT_FAILURE);
}

void	execute(t_cmd	**cmd, t_env **env)
{
	char	**path;
	// char	*line;

	(void)path;
	if (count_her(*cmd, (*cmd)->redir) >= 17)
		clear_and_exit(cmd, env);
	exec_herdocs(*cmd, *env);
	exec_commands(cmd, env);
	// t_cmd *itr = *cmd;
	// while (itr)
	// {
	// 	if (itr->her_fd != -1)
	// 	{
	// 		while (1)
	// 		{
	// 			line = get_next_line(itr->her_fd);
	// 			if (!line)
	// 				break;
	// 			printf("%s", line);
	// 			free(line);
	// 		}
	// 		close(itr->her_fd);
	// 	}
	// 	itr = itr->next;
	// }
}
