/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 21:32:42 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/07/18 00:44:37 by zel-bouz         ###   ########.fr       */
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


bool	open_and_close(char *file, t_tok t)
{
	int	fd;

	fd = open(file, O_RDWR|(t == APP || t == OUT) * O_CREAT|
		(t == OUT) * O_TRUNC|(t == APP) * O_APPEND, 0777);
	if (fd == -1)
	{
		perror("minishell: ");
		return (false);
	}
	close(fd);
	return (true);
}

bool	open_and_save(char *file, t_tok t, int *fd)
{
	*fd = open(file, O_RDWR|(t == APP || t == OUT) * O_CREAT|
		(t == OUT) * O_TRUNC|(t == APP) * O_APPEND, 0777);
	if (*fd == -1)
	{
		perror("minishell: ");
		return (false);
	}
	return (true);
}

void	exec_redirs(t_cmd *cmd)
{
	t_redir	*red;

	while (cmd)
	{
		red = cmd->redir;
		while (red)
		{
			if (red->type == INP || red->type == OUT || red->type == APP)
				if (!open_and_save(red->file, red->type, &red->fd))
				{
					cmd->triger = -1;
					break;
				}
			red = red->next;
		}
		cmd = cmd->next;
	}
}



void	get_input_output(t_cmd *cmd)
{
	int	last_input;
	int	last_output;
	t_redir	*itr;
	
	if (!cmd)
		return ;
	last_input = NO_INP;
	last_output = NO_OUT;
	itr = cmd->redir;
	while (itr)
	{
		if (cmd->triger == -1)
		{
			if (itr->fd > 0)
				close(itr->fd);
		}
		else if (itr->type == OUT || itr->type == APP)
		{
			if (last_output > 0)
				close(last_output);
			last_output = itr->fd;
		}
		else if (itr->type == INP || itr->type == HER)
		{
			if (last_input > 0)
				close(last_input);
			last_input = itr->fd;
		}
		itr = itr->next;
	}
	cmd->inp = last_input;
	cmd->out = last_output;
	get_input_output(cmd->next);
}

// void	save_std_io(int *in_cp, int *out_cp)
// {
// 	in_cp = dup(0);
// 	in_cp = dup(1);
// }

void	execute(t_cmd	**cmd, t_env **env)
{
	int		in_cp;
	int		out_cp;

	in_cp = dup(0);
	out_cp = dup(1);
	if (count_her(*cmd, (*cmd)->redir) >= 17)
		clear_and_exit(cmd, env);
	exec_herdocs(*cmd, *env);
	exec_redirs(*cmd);
	get_input_output(*cmd);
	exec_commands(cmd, env);
	dup2(in_cp, 0);
	dup2(out_cp, 1);
	close(in_cp);
	close(out_cp);
}
