/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 04:12:12 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/07/15 00:45:54 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_cmd(char *cmd, char **path)
{
	int		idx;
	char 	*p;

	idx = -1;
	if (!access(cmd, X_OK))
		return (cmd);
	while (path[++idx])
	{
		p = ft_strjoin(ft_strdup(path[idx]), cmd);
		if (!access(p, X_OK))
			return (free(cmd), p);
		free(p);
		p = NULL;
	}
	return (NULL);
}

void	err_cmd_404(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found", 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

void	exec_cmd(t_cmd	*cmd, t_exec *exec)
{
	char	*command;

	if (!cmd->args)
		exit(0);
	command = cmd->cmd[0];
	cmd->cmd[0] = find_cmd(cmd->cmd[0], exec->path);
	if (!cmd->cmd[0])
		err_cmd_404(command);
	printf("cmd: %s\n", cmd->cmd[0]);
	printf("args: \n");
	for (int i = 1; cmd->cmd[i]; i++)
	{
		printf("\t%s\n", cmd->cmd[i]);
	}
	exit(0);
}

void	exec_pipes(t_exec *exec)
{
	pid_t	pid;
	t_cmd	*cmd;
	int		status;

	cmd = *exec->cmd;
	while (cmd)
	{
		pid = fork();
		if (pid == -1)
			ft_perror("minishell: ");
		if (pid == 0)
			exec_cmd(cmd, exec);
		cmd = cmd->next;
	}
	while ((pid = waitpid(-1, &status, 0)) > 0) {
        // if (WIFEXITED(status)) {
        //     printf("Child process %d exited with status %d\n", pid, WEXITSTATUS(status));
        // } else {
        //     printf("Child process %d terminated abnormally\n", pid);
        // }
    }
	// printf("___done:_____\n");
	(void)exec;
}
