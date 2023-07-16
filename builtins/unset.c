/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 00:46:07 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/07/16 01:16:26 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//recieve cmd->args->next  
void	ft_env_delete(t_env **env, t_env *node)
{
	if (!env || !*env)
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
bool valid_identifier_unset(char *s)
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
void	ft_unset(t_exec *exec, int p)
{
	t_env *node;
	char	*s;
	t_list	*args;
	
	args = (*exec->cmd)->args;
	while (args)
	{
		s = args->content;
		if (!valid_identifier_unset(s))
		{
			ft_put_error(3, "unset", s, "not a valid identifier");
			g_status = 1;
		}
		node = env_find(s, *exec->env);
		if (node)
			ft_env_delete(exec->env, node);
		args = args->next;
	}
	if (!p)
		exit (1);
}
