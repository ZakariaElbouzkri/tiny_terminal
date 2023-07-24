/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_construct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asettar <asettar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 02:43:05 by asettar           #+#    #+#             */
/*   Updated: 2023/07/24 07:23:39 by asettar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_last_args(t_lex *lex, t_cmd *last)
{
	int		i;
	int		start;
	char	*arg;

	if (lex->expanded && lex->tok == WRD)
	{
		i = 0;
		while (lex->data[i])
		{
			start = i;
			while (lex->data[i] && !ft_isspace(lex->data[i]))
				i++;
			arg = ft_substr(lex->data, start, i - start);
			if (arg && *arg)
				ft_lstadd_back(&last->args, ft_lstnew(arg));
			while (lex->data[i] && ft_isspace(lex->data[i]))
				i++;
		}
	}
	else
		ft_lstadd_back(&last->args, ft_lstnew(ft_strdup(lex->data)));
}

void	change_last_redir(t_lex **lst, t_cmd *last)
{
	t_lex	*lex;
	t_redir	*red;

	lex = *lst;
	while (lex && is_redir(lex))
	{
		red = (t_redir *)malloc(sizeof(t_redir));
		if (!red)
			exit_with_failure();
		red->type = lex->tok;
		red->file = ft_strdup(lex->next->data);
		red->flag = (lex->next->tok == WRD);
		red->fd = NO_INP;
		red->next = NULL;
		ft_redir_add_back(&last->redir, red);
		*lst = lex->next;
		lex = lex->next->next;
	}
}

void	change_env_last_cmd(t_env *env, t_cmd *cmd)
{
	t_env	*last_env;
	t_list	*last_arg;

	last_env = env_find("_", env);
	free(last_env->value);
	last_env->value = NULL;
	if (!cmd || !cmd->args || cmd->next)
		return ;
	last_arg = ft_lstlast(cmd->args);
	last_env->value = ft_strdup(last_arg->content);
}

void	check_first_arg(t_cmd *cmd)
{
	t_list	*node;

	while (cmd)
	{
		if (cmd->args && !ft_strcmp(cmd->args->content, "env")
			&& cmd->args->next)
		{
			node = cmd->args->next;
			free(cmd->args->content);
			free(cmd->args);
			cmd->args = node;
		}
		cmd = cmd->next;
	}
}

void	construct_cmds(t_cmd **cmd, t_lex **lst, t_env *env)
{
	t_lex	*lex;
	bool	new_cmd;
	t_cmd	*last;

	lex = *lst;
	new_cmd = true;
	while (lex)
	{
		if (new_cmd)
			create_new_cmd(cmd, &last, &new_cmd);
		if (is_word(lex))
			change_last_args(lex, last);
		else if (is_redir(lex))
			change_last_redir(&lex, last);
		if (lex && lex->tok == PIP)
			new_cmd = true;
		lex = lex->next;
	}
	change_env_last_cmd(env, *cmd);
	check_first_arg(*cmd);
}
