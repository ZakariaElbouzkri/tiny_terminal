#include "../minishell.h"

void	ft_env(t_exec *exec, int p)
{
	t_env *env;

	env = *exec->env;
	if ((*exec->cmd)->args->next)
	{
		ft_put_error(1, "too much args");
		g_status = 1;
		if (!p)
			exit(1);
		return ;
	}
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
	g_status = 0;
	if (!p)
		exit(0);
}
