/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_construct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asettar <asettar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 02:43:05 by asettar           #+#    #+#             */
/*   Updated: 2023/07/24 04:58:37 by asettar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_new_cmd(t_cmd **cmd, t_cmd **last, bool *new_cmd)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	ft_memset(new, 0, sizeof(t_cmd));
	new->inp = NO_INP;
	new->out = NO_OUT;
	*new_cmd = false;
	ft_cmd_add_back(cmd, new);
	*last = new;
}

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
			exit_with_failure(env, lst, NULL, NULL)
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

void	construct_cmds(t_cmd **cmd, t_lex **lst, t_env *env)
{
	t_lex	*lex;
	bool	new_cmd;
	t_cmd	*last;

	lex = *lst;
	new_cmd = true;
	g_glob.cmd = cmd;
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
}
