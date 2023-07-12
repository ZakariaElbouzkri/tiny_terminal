/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 05:32:33 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/07/12 23:38:36 by zel-bouz         ###   ########.fr       */
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
	free(line);
	return (exp);
}

void	create_herdoc(t_redir *redir, t_env *env)
{
	int fd[2];
	int	pid;
	int	status;
	char	*line;

	if (pipe(fd) == -1)
		ft_perror("pipe");
	pid = fork();
	if (pid == -1)
		ft_perror("fork");
	if (!pid)
	{
		close(fd[0]);
		while (1)
		{
			line = readline("herdoc $> ");
			if (!line)
				exit(0);
			if (!ft_strcmp(line, redir->file))
			{
				free(line);
				exit(0);
			}
			line = ft_her_expander(line, redir->flag, env);
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
		}
		close(fd[1]);
		exit(1);
	}
	waitpid(pid, &status, 0);
	close(fd[1]);
	while (1)
	{
		line = get_next_line(fd[0]);
		if (!line)
			break;
		printf("%s", line);
		free(line);
	}
}

void	init_in_out(int *inp, int *out, t_redir *redir, t_env *env)
{
	t_redir *itr;

	itr = redir;
	(void)out;
	(void)inp;
	while (itr)
	{
		if (itr->type == HER)
			create_herdoc(redir, env);
		itr = itr->next;
	}
}

int	count_her(t_cmd *cmd, t_redir *redir)
{
	if (!redir)
	{
		if (!cmd->next)
			return (0);	
		return (count_her(cmd->next, cmd->next->redir));
	}
	return (redir->type == HER) + count_her(cmd, redir->next);
}

void	init_redirections(t_cmd *cmd, t_env *env)
{
	printf("her count :%d\n", count_her(cmd, cmd->redir));
	if (count_her(cmd, cmd->redir) >= 17)
	{
		free_cmd(&cmd);
		free_env(&env);
		ft_putstr_fd("bash: maximum here-document count exceeded\n", 2);
		exit(EXIT_FAILURE);
	}
	while (cmd)
	{
		if (cmd->redir)
			init_in_out(&cmd->inp, &cmd->out, cmd->redir, env);
		cmd = cmd->next;
	}
}