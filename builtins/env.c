#include "../minishell.h"

int	ft_env(t_exec *exec)
{
	t_env *env;

	env = *exec->env;
	if ((*exec->cmd)->args->next)
	{
		ft_put_error(1, "too much args");
		return (g_status = 1);
	}
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
	return (g_status = 0);
}
