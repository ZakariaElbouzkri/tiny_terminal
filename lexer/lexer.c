#include "../minishell.h"


t_tok	check_token_type(char *cmd, int *idx)
{
	int	i;

	i = *idx;
	if (cmd[i] == '|')
		return (PIP);
	else if (ft_isspace(cmd[i]))
	{
		while (cmd[i] && ft_isspace(cmd[i]))
			i++;
		*idx = i - 1;
		return (SPA);
	}
	else if (cmd[i] == '<')
	{
		*idx += (cmd[i] == cmd[i + 1]);
		return (HER * (cmd[i] == cmd[i + 1]) + INP * (cmd[i] != cmd[i + 1]));
	}
	else if (cmd[i] == '>')
	{
		*idx += (cmd[i] == cmd[i + 1]);
		return (APP * (cmd[i] == cmd[i + 1]) + OUT * (cmd[i] != cmd[i + 1]));
	}
	else if (cmd[i] == '\'' || cmd[i] == '\"')
		return (SQU * (cmd[i] == '\'') + DQU * (cmd[i] == '\"'));
	else
		return WRD;
}

bool	lexer(char *cmd)
{
	int		i;
	t_lex	*lex;
	t_tok	token;
	t_lex	*node;

	i = -1;
	while (cmd[++i])
	{
		// token = check_token_type(cmd, &i);
		node = malloc(sizeof(cmd));
		node->tok = check_token_type(cmd, &i);

		node->data = 
		node->next = NULL;
	}
}
