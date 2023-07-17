#include "../minishell.h"



void	change_pwd_oldpwd(t_env *env, char *new_path)
{
	t_env *pwd;
	t_env *old_pwd;

	pwd = env_find("PWD", env);
	old_pwd = env_find("OLDPWD", env);
	free(old_pwd->value);
	if (!pwd->value)
		old_pwd->value = ft_strdup("");
	else
		old_pwd->value = ft_strdup(pwd->value);
	free(pwd->value);
	pwd->value = ft_strdup(new_path);

}

int	ft_cd(t_exec *exec, t_cmd *cmd)
{
	t_env	*home;
	t_list	*args;
	char	new_path[10000];
	// char	old_path[10000];

	(void)exec;
	args = cmd->args;
	if (!args->next)
	{
		home = env_find("HOME", *exec->env);
		if (!home)
		{
			ft_put_error(2, "cd", "HOME not set");
			return (1);
		}
		ft_lstadd_back(&(*exec->cmd)->args, ft_lstnew(ft_strdup(home->value)));
	}
	// getcwd(old_path, 10000);
	if (chdir(args->next->content) == -1)
	{
		ft_put_error(3, "cd", args->next->content, strerror(errno));
		g_status = 1;
	}
	else
	{
		// printf("hiii\n");
		if (!getcwd(new_path, 10000))
			ft_putstr_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
			// printf("%s\n", new_path);
		change_pwd_oldpwd(*exec->env, new_path);
	}
	return (g_status);
}
