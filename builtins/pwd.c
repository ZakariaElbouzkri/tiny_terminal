#include "../minishell.h"

void	pwd(t_env *env)
{
	if (!env)
		return ;
	if (!ft_strncmp("PWD", env->name, ft_strlen(env->name)))
	{
		ft_putstr_fd(env->value, 1);
		return ;
	}
	pwd(env->next);
}
