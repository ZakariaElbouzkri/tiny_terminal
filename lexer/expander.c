#include "../minishell.h"

void	ft_expander(t_lex *lex)
{
	t_lex	*last;
	t_tok	last_tok;
	last = NULL;
	while (lex)
	{
		if (lex->tok == HER)
		{
			lex = lex->next;
			while (lex && is_word(lex))
				lex = lex->next;
		}
		else if (lex->tok == WRD || lex->tok == DQU && ft_strchr(lex->data, '$'))
		{

		}
		else
			lex = lex->next;
	}
}
