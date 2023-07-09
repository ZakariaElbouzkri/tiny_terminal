#include "../minishell.h"

void	delete_last_node(t_lex **lst, t_lex *node_to_del)
{
	t_lex* curr_node = *lst;
	t_lex* prev_node;

	prev_node = NULL;
	if (curr_node == node_to_del)
	{
		*lst = curr_node->next;
		// free(node_to_del->data);
		free(node_to_del);
		return;
	}
	while (curr_node != node_to_del)
	{
		prev_node = curr_node;
		curr_node = curr_node->next;
	}
	prev_node->next = curr_node->next;
	// free(node_to_del->data);
	free(node_to_del);
}

void	remove_white_spaces(t_lex **lex)
{
	t_lex	*tmp;
	t_lex	*prev;

	prev = *lex;
	tmp = *lex;
	while (tmp)
	{
		if (tmp->tok == SPA)
		{
			prev->next = tmp->next;
			free(tmp);
		}
		if (tmp->tok != SPA)
			prev = tmp;
		tmp = tmp->next;
	}
}

void	join_words(t_lex **lex)
{
	t_lex	*last;
	t_lex	*tmp;

	last = NULL;
	tmp = *lex;
	while(tmp)
	{
		if (last && is_word(tmp) && is_word(last))
		{
			tmp->data = ft_strjoin(last->data, tmp->data);
			tmp->tok = SQU;
			delete_last_node(lex, last);
		}
		last = tmp;
		tmp = tmp->next;
	}
	// display_lexer(*lex);
	// remove_white_spaces(lex);
	// display_lexer(*lex);

}