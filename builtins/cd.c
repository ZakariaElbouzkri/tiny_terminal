#include "../minishell.h"

t_env	*env_find(char *s, t_env *env)
{
	if (!env || !s)
		return (NULL);
	if (!strcmp(s, env->name))
		return (env);
	return (env_find(s, env->next));
}

void	change_pwd_oldpwd(t_env *env, char *new_path)
{
	t_env	*pwd;
	t_env	*old_pwd;

	if (!getcwd(new_path, 10000))
	{
		ft_put_error(4, "cd", "error retrieving current directory", "getcwd",
			"cannot access parent directories: No such file or directory");
		g_glob.status = 0;
	}
	pwd = env_find("PWD", env);
	old_pwd = env_find("OLDPWD", env);
	free(old_pwd->value);
	if (!pwd->value)
		old_pwd->value = ft_strdup("");
	else
		old_pwd->value = ft_strdup(pwd->value);
	free(pwd->value);
	pwd->value = ft_strdup(new_path);
	pwd->echo_val = 0;
	old_pwd->echo_val = 0;
}

int	ft_cd(t_exec *exec, t_cmd *cmd)
{
	t_env	*home;
	t_list	*args;
	char	new_path[10000];

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
	if (chdir(args->next->content) == -1)
	{
		ft_put_error(3, "cd", args->next->content, strerror(errno));
		g_glob.status = 1;
	}
	else
		change_pwd_oldpwd(*exec->env, new_path);
	return (g_glob.status);
}
