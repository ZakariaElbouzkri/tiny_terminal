/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 21:32:42 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/07/10 22:46:46 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void	free_dubptr(char **ptr)
{
	int idx;

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

char	**parse_path(t_env *env)
{
	char	*path;
	char	**spl_pth;
	int		idx;

	path = get_env(ft_strdup("PATH"), env);
	if (!path)
		return (NULL);
	spl_pth = ft_split(path, ':');
	if (!spl_pth || !*spl_pth)
		return (NULL);
	idx = -1;
	while (spl_pth[++idx])
	{
		if (spl_pth[idx][ft_strlen(spl_pth[idx]) - 1] != '/')
			spl_pth[idx] = ft_strjoin(spl_pth[idx], "/");
	}
	return (spl_pth);
}

void	execute(t_cmd	*cmd, t_env *env)
{
	char	**path;

	(void)cmd;
	path = parse_path(env);
}
