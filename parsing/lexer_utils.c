/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 02:36:46 by asettar           #+#    #+#             */
/*   Updated: 2023/07/20 05:09:30 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lex_add_back(t_lex **lex, t_lex *new)
{	
	if (!lex || !new)
		return ;
	if (*lex == NULL)
	{
		*lex = new;
		return ;
	}
	ft_lex_add_back(&(*lex)->next, new);
}

void	ft_cmd_add_back(t_cmd **cmd, t_cmd *new)
{	
	if (!cmd || !new)
		return ;
	if (*cmd == NULL)
	{
		*cmd = new;
		return ;
	}
	ft_cmd_add_back(&(*cmd)->next, new);
}

bool	is_token(char c)
{
	return (c == '>' || c == '<' || c == '|'
		|| c == '\'' || c == '\"' || ft_isspace(c));
}

bool	is_word(t_lex	*node)
{
	return (node->tok == WRD || node->tok == SQU || node->tok == DQU);
}

bool	is_redir(t_lex *node)
{
	return (node->tok == APP || node->tok == HER
		|| node->tok == OUT || node->tok == INP);
}
