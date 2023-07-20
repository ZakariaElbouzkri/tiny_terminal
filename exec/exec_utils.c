/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asettar <asettar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 03:50:27 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/07/19 23:49:43 by asettar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_dubptr(char **ptr)
{
	int	idx;

	if (!ptr)
		return ;
	idx = -1;
	while (ptr[++idx])
	{
		free(ptr[idx]);
		ptr[idx] = NULL;
	}
	free(ptr);
	ptr = NULL;
}

int	count_her(t_cmd *cmd, t_redir *redir)
{
	if (!redir)
	{
		if (!cmd->next)
			return (0);
		return (count_her(cmd->next, cmd->next->redir));
	}
	return ((redir->type == HER) + count_her(cmd, redir->next));
}

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
	return (1 + t_env_size(env->next));
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
		var = ft_strjoin(ft_strdup(env->name), "=");
		envp[++idx] = ft_strjoin(var, env->value);
		env = env->next;
	}
	return (envp);
}
