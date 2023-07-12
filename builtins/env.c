#include "../minishell.h"

void	print_env(t_env *env)
{
	if (!env)
		return ;
	if (!env->value)
		return (print_env(env->next));
	if (!env->flag)
	{
		ft_putstr_fd(env->name, 1);
		ft_putchar_fd('=', 1);
		ft_putstr_fd(env->value, 1);
		ft_putchar_fd('\n', 1);
	}
	print_env(env->next);
}
