/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 03:50:27 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/07/15 21:57:02 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_path(t_env *env)
{
	char	**path;
	char	*p;
	int		idx;

	p = get_env(ft_strdup("PATH"), env);
	if (!p)
		return (NULL);
	path = ft_split(p, ':');
	idx = -1;
	while (path && path[++idx])
	{
		if (path[idx][ft_strlen(path[idx]) - 1] != '/')
			path[idx] = ft_strjoin(path[idx], "/");
	}
	return (path);
}

int	t_env_size(t_env *env)
{
	if (!env)
		return (0);
	return (!env->flag) + t_env_size(env->next);
}

char	**extract_envp(t_env *env)
{
	int		idx;
	int		len;
	char	**envp;
	char	*var;


	len = t_env_size(env);
	envp = ft_calloc(sizeof(char *), len + 1);
	idx = -1;
	while (env)
	{
		if (!env->flag)
		{
			var = ft_strjoin(ft_strdup(env->name), "=");
			envp[++idx] =  ft_strjoin(var, env->value);
		}
		env = env->next;
	}
	return (envp);
}
