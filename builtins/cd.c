/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asettar <asettar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 23:33:26 by asettar           #+#    #+#             */
/*   Updated: 2023/07/19 23:33:27 by asettar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*env_find(char *s, t_env *env)
{
	if (!env || !s)
		return (NULL);
	if (!strcmp(s, env->name))
		return (env);
	return (env_find(s, env->next));
}
void	update_old_pwd(t_env **env, t_env *pwd, t_env *old_pwd)
{
	char	*value;

	if (!old_pwd)
	{
		if (!pwd)
			value = NULL;
		else
			value = pwd->value;
		
		old_pwd = ft_new_env(ft_strdup("OLDPWD"), ft_strdup(value));
		old_pwd->hidden = 1;
		ft_env_add_back(env, old_pwd);
	}
	else
	{
		free(old_pwd->value);
		if (!pwd)
			old_pwd->value = NULL;
		else
			old_pwd->value = ft_strdup(pwd->value);
	}
}

void	update_pwd(t_env **env , char *new_path, char *content, char *getcwd_ret)
{
	t_env	*pwd;

	pwd = env_find("PWD", *env);
	if (!pwd)
	{
		pwd = ft_new_env(ft_strdup("PWD"), ft_strdup(new_path));
		pwd->hidden = 0;
		ft_env_add_back(env, pwd);
	}
	else if (!getcwd_ret && !ft_strcmp(content, ".."))
	{
		pwd->value = ft_strjoin(pwd->value, "/..");
		free(g_glob.pwd);
		g_glob.pwd = ft_strdup(pwd->value);
	}
	else
	{
		free(pwd->value);
		free(g_glob.pwd);
		pwd->value = ft_strdup(new_path);
		g_glob.pwd = ft_strdup(new_path);
	}
}

void	change_pwd_oldpwd(t_env **env, char *content)
{
	char	new_path[PATH_MAX];
	t_env	*pwd;
	t_env	*old_pwd;
	char	*getcwd_ret;
	getcwd_ret = getcwd(new_path, PATH_MAX);
	if (!getcwd_ret)
	{
		ft_put_error(4, "cd", "error retrieving current directory", "getcwd",
			"cannot access parent directories: No such file or directory");
		g_glob.status = 0;
	}
	pwd = env_find("PWD", *env);
	old_pwd = env_find("OLDPWD", *env);
	update_old_pwd(env, pwd, old_pwd);
	update_pwd(env, new_path, content, getcwd_ret);
	
}

int	ft_cd(t_exec *exec, t_cmd *cmd)
{
	t_env	*home;
	t_list	*args;

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
		change_pwd_oldpwd(exec->env, args->next->content);
	return (g_glob.status);
}
