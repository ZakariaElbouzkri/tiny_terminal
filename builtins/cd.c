#include "../minishell.h"

//int chdir(const char *path);
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

void	cd(t_cmd *cmd, t_env *env)
{
	if (cmd->args->next == NULL)
	{
		go_to_home(env);
		return ;
	}
}
