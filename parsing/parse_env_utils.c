#include "../minishell.h"

void	free_env(t_env	**env)
{
	if (!env || !*env)
		return ;
	free_env(&(*env)->next);
	free((*env)->name);
	free((*env)->value);
	free(*env);
	*env = NULL;
}

void	ft_env_add_back(t_env **env, t_env *node)
{
	if (!env || !node)
		return ;
	if (*env == NULL)
	{
		*env = node;
		return ;
	}
	ft_env_add_back(&(*env)->next, node);
}

t_env	*ft_new_env(char *name, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	ft_memset(new, 0, sizeof(t_env));
	new->value = value;
	new->name = name;
	return (new);
}
