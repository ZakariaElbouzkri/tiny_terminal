/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asettar <asettar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 00:46:07 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/07/20 00:52:27 by asettar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env_delete(t_env **env, t_env *node)
{
	if (!env || !*env || !node)
		return ;
	if ((*env) == node)
	{
		node = (*env)->next;
		free((*env)->name);
		free((*env)->value);
		free(*env);
		*env = node;
		return ;
	}
	ft_env_delete(&(*env)->next, node);
}

bool	valid_identifier_unset(char *s)
{
	if (*s != '_' && !ft_isalpha(*s))
		return (0);
	s++;
	while (*s)
	{
		if (!ft_isalpha(*s) && !ft_isalnum(*s) && *s != '_')
			return (0);
		s++;
	}
	return (1);
}

int	ft_unset(t_exec *exec, t_cmd *cmd)
{
	t_env	*node;
	char	*s;
	t_list	*args;

	args = cmd->args->next;
	while (args)
	{
		s = args->content;
		if (!valid_identifier_unset(s))
		{
			ft_put_error(3, "unset", s, "not a valid identifier");
			g_glob.status = 1;
		}
		node = env_find(s, *exec->env);
		if (node && ft_strcmp("_", s))
			ft_env_delete(exec->env, node);
		args = args->next;
	}
	return (0);
}
