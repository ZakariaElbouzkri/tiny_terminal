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
// <<<<<<< HEAD÷÷
			char *s = tmp->data;
// =======
			// last->data = ft_strjoin(last->data, )
// >>>>>>> 665e99be42f6d619a61bccf44f7deec4a565bfdb
			tmp->data = ft_strjoin(last->data, tmp->data);
			free(tmp->data);
			tmp->tok = SQU;
// <<<<<<< HEAD
			free(s);
			// printf("|||%s \n", last->data);
// =======
// >>>>>>> 665e99be42f6d619a61bccf44f7deec4a565bfdb
			delete_last_node(lex, last);
		}
		last = tmp;
		tmp = tmp->next;
	}
	// display_lexer(*lex);
	remove_white_spaces(lex);
	// display_lexer(*lex);

}

// <<<<<<< HEAD

// ls a
// =======
void	lex_del_one(t_lex **lex, t_lex	*node)
{
	if (!lex || !*lex)
		return ;
	if ((*lex) == node)
	{
		node = (*lex)->next;
		free((*lex)->data);
		free(*lex);
		*lex = node;
		return ;
	}
	lex_del_one(&(*lex)->next, node);
}

void	join_words2(t_lex **lex)
{
	t_lex	*itr;

	itr = *lex;
	while (itr)
	{
		if (itr->next && (is_word(itr) && is_word(itr->next)))
		{
			itr->data = ft_strjoin(itr->data, itr->next->data);
			if (itr->tok != WRD || itr->next->tok != WRD)
				itr->tok = SQU;
			lex_del_one(lex, itr->next);
		}
		if (itr)
			itr = itr->next;
	}
}
// >>>>>>> 665e99be42f6d619a61bccf44f7deec4a565bfdb
