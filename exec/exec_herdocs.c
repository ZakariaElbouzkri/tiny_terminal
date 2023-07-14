/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_herdocs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 04:16:48 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/07/13 21:33:14 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_perror(char *err)
{
	perror(err);
	exit(EXIT_FAILURE);
}

char	*ft_her_expander(char *line, int flg, t_env *env)
{
	char	*exp;
	int 	idx;
	int		i;

	if (!flg || !ft_strchr(line, '$'))
		return (line);
	i = -1;
	exp = ft_strdup("");
	while (line[++i])
	{
		if (line[i] == '$')
		{
			idx = i + 1;
			while (line[idx] && line[idx] != '$')
				idx++;
			if (i == idx + 1)
				exp = ft_strrcat(exp, '$');
			else
				exp = ft_strjoin(exp, get_env(ft_substr(line, i + 1, idx - i - 1), env));
			i = idx - 1;
		}
		else
			exp = ft_strrcat(exp, line[i]);
	}
	return (free(line), exp);
}

char	*ft_readline(char *prompt)
{
	char	*line;

	ft_printf("%s", prompt);
	line = get_next_line(0);
	return (line);
}

int	create_herdoc(t_redir *redir, t_env *env)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		ft_perror("minishell: ");
	while (1)
	{
		line = readline("\033[0;36mherdoc $> \033[0m");
		if (!line || !ft_strcmp(line, redir->file))
			return (free(line), close(fd[1]), fd[0]);
		line = ft_her_expander(line, redir->flag, env);
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	return (close(fd[1]), fd[0]);
}


void	exec_herdocs(t_cmd	*cmd, t_env *env)
{
	int		tmp_fd;

	while (cmd)
	{
		cmd->her_fd = -1;
		cmd->her_pos = -1;
		tmp_fd = -1;
		while (cmd->redir)
		{
			if (cmd->redir->type == HER)
			{
				cmd->her_pos = cmd->redir->pos;
				tmp_fd = create_herdoc(cmd->redir, env);
				if (cmd->her_fd != -1)
					close(cmd->her_fd);
				cmd->her_fd = tmp_fd;
			}
			cmd->redir = cmd->redir->next;
		}
		cmd = cmd->next;
	}
}
