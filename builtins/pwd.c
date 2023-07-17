#include "../minishell.h"

// void	pwd(t_env *env, int p)
// {
// 	if (!env)
// 		return ;
// 	if (!ft_strncmp("PWD", env->name, ft_strlen(env->name)))
// 	{
// 		ft_putstr_fd(env->value, 1);
// 		return ;
// 	}
// 	pwd(env->next);
// }

int	ft_pwd(t_exec *exec, t_cmd *cmd)
{
	(void)exec;
	(void)cmd;

	char	path[10000];
	getcwd(path, 10000);
	printf("%s\n", path);
	return (0);
}
