/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 20:51:05 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/07/21 22:08:39 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	evlauate(char *nbr)
{
	int	ret;
	int	sign;

	if (!*nbr)
		return (1);
	sign = (*nbr == '-');
	if (sign)
		nbr++;
	ret = 0;
	while (*nbr)
	{
		if (!ft_isdigit(*nbr))
			return (1);
		ret *= 10;
		ret += (*nbr - 48);
		nbr++;
	}
	return ((!sign) * (ret + 1));
}

void	update_shell_level(t_env **env)
{
	t_env	*node;
	int		lvl;

	lvl = 1;
	node = env_find("SHLVL", *env);
	if (node)
		lvl = evlauate(node->value);
	ft_env_delete(env, node);
	ft_env_add_back(env, ft_new_env(ft_strdup("SHLVL"), ft_itoa(lvl)));
}
