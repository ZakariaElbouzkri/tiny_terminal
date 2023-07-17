/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 02:46:18 by asettar           #+#    #+#             */
/*   Updated: 2023/07/17 04:45:54 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strrcat(char *s, char c)
{
	char	*ret;
	int		i;

	ret = malloc(ft_strlen(s) + 2);
	i = -1;
	while (s[++i])
		ret[i] = s[i];
	ret[i++] = c;
	ret[i] = 0;
	free(s);
	return (ret);
}

char	*exit_status(char *s)
{
	char	*ex;

	ex = ft_itoa(g_status);
	ex = ft_strjoin(ex, &s[1]);
	return (free(s), ex);
}

char	*get_env(char *s, t_env *env)
{
	if (!env)
		return (free(s), NULL);
	if (*s == '?')
		return (exit_status(s));
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

void	replace_dolar(t_lex *tmp, t_env *env)
{
	int		i;
	int		idx;
	char	*s;

	i = -1;
	s = ft_strdup("");
	while (tmp->data[++i])
	{
		if (tmp->data[i] == '$')
		{
			idx = i + 1;
			while (tmp->data[idx] && tmp->data[idx] != '$')
				idx++;
			if (idx == i + 1)
				s = ft_strrcat(s, '$');
			else
				s = ft_strjoin(s,
						get_env(ft_substr(tmp->data, i + 1, idx - i - 1), env));
			i = idx - 1;
		}
		else
			s = ft_strrcat(s, tmp->data[i]);
	}
	free(tmp->data);
	tmp->data = s;
}

void	ft_expander(t_lex **lex, t_env *env)
{
	t_lex	*tmp;
	t_lex	*last;

	tmp = *lex;
	last = NULL;
	while (tmp)
	{
		last = tmp;
		if (tmp->tok == HER)
		{
			tmp = tmp->next;
			if (tmp && tmp->tok == SPA)
				tmp = tmp->next;
			while (tmp && is_word(tmp))
				tmp = tmp->next;
		}
		else if ((tmp->tok == WRD || tmp->tok == DQU)
			&& ft_strchr(tmp->data, '$'))
		{
			replace_dolar(tmp, env);
			tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
}
