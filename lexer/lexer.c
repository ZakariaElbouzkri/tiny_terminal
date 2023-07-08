#include "../minishell.h"

void	display_lexer(t_lex *lex)    
{
	char	*tok[10] = {"WRD", "SPA", "DQU", "SQU", "INP", "OUT", "HER", "APP", "PIP", NULL};
	while (lex)
	{
		printf("__________________________\n");
		printf("type : %s\n", tok[lex->tok]);
		if(lex->tok == WRD || lex->tok == SQU || lex->tok == DQU)
			printf("data : %s\n", lex->data);
		else
			printf("data : (null)\n");
		lex = lex->next;
	}
}

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
		i--;
	}
	*idx = i;
}

void	check_token_type(char *cmd, int *idx, t_lex *token)
{
	int	i;

	i = *idx;
	if (cmd[i] == '|')
		token->tok = PIP;
	else if (ft_isspace(cmd[i]))
	{
		while (cmd[i] && ft_isspace(cmd[i]))
			i++;
		*idx = i - 1;
		token->tok = SPA;
	}
	else if (cmd[i] == '<')
	{
		*idx += (cmd[i] == cmd[i + 1]);
		token->tok = (HER * (cmd[i] == cmd[i + 1]) + INP * (cmd[i] != cmd[i + 1]));
	}
	else if (cmd[i] == '>')
	{
		*idx += (cmd[i] == cmd[i + 1]);
		token->tok = (APP * (cmd[i] == cmd[i + 1]) + OUT * (cmd[i] != cmd[i + 1]));
	}
	else
		get_data(cmd, idx, token);
}

bool	lexer(char *cmd)
{
	int		i;
	t_lex	*lex;
	t_lex	*token;

	i = -1;
	lex = NULL;
	while (cmd[++i])
	{
		token = (t_lex *)malloc(sizeof(t_lex));
		token->next = NULL;
		check_token_type(cmd, &i, token);
		ft_lex_add_back(&lex, token);
		// printf("%s, %d \n", token->data, i);
	}
	join_words(&lex);
	display_lexer(lex);
	return (0);
}
