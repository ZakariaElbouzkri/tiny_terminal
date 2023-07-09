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
			break;
	}
	return (true);
}

void	prompt(t_env **env)
{
	char	*cmd;

	while (true)
	{
		cmd = readline("minishell$ ");
		if (!cmd)
			exit(0);
		cmd = ft_strtrim(cmd, " \n\t\v\r");
		if (cmd && !ft_strncmp("exit", cmd, 4))
			exit(0);
		if ((cmd && *cmd) && (!check_qutes(cmd) || lexer(cmd, *env)))
			ft_putstr_fd("syn_err\n", 2);
		add_history(cmd);
		free(cmd);
	}
}
void leaks(){system("leaks minishell");}

int	main(int ac, char **av, char** envp)
{
	(void)av;
	(void)ac;
	t_env	*env;
	atexit(leaks);

	env = NULL;
	parse_env(envp, &env);
	prompt(&env);
	free_env(&env);
}
