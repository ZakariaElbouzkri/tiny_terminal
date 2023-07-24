/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asettar <asettar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 05:30:56 by asettar           #+#    #+#             */
/*   Updated: 2023/07/24 05:30:57 by asettar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_cmd(t_cmd	**cmd)
{
	t_redir	*red;
	t_redir	*tmp;

	if (!cmd || !*cmd)
		return ;
	free_cmd(&(*cmd)->next);
	if ((*cmd)->args)
	{
		ft_lstclear(&(*cmd)->args, free);
		free((*cmd)->cmd);
	}
	red = (*cmd)->redir;
	if (red)
	{
		while (red)
		{
			tmp = red;
			free(red->file);
			free(red);
			red = tmp->next;
		}
	}
	free(*cmd);
	*cmd = NULL;
}

void	free_lex(t_lex	**lex)
{
	if (!lex || !*lex)
		return ;
	free_lex(&(*lex)->next);
	if (is_word(*lex))
		free((*lex)->data);
	free(*lex);
	*lex = NULL;
}

void	lex_del_one(t_lex **lex, t_lex	*node)
{
	if (!lex || !*lex)
		return ;
	if ((*lex) == node)
	{
		node = (*lex)->next;
		free((*lex)->data);
		free(*lex);
		*lex = node;
		return ;
	}
	lex_del_one(&(*lex)->next, node);
}

void	free_env(t_env	**env)
{
	if (!env || !*env)
		return ;
	free_env(&(*env)->next);
	free((*env)->name);
	free((*env)->value);
	free(*env);
	*env = NULL;
}
