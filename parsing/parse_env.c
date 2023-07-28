/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asettar <asettar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 11:52:53 by asettar           #+#    #+#             */
/*   Updated: 2023/07/28 00:43:14 by asettar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_shlvl(t_env **env)
{
	t_env	*shlvl;
	int		new_shlvl;

	shlvl = env_find("SHLVL", *env);
	if (!shlvl)
		ft_env_add_back(env, ft_new_env(ft_strdup("SHLVL"), ft_strdup("1")));
	else
	{
		new_shlvl = ft_atoi(shlvl->value);
		if (new_shlvl < 0)
			new_shlvl = -1;
		else if (new_shlvl >= 1000)
		{
			ft_putstr_fd("minishell: warning: shell level (", 2);
			ft_putnbr_fd(new_shlvl, 2);
			ft_putstr_fd(") too high, resetting to 1\n", 2);
			new_shlvl = 0;
		}
		if (new_shlvl == 999)
			shlvl->value = ft_strdup("");
		else
			shlvl->value = ft_itoa(new_shlvl + 1);
	}
}

void	update_last_cmd(t_env **env)
{
	t_env	*last_cmd;
	t_env	*path;

	if (!env_find("_", *env))
	{
		ft_env_add_back(env, ft_new_env(ft_strdup("PATH"),
				ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.")));
		path = env_find("PATH", *env);
		path->hidden = 1;
		last_cmd = ft_new_env(ft_strdup("_"), ft_strdup("./minishell"));
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
		if (!node)
			exit_with_failure();
		node->name = ft_substr(envp[i], 0, idx);
		node->value = ft_substr(envp[i], idx + 1, ft_strlen(envp[i]) - idx - 1);
		node->hidden = 0;
		node->next = NULL;
		ft_env_add_back(env, node);
	}
	ft_env_delete(env, env_find("PWD", *env));
	ft_env_delete(env, env_find("OLDPWD", *env));
	ft_env_add_back(env, ft_new_env(ft_strdup("PWD"), getcwd(NULL, 0)));
	ft_env_add_back(env, ft_new_env(ft_strdup("OLDPWD"), NULL));
	update_shlvl(env);
	update_last_cmd(env);
}
