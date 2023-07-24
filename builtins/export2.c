/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asettar <asettar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 23:33:39 by asettar           #+#    #+#             */
/*   Updated: 2023/07/24 02:52:18 by asettar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_create_env_node(char *s, char *before, char *after)
{
	t_env	*env_node;

	env_node = (t_env *)malloc(sizeof(t_env));
	if (!env_node)
		return (NULL);
	if (ft_strchr(s, '='))
	{
		env_node->name = ft_strdup(before);
		env_node->value = ft_strdup(after);
	}
	else
	{
		env_node->name = ft_strdup(s);
		env_node->value = NULL;
	}
	env_node->hidden = 0;
	env_node->next = NULL;
	return (env_node);
}

void	insert_node_env(char *s, char *before, char *after, t_env **env)
{
	t_env	*env_node;

	env_node = env_find(before, *env);
	if (env_node && ft_strchr(s, '='))
	{
		if (env_node->value == NULL)
			env_node->value = ft_strdup("");
		if (s[ft_strichr(s, '=') - 1] == '+')
			env_node->value = ft_strjoin(env_node->value, after);
		else
		{
			free(env_node->value);
			env_node->value = ft_strdup(after);
		}
	}
	else if (!env_node)
	{
		env_node = ft_create_env_node(s, before, after);
		ft_env_add_back(env, env_node);
	}
	env_node->hidden = 0;
}

void	export_args_hlp(char *s, t_env **env)
{
	int		idx;
	char	*before;
	char	*after;

	idx = ft_strichr(s, '=');
	before = ft_substr(s, 0, idx - (s[idx - 1] == '+'));
	after = ft_substr(s, idx + 1, ft_strlen(s) - idx - 1);
	insert_node_env(s, before, after, env);
	free(before);
	free(after);
}

void	export_args(t_list *args, t_env **env)
{
	char	*s;

	while (args)
	{
		s = (char *)args->content;
		if (!valid_identifer(s, 0))
		{
			ft_put_error(3, "export", s, "not a valid identifier");
			g_glob.status = 1;
		}
		else if (ft_strcmp("_", s))
			export_args_hlp(s, env);
		args = args->next;
	}
}
