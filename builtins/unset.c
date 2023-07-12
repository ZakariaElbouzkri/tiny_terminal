#include "../minishell.h"

//recieve cmd->args->next  
void	unset(t_list *args, t_env *env)
{
	t_env *node;

	if (!args)
		return ;
	node = env_find(args->content, env);
	if (node)
		node->flag = 2;
	unset(args->next, env);
}
