#include "../minishell.h"

int	ft_env(t_exec *exec, t_cmd *cmd)
{
	t_env *env;

	env = *exec->env;
	if (cmd->args->next)
	{
		ft_put_error(1, "too much args");
		return (1);
	}
	while (env)
	{
		if (env->value && !env->hidden)
			printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
	return (0);
}
