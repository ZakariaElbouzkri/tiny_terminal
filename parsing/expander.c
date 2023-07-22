/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asettar <asettar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 02:46:18 by asettar           #+#    #+#             */
/*   Updated: 2023/07/21 01:05:35 by asettar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env(char *s, t_env *env)
{
	if (!env)
		return (free(s), NULL);
	while (env)
	{
		if (!ft_strcmp(s, env->name))
		{
			free(s);
			return (env->value);
		}
		env = env->next;
	}
	free(s);
	return (NULL);
}

void	ft_join_value(char *data, char **s, int *i, t_env *env)
{
	int	idx;

	idx = *i + 1;
	if (ft_isdigit(data[idx]))
	{
		*i = idx;
		return ;
	}
	while (data[idx]
		&& (ft_isalnum(data[idx]) || data[idx] == '_'))
			idx++;
	if (idx == *i + 1 && data[idx] == '$')
	{
		*s = ft_strjoin(*s, "PID");
		*i = idx;
		return ;
	}
	else if (idx == *i + 1)
		*s = ft_strrcat(*s, '$');
	else
		*s = ft_strjoin(*s,
				get_env(ft_substr(data, *i + 1, idx - (*i) - 1), env));
	*i = idx - 1;
}

char	*replace_dolar(char *data, t_env *env)
{
	int		i;
	char	*s;
	char	*ex;

	i = -1;
	s = ft_strdup("");
	while (data[++i])
	{
		if (data[i] == '$')
		{
			if (data[i + 1] == '?')
			{
				ex = ft_itoa(g_glob.status);
				s = ft_strjoin(s, ex);
				i++;
				free(ex);
			}
			else
				ft_join_value(data, &s, &i, env);
		}
		else
			s = ft_strrcat(s, data[i]);
	}
	free(data);
	return (s);
}

void	skip_herdoc_words(t_lex **lst)
{
	t_lex	*lex;

	lex = *lst;
	lex = lex->next;
	if (lex && lex->tok == SPA)
		lex = lex->next;
	while (lex && is_word(lex))
		lex = lex->next;
	*lst = lex;
}

void	ft_expander(t_lex *lex, t_env *env)
{
	t_lex	*last;

	last = NULL;
	while (lex)
	{
		last = lex;
		if (lex->tok == HER)
			skip_herdoc_words(&lex);
		else if ((lex->tok == WRD || lex->tok == DQU)
			&& ft_strchr(lex->data, '$'))
		{
			lex->expanded = true;
			lex->data = replace_dolar(lex->data, env);
			if (lex->tok == WRD && *lex->data
				&& lex->data[ft_strlen(lex->data) - 1] == '$'
				&& lex->next && lex->next->tok == DQU)
					lex->data = ft_strtrim(lex->data, "$");
			lex = lex->next;
		}
		else
			lex = lex->next;
	}
}
