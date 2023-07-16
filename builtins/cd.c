#include "../minishell.h"

// int chdir(const char *path);
// path begins with a '/'
// return 0 for succes -1 for error and set errno

void	go_to_home(t_env *env)
{
	t_env	*home;
	t_env	*pwd;
	t_env	*oldpwd;
	
	char buff[1000];
	home = env_find("HOME", env);
	if (home->flag) // either removed r nothing set to it
	{
		ft_putstr_fd("bash: cd: HOME not set\n", 2);
		return ;
	}
	if (chdir(home->value) == -1)
	{
		perror("bash: cd ");
		return ;
	}
	oldpwd = env_find("OLDPWD", env);
	pwd =  env_find("PWD", env);
	oldpwd->value =pwd->value;
	pwd->value = getcwd(buff, 1000);
	printf("::%s::\n", pwd->value);
}

void	ft_cd(t_exec *exec, int p)
{
	t_env	*home;
	t_list	*args;
	char	*path;

	(void)p;
	args = (*exec->cmd)->args;
	if (!args->next)
	{
		home = env_find("HOME", *exec->env);
		if (!home)
		{
			ft_put_error(2, "cd", "HOME not set");
			g_status = 1;
		}
		else if (chdir(home->value) == -1)
		{
			ft_put_error(3, "cd", home->value, strerror(errno));
			g_status = 1;
		}
	}
	path = getcwd(NULL, 0);
	if (chdir(args->next->content) == -1)
	{
		g_status = 1;
		ft_put_error(2, "cd", strerror(errno));
	}

}
