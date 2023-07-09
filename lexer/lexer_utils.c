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

void	display_cmd(t_cmd *cmd)
{
	char	*tok[9] = {"WRD", "SPA", "DQU", "SQU", "INP", "OUT", "HER", "APP", "PIP"};
	if(!cmd)
		return ;
	while (cmd)
	{
		printf("\nCOMMAND:--------------------------\n");
		t_list *lst = cmd->args;
		printf("  args: ");
		while (lst){
			printf("%s ", lst->content);
			lst=lst->next;
		}
		printf("\n  redirs:\n");
		t_redir *ls = cmd->redir;
		while (ls){
			printf("    type = %s  || file = %s\n", tok[ls->type], ls->file);
			ls = ls->next;
		}
		cmd = cmd->next;
	}
}
