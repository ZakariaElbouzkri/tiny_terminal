/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asettar <asettar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 11:53:40 by asettar           #+#    #+#             */
/*   Updated: 2023/07/16 07:11:36 by asettar          ###   ########.fr       */
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
				return (false);
		}
		if (!cmd[i])
			break ;
	}
	g_status = 1;
	return (true);
}

void	sigint_handler(int sig)
{
	(void)sig;
	// rl_replace_line("", 0);
	// rl_redisplay();
	g_status = 1;
}
void	sigquit_handler(int sig)
{
	(void)sig;
}
void	prompt(t_env **env)
{
	char	*cmd;

	// signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	while (true)
	{
		cmd = readline("\033[0;33m➜  minishell$ \033[0m");
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

	(void)ac;
	(void)av;
	env = NULL;
	g_status = 0;
	parse_env(envp, &env);
	// display_env(env);
	t_env *PWD = env_find("PWD", env);
	t_env *OLDPWD = env_find("OLDPWD", env);
	t_env	*pwd =  (t_env *)malloc(sizeof(t_env));
	t_env	*oldpwd = (t_env *)malloc(sizeof(t_env));
	pwd->name = ft_strdup("pwd");
	pwd->value = ft_strdup(PWD->value);
	pwd->flag = 1;
	oldpwd->flag = 1;
	oldpwd->name = ft_strdup("oldpwd");
	oldpwd->value = ft_strdup(OLDPWD->value);
	prompt(&env);
	free_env(&env);
}
