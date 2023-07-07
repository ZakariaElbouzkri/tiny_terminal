#include "minishell.h"

void	ft_env_add_back(t_env **env, t_env *node)
{
	if (!env || !node)
		return ;
	if (*env == NULL)
	{
		*env = node;
		return ;
	}
	ft_env_add_back(&(*env)->next, node);
}

void	parse_env(char **envp, t_env **env)
{
	int		i;
	int		idx;
	t_env	*node;

	i = -1;
	while (envp[++i])
	{

		idx = ft_strchr(envp[i], '=') - envp[i];
		node = malloc(sizeof(t_env));
		node->name = ft_substr(envp[i], 0, idx);
		node->value = ft_substr(envp[i], idx + 1, ft_strlen(envp[i]) - idx - 1);
		node->next = NULL;
		ft_env_add_back(env, node);
	}
}

void	display_env(t_env *env)
{
	if(!env)
		return;
	printf("%s = %s\n", env->name, env->value);
	display_env(env->next);
}

void	prompt(t_env *env)
{
	char	*cmd;

	while (true)
	{
		cmd = readline("minishell$ ");
		cmd = ft_strtrim(cmd, " \n\t\v\r");
		if (lexer(cmd))
		{
			ft_putstr_fd("syn_err\n", 2);
		}
		
	}
}

int	main(int ac, char **av, char** envp)
{
	(void)av;
	(void)ac;
	t_env	*env;

	env = NULL;
	parse_env(envp, &env);
	display_env(env);
	prompt(&env);
}