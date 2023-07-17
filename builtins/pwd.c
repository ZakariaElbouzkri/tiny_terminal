// #include "../minishell.h"

// // void	pwd(t_env *env, int p)
// // {
// // 	if (!env)
// // 		return ;
// // 	if (!ft_strncmp("PWD", env->name, ft_strlen(env->name)))
// // 	{
// // 		ft_putstr_fd(env->value, 1);
// // 		return ;
// // 	}
// // 	pwd(env->next);
// // }

// int	ft_pwd(t_exec *exec)
// {
// 	char	*path;
// 	t_env	*env;

// 	// exec->env = ;
// 	if (path)
// 	{
// 		path = getcwd(NULL, 0);
// 		ft_putstr_fd(path, 1);
// 		ft_putstr_fd("\n", 1);
// 		free(path);
// 	}
// 	else
// 	{
// 		ft_put_error(2, "pwd", strerror(errno));
// 		g_status = 1;
// 		return (g_status);
// 	}
// 	ft_putstr_fd(path, 1);
// 	ft_putstr_fd("\n", 1);
// 	return (g_status = 0);
// // }

