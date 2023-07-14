#include "../minishell.h"

// recieve in args args->next from execution 
// if not alnum char or start with number  --> unvalid

bool valid_identifer(char *s, int i)
{
	if (!ft_isalpha(s[0]) && s[0] != '_')
		return (0);
	if (!s[i] || s[i] == '=' || (s[i] == '+' && s[i + 1] == '='))
		return (1);
	if (!ft_isalnum(s[i]))
		return (0);
	return (valid_identifer(s, i + 1));
}

t_env	*env_find(char *s, t_env *env)
{
	if (!env || !s)
		return (NULL);
	if (env && env->name && ft_strlen(s) == ft_strlen(env->name) &&!strncmp(s, env->name, ft_strlen(s)))
		return (env);
	return (env_find(s, env->next));
}

t_env	*ft_create_env_node(char *s, char *before, char *after)
{
	t_env	*env_node;

	env_node = (t_env *)malloc(sizeof(t_env));
	if (ft_strchr(s, '='))
	{
		env_node->name = ft_strdup(before);
		env_node->value = ft_strdup(after);
	}
	else
	{
		env_node->name = ft_strdup(s);
		env_node->value = NULL;
	}
	env_node->flag = 0;
	env_node->next = NULL;
	return (env_node);
}

void	check_env_args(char *before, char *after, char *s, t_env **env)
{
	t_env	*env_node;
	int		idx;

	env_node = env_find(before, *env);
	idx = ft_strichr(s, '=');
	if (env_node && ft_strchr(s, '='))
	{
		if (s[idx - 1] == '+')
			env_node->value = ft_strjoin(env_node->value, after);
		else
		{
			free(env_node->value);
			env_node->value = ft_strdup(after);
		}
			
		env_node->flag = 0;
	}
	else if (!env_node)
	{
		env_node = ft_create_env_node(s, before, after);
		ft_env_add_back(env, env_node);
	}
	free(before);
	free(after);
	before = after = NULL;
}
void	export_args(t_list *args, t_env **env)
{
	char	*s;
	int idx;
	char *before;
	char *after;
	
	while (args)
	{
		s = (char *)args->content;
		if (!valid_identifer(s, 0))
		{
			ft_putstr_fd("bash: export: `", 2);
			ft_putstr_fd(s, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
		}
		else
		{
			idx = ft_strichr(s, '=');
			before = ft_substr(s, 0, idx - (s[idx - 1] == '+'));
			after = ft_substr(s, idx + 1, ft_strlen(s) - idx - 1);
			// if (after)
				printf(":::%s || %s:::\n", before, after);
			// else
			// 	printf(":::%s || :::\n", before);
			check_env_args(before, after, s, env);
		}
		args = args->next;
	}
}

// ab
// 3 , 2 - 3 - 1 = 
