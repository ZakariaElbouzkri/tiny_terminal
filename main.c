/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asettar <asettar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 11:53:40 by asettar           #+#    #+#             */
/*   Updated: 2023/07/24 05:03:24 by asettar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_qutes(char *cmd)
{
	int		i;
	char	c;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			c = cmd[i++];
			while (cmd[i] && cmd[i] != c)
				i++;
			if (cmd[i] != c)
				return (g_glob.status = 1, false);
		}
		if (!cmd[i])
			break ;
	}
	return (true);
}

void	sigint_handler(int sig)
{
	(void)sig;
	if (!g_glob.under_exec)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_glob.status = 1;
	}
}

void	prompt(t_env **env)
{
	char	*cmd;

	while (true)
	{
		g_glob.her = 0;
		g_glob.under_exec = 0;
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		cmd = readline("➜  minishell$ ");
		cmd = ft_strtrim(cmd, " \n\t\v\r");
		if (!cmd || !ft_strcmp("exit", cmd))
			return (ft_putstr_fd("exit\n", 1), free(cmd));
		if ((cmd && *cmd) && (!check_qutes(cmd) || lexer(cmd, env)))
			ft_put_error(1, " syntax error");
		add_history(cmd);
		free(cmd);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env;

	if (ac != 1)
	{
		ft_put_error(2, av[1], "No such file or directory");
		exit (127);
	}
	env = NULL;
	ft_memset(&g_glob, 0, sizeof(t_glob));
	rl_catch_signals = 0;
	g_glob.env = &env;
	parse_env(envp, &env);
	g_glob.pwd = ft_strdup(env_find("PWD", env)->value);
	if (!g_glob.pwd)
		exit_with_failure();
	prompt(&env);
	free_env(&env);
	free(g_glob.pwd);
}
