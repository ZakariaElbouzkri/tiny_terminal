/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asettar <asettar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 02:31:55 by asettar           #+#    #+#             */
/*   Updated: 2023/07/24 05:31:19 by asettar          ###   ########.fr       */
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

void	lexer_helper(char *cmd, t_lex **lex)
{
	int		i;
	t_lex	*token;

	i = -1;
	while (cmd[++i])
	{
		token = (t_lex *)malloc(sizeof(t_lex));
		if (!token)
			exit_with_failure();
		token->next = NULL;
		token->tok = WRD;
		token->expanded = false;
		check_token_type(cmd, &i, token);
		ft_lex_add_back(lex, token);
	}
}

bool	lexer(char *cmd, t_env **env)
{
	t_lex	*lex;
	t_cmd	*cmds;

	lex = NULL;
	g_glob.lex = &lex;
	lexer_helper(cmd, &lex);
	ft_expander(lex, *env);
	join_words(&lex);
	if (check_errors(lex))
		return (free_lex(&lex), 1);
	cmds = NULL;
	g_glob.cmd = &cmds;
	construct_cmds(&cmds, &lex, *env);
	free_lex(&lex);
	execute(&cmds, env);
	return (free_cmd(&cmds), 0);
}
