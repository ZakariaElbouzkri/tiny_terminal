/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_words.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asettar <asettar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 02:39:46 by asettar           #+#    #+#             */
/*   Updated: 2023/07/10 02:42:15 by asettar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_white_spaces(t_lex **lex)
{
	if (!lex || !*lex)
		return ;
	if ((*lex)->tok == SPA)
	{
		free(*lex);
		*lex = (*lex)->next;
		remove_white_spaces(&(*lex));
	}
	else
		remove_white_spaces(&(*lex)->next);
}

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

void	join_words(t_lex **lex)
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
			continue ;
		}
		if (itr)
			itr = itr->next;
	}
	remove_white_spaces(lex);
}
