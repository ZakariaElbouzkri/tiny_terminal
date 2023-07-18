# include "../minishell.h"

void	ft_swap(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
void	sort_env(t_env *env)
{
	t_env	*tmp;
	char	*s;

	while (env)
	{
		tmp = env->next;
		while (tmp)
		{
			if (ft_strncmp(env->name, tmp->name, ft_strlen(tmp->name) + 1) > 0)
			{
				s = env->name;
				env->name = tmp->name;
				tmp->name = s;
				s = env->value;
				env->value = tmp->value;
				tmp->value = s;
				ft_swap(&env->hidden, &tmp->hidden);
			}
			tmp = tmp->next;
		}
		env = env->next;
	}
}

void	print_export(t_env *env)
{
	t_env	*sorted_env;
	t_env	*node;

	sorted_env = NULL;
	while (env)
	{
		node = (t_env *)malloc(sizeof(t_env));
		node->name = ft_strdup(env->name);
		node->hidden = env->hidden;
		node->value = ft_strdup(env->value);
		node->next = NULL;
		ft_env_add_back(&sorted_env, node);
		env = env->next;
	}
	sort_env(sorted_env);
	node = sorted_env;
	while (node)
	{
		if (!node->hidden)
		{
			printf("declare -x %s", node->name);
			if (node->value)
				printf("=\"%s\"", node->value);
			printf("\n");
		}
		node = node->next;
	}
	free_env(&sorted_env);
}
int	ft_export(t_exec *exec, t_cmd *cmd)
{
	if (!cmd->args->next)
		print_export(*exec->env);
	else
		export_args(cmd->args->next, exec->env);
	return (g_status);
}
