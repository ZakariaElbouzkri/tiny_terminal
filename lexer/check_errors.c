/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 02:42:42 by asettar           #+#    #+#             */
/*   Updated: 2023/07/18 06:06:48 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_errors(t_lex *lex)
{
	t_lex	*last;

	if (!lex)
		return (0);
	if (lex->tok == PIP)
		return (1);
	last = NULL;
	while (lex)
	{
		if (is_redir(lex))
		{
			if (!lex->next || !is_word(lex->next))
				return (g_status = 1);
		}
		else if (lex->tok == PIP)
		{
			if (!lex->next || lex->next->tok == PIP)
				return (g_status = 1);
		}
		lex = lex->next;
	}
	return (0);
}
