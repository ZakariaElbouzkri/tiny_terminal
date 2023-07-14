#include "../minishell.h"

//recieve cmd->args->next  
void	unset(t_list *args, t_env *env)
{
	t_env *node;

	if (!args)
		return ;
	if (!valid_identifer(args->content, 0))
	{
		ft_putstr_fd("bash: export: `", 2);
		ft_putstr_fd(args->content, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	node = env_find(args->content, env);
	if (node)
		node->flag = 2;
	unset(args->next, env);
}
