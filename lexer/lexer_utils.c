/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 02:36:46 by asettar           #+#    #+#             */
/*   Updated: 2023/07/19 07:16:04 by zel-bouz         ###   ########.fr       */
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

// void	display_cmd(t_cmd *cmd)
// {
// 	char	*tok[9] = {"WRD", "SPA", "DQU", "SQU", "INP", "OUT", "HER", "APP", "PIP"};
// 	if(!cmd)
// 		return ;
// 	while (cmd)
// 	{
// 		printf("\nCOMMAND:--------------------------\n");
// 		t_list *lst = cmd->args;
// 		printf("  args: ");
// 		while (lst){
// 			printf("%s ", lst->content);
// 			lst=lst->next;
// 		}
// 		printf("\n  redirs:\n");
// 		t_redir *ls = cmd->redir;
// 		while (ls){
// 			printf("    type = %s  || file = %s\n", tok[ls->type], ls->file);
// 			ls = ls->next;
// 		}
// 		cmd = cmd->next;
// 	}
// }

// void	display_lexer(t_lex *lex)    
// {
// 	char	*tok[9] = {"WRD", "SPA", "DQU", "SQU", "INP", "OUT", "HER", "APP", "PIP"};
// 	while (lex)
// 	{
// 		printf("__________________________\n");
// 			printf("type : %s\n", tok[lex->tok]);
// 		if(lex->tok == WRD || lex->tok == SQU || lex->tok == DQU)
// 			printf("data : %s\n", lex->data);
// 		else
// 			printf("data : (null)\n");
// 		lex = lex->next;
// 	}
// }