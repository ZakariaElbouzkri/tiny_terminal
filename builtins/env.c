/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asettar <asettar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 23:33:32 by asettar           #+#    #+#             */
/*   Updated: 2023/07/19 23:33:33 by asettar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	valid_identifer(char *s, int i)
{
	if (!ft_isalpha(s[0]) && s[0] != '_')
		return (0);
	if (!s[i] || s[i] == '=' || (s[i] == '+' && s[i + 1] == '='))
		return (1);
	if (!ft_isalnum(s[i]) && s[i] != '_')
		return (0);
	return (valid_identifer(s, i + 1));
}

int	ft_env(t_exec *exec, t_cmd *cmd)
{
	t_env	*env;

	env = *exec->env;
	if (cmd->args->next)
	{
		ft_put_error(1, "too much args");
		return (1);
	}
	while (env)
	{
		if (env->value && !env->hidden)
			printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
	return (0);
}
