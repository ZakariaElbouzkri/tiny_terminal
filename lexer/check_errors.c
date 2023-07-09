#include "../minishell.h"

bool	check_errors(t_lex *lex)
{
	t_lex *last;

	last = NULL;
	if (!lex)
		return (0);
	if (lex->tok == PIP)
		return (1);
	while (lex)
	{
		if (is_redir(lex))
		{
			if (!lex->next || is_word(lex->next))
				return (1);
		}
		else if (lex->tok == PIP)
		{
			if (!lex->next || lex->next->tok == PIP)
				return (1);
		}
		lex = lex->next;
	}
	return (0);
}
