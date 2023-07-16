#include "../minishell.h"

// recieve in args args->next from execution 
// if not alnum char or start with number  --> unvalid

bool valid_identifer(char *s, int i)
{
	if (!ft_isalpha(s[0]) && s[0] != '_')
		return (0);
	if (!s[i] || s[i] == '=' || (s[i] == '+' && s[i + 1] == '='))
		return (1);
	if (!ft_isalnum(s[i]) && s[i] != '_')
		return (0);
	return (valid_identifer(s, i + 1));
}

t_env	*env_find(char *s, t_env *env)
{
	if (!env || !s)
		return (NULL);
	if (!strcmp(s, env->name))
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
	env_node->next = NULL;
	return (env_node);
}

void	insert_node_env(char *s, char *before, char *after, t_env **env)
{
	t_env	*env_node;
	
	env_node = env_find(before, *env);
	if (env_node && ft_strchr(s, '='))
	{
		if (env_node->value == NULL)
			env_node->value = ft_strdup("");
		if (s[ft_strichr(s, '=') - 1] == '+')
			env_node->value = ft_strjoin(env_node->value, after);
		else
		{
			free(env_node->value);
			env_node->value = ft_strdup(after);
		}
	}
	else if (!env_node)
	{
		env_node = ft_create_env_node(s, before, after);
		ft_env_add_back(env, env_node);
	}
}
void	check_env_args(char *s, t_env **env)
{
	int		idx;
	char	*before;
	char	*after;

	idx = ft_strichr(s, '=');
	before = ft_substr(s, 0, idx - (s[idx - 1] == '+'));
	after = ft_substr(s, idx + 1, ft_strlen(s) - idx - 1);
	insert_node_env(s, before, after, env);
	free(before);
	free(after);
}
int	export_args(t_list *args, t_env **env)
{
	char	*s;

	g_status = 0;
	while (args)
	{
		s = (char *)args->content;
		if (!valid_identifer(s, 0))
		{
			ft_put_error(3, "export", s, "not a valid identifier");
			g_status = 1;
		}
		else
			check_env_args(s, env);
		args = args->next;
	}
	return (g_status);
}

// ab
// 3 , 2 - 3 - 1 = 

