#include "../minishell.h"

void	display_lexer(t_lex *lex)    
{
	char	*tok[9] = {"WRD", "SPA", "DQU", "SQU", "INP", "OUT", "HER", "APP", "PIP"};
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
		token->tok = WRD;
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
		token->tok = WRD;
		check_token_type(cmd, &i, token);
		ft_lex_add_back(&lex, token);
		
		// printf("%s, %d \n", token->data, i);
	}
	// display_lexer(lex);
	ft_expander(&lex);
	printf("::::::\n");
	display_lexer(lex);
	join_words(&lex);
	if (check_errors(lex))
		return (free_lex(&lex), 1);
	free_lex(&lex);
	return (0);
}
