/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 02:31:55 by asettar           #+#    #+#             */
/*   Updated: 2023/07/17 04:38:58 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_data(char *cmd, int *idx, t_lex *token)
{
	int	i;

	i = *idx;
	if (cmd[i] == '\'' || cmd[i] == '\"')
	{
		token->tok = SQU * (cmd[i] == '\'') + DQU * (cmd[i] == '\"');
		token->data = ft_substr(cmd, i + 1,
				ft_strchr(cmd + i + 1, cmd[i]) - (cmd + i + 1));
		i = ft_strchr(cmd + i + 1, cmd[i]) - cmd;
	}
	else
	{
		while (cmd[i] && !is_token(cmd[i]))
			i++;
		token->data = ft_substr(cmd, *idx, i - *idx);
		token->tok = WRD;
		i--;
	}
	*idx = i;
}

void	check_token_type(char *cmd, int *idx, t_lex *tk)
{
	int	i;

	i = *idx;
	if (cmd[i] == '|')
		tk->tok = PIP;
	else if (ft_isspace(cmd[i]))
	{
		while (cmd[i] && ft_isspace(cmd[i]))
			i++;
		*idx = i - 1;
		tk->tok = SPA;
	}
	else if (cmd[i] == '<')
	{
		*idx += (cmd[i] == cmd[i + 1]);
		tk->tok = (HER * (cmd[i] == cmd[i + 1]) + INP * (cmd[i] != cmd[i + 1]));
	}
	else if (cmd[i] == '>')
	{
		*idx += (cmd[i] == cmd[i + 1]);
		tk->tok = (APP * (cmd[i] == cmd[i + 1]) + OUT * (cmd[i] != cmd[i + 1]));
	}
	else
		get_data(cmd, idx, tk);
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

bool	lexer(char *cmd, t_env **env)
{
	int		i;
	t_lex	*lex;
	t_lex	*token;
	t_cmd	*cmds;

	i = -1;
	lex = NULL;
	while (cmd[++i])
	{
		token = (t_lex *)malloc(sizeof(t_lex));
		token->next = NULL;
		token->tok = WRD;
		check_token_type(cmd, &i, token);
		ft_lex_add_back(&lex, token);
	}
	ft_expander(&lex, *env);
	join_words2(&lex);
	if (check_errors(lex))
		return (free_lex(&lex), 1);
	cmds = NULL;
	construct_cmds(&cmds, &lex);
	free_lex(&lex);
	execute(&cmds, env);
	return (free_cmd(&cmds), 0);
}
