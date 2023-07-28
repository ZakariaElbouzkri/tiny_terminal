/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asettar <asettar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 19:59:37 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/07/28 00:39:00 by asettar          ###   ########.fr       */
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
	if (!new)
		exit_with_failure();
	ft_memset(new, 0, sizeof(t_env));
	new->value = value;
	new->name = name;
	return (new);
}

void	ft_redir_add_back(t_redir **red, t_redir *new)
{
	if (!red || !new)
		return ;
	if (*red == NULL)
	{
		*red = new;
		return ;
	}
	ft_redir_add_back(&(*red)->next, new);
}
