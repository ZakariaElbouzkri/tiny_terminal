/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 21:32:42 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/07/20 05:07:22 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	open_and_close(char *file, t_tok t)
{
	int	fd;

	fd = open(file, O_RDWR | (t == APP || t == OUT) * O_CREAT
			| (t == OUT) * O_TRUNC | (t == APP) * O_APPEND, 0777);
	if (fd == -1)
	{
		perror("minishell: ");
		return (false);
	}
	close(fd);
	return (true);
}

void	get_inp_out_hlpr(t_cmd *cmd, t_redir *itr, int *last_out, int *last_in)
{
	if (cmd->triger == -1)
	{
		if (itr->fd > 0)
			close(itr->fd);
	}
	else if (itr->type == OUT || itr->type == APP)
	{
		if (*last_out > 0)
			close(*last_out);
		*last_out = itr->fd;
	}
	else if (itr->type == INP || itr->type == HER)
	{
		if (*last_in > 0)
			close(*last_in);
		*last_in = itr->fd;
	}
}

void	get_input_output(t_cmd *cmd)
{
	int		last_input;
	int		last_output;
	t_redir	*itr;

	if (!cmd)
		return ;
	last_input = NO_INP;
	last_output = NO_OUT;
	itr = cmd->redir;
	while (itr)
	{
		get_inp_out_hlpr(cmd, itr, &last_output, &last_input);
		itr = itr->next;
	}
	cmd->inp = last_input;
	cmd->out = last_output;
	get_input_output(cmd->next);
}

void	close_opened_her(t_cmd *cmd, t_redir *redir)
{
	if (!cmd)
		return ;
	if (!redir)
	{
		if (cmd->next)
			close_opened_her(cmd->next, cmd->next->redir);
	}
	else
	{
		if (redir->type == HER && redir->fd != NO_INP)
			close(redir->fd);
		close_opened_her(cmd, redir->next);
	}
}

void	execute(t_cmd	**cmd, t_env **env)
{
	int		in_cp;
	int		out_cp;

	in_cp = dup(0);
	out_cp = dup(1);
	open_herdocs(*cmd, *env);
	if (g_glob.her == 1)
	{
		close_opened_her(*cmd, (*cmd)->redir);
		(close(in_cp), close(out_cp));
		return ;
	}
	open_redirs(*cmd);
	get_input_output(*cmd);
	g_glob.under_exec = 1;
	exec_commands(cmd, env);
	(dup2(in_cp, 0), dup2(out_cp, 1));
	(close(in_cp), close(out_cp));
}
