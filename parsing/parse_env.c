/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 11:52:53 by asettar           #+#    #+#             */
/*   Updated: 2023/07/20 05:06:15 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env_add_back(t_env **env, t_env *node)
{
	if (!env || !node)
		return ;
	if (*env == NULL)
	{
		*env = node;
		return ;
	}
	ft_env_add_back(&(*env)->next, node);
}

t_env	*ft_new_env(char *name, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	ft_memset(new, 0, sizeof(t_env));
	new->value = value;
	new->name = name;
	return (new);
}

void	update_pwds_shlvl(t_env **env)
{
	t_env	*shlvl;
	t_env	*last_cmd;
	t_env	*pwd;
	t_env	*path;

	ft_env_delete(env, env_find("PWD", *env));
	ft_env_delete(env, env_find("OLDPWD", *env));
	ft_env_add_back(env, ft_new_env(ft_strdup("PWD"), getcwd(NULL, 0)));
	ft_env_add_back(env, ft_new_env(ft_strdup("OLDPWD"), NULL));
	shlvl = env_find("SHLVL", *env);
	if (!shlvl)
		ft_env_add_back(env, ft_new_env(ft_strdup("SHLVL"), ft_strdup("1")));
	else
		shlvl->value = ft_itoa(ft_atoi(shlvl->value) + 1);
	pwd = env_find("PWD", *env);
	if (!env_find("_", *env))
	{
		ft_env_add_back(env , ft_new_env(ft_strdup("PATH"),
			ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.")));
		path = env_find("PATH", *env);
		path->hidden = 1;
		last_cmd = ft_new_env(ft_strdup("_"),
				ft_strdup("/usr/bin/env"));
		ft_env_add_back(env, last_cmd);
	}
}
void	parse_env(char **envp, t_env **env)
{
	int		i;
	int		idx;
	t_env	*node;

	i = -1;
	while (envp && envp[++i])
	{
		idx = ft_strchr(envp[i], '=') - envp[i];
		node = malloc(sizeof(t_env));
		node->name = ft_substr(envp[i], 0, idx);
		node->value = ft_substr(envp[i], idx + 1, ft_strlen(envp[i]) - idx - 1);
		node->hidden = 0;
		node->echo_val = 0;
		node->next = NULL;
		ft_env_add_back(env, node);
	}
	update_pwds_shlvl(env);
}

void	free_env(t_env	**env)
{
	if (!env || !*env)
		return ;
	free_env(&(*env)->next);
	free((*env)->name);
	free((*env)->value);
	free(*env);
	*env = NULL;
}
