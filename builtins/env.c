#include "../minishell.h"

void	print_env(t_env *env)
{
	if (!env)
		return ;
	if (!env->value)
		return (print_env(env->next));
	if (!env->flag)
		printf("%s=%s\n", env->name, env->value);
	print_env(env->next);
}
