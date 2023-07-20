/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 05:32:33 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/07/20 04:46:23 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	open_and_save(char *file, t_tok t, int *fd)
{
	*fd = open(file, O_RDWR | (t == APP || t == OUT) * O_CREAT
			| (t == OUT) * O_TRUNC | (t == APP) * O_APPEND, 0777);
	if (*fd == -1)
	{
		ft_put_error(2, file, strerror(errno));
		return (false);
	}
	return (true);
}

void	open_redirs(t_cmd *cmd)
{
	t_redir	*red;

	while (cmd)
	{
		red = cmd->redir;
		while (red)
		{
			if (red->type == INP || red->type == OUT || red->type == APP)
			{
				if (!open_and_save(red->file, red->type, &red->fd))
				{
					cmd->triger = -1;
					break ;
				}
			}
			red = red->next;
		}
		cmd = cmd->next;
	}
}
