/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asettar <asettar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 07:30:00 by asettar           #+#    #+#             */
/*   Updated: 2023/07/24 07:30:30 by asettar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*env_find(char *s, t_env *env)
{
	if (!env || !s)
		return (NULL);
	if (!strcmp(s, env->name))
		return (env);
	return (env_find(s, env->next));
}

void	assign_new_content(t_list *args, char *new)
{
	free(args->content);
	args->content = new;
}
