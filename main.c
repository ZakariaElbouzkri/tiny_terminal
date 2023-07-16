/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 11:53:40 by asettar           #+#    #+#             */
/*   Updated: 2023/07/16 00:40:21 by zel-bouz         ###   ########.fr       */
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
	return (true);
}

void	prompt(t_env **env)
{
	char	*cmd;

	while (true)
	{
		cmd = readline("\033[0;33m➜  minishell$ \033[0m");
		cmd = ft_strtrim(cmd, " \n\t\v\r");
		if (!cmd || !ft_strncmp("exit", cmd, 4))
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
	prompt(&env);
	free_env(&env);
}
