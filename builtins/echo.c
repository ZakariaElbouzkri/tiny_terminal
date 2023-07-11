#include "../minishell.h"

// APP >>  : write (O_CREAT | O_WRONLY | O_APP)
// >  : overwrite (O_CREAT | O_WRONLY | O_TRUNC)

bool check_n_flag(char *s)
{
	int i;

	if (!s || s[0] != '-')
		return (0);
	
	i = 0;
	while (s[++i])
	{
		if (s[i] != 'n')
			return (0);
	}
	return (1);
}

void	echo_cmds(t_list *args)
{
	bool	new_line;
	bool	next;

	new_line = true;
	next = true;
	args = args->next;
	while (args)
	{
		if (next && check_n_flag(args->content))
			new_line = false;
		else
		{
			ft_putstr_fd(args->content, 1);
			if (args->next)
				ft_putchar_fd(' ', 1);
			next = false;
		}
		args = args->next;
	}
	if (new_line)
		ft_putchar_fd('\n', 1);
}


void	pwd(t_env *env)
{
	while (env)
	{
		if (!ft_strncmp("PWD", env->name, ft_strlen(env->name)))
		{
			ft_putstr_fd(env->value, 1);
			return ;
		}
		env = env->next;
	}
}
// export a : crete 
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

