#include "../minishell.h"

char	*ft_strrcat(char *s, char c)
{
	char *ret;
	int	i;

	ret = malloc(ft_strlen(s) + 2);
	i = -1;
	while (s[++i])
		ret[i] = s[i];
	ret[i++] = c;
	ret[i] = 0;
	free(s);
	return (ret);
}

void	ft_expander(t_lex **lex)
{
	char	*s;
	int		i;
	t_lex	*tmp;
	t_lex	*last;
	int		idx;

	tmp = *lex;
	last = NULL;
	while (tmp)
	{
		if (is_word(tmp) && last && is_word(last) && last->tok != WRD && !ft_strncmp(last->data, "$", ft_strlen(last->data)))
		{
			delete_last_node(lex, last);
			// continue;
		}
		last = tmp;
		if (tmp->tok == HER)
		{
			tmp = tmp->next;
			if (tmp && tmp->tok == SPA)
				tmp = tmp->next;
			while (tmp && is_word(tmp))
				tmp = tmp->next;
		}
		else if ((tmp->tok == WRD || tmp->tok == DQU) && ft_strchr(tmp->data, '$'))
		{
			i = -1;
			s = ft_strdup("");
			while (tmp->data[++i])
			{
				if (tmp->data[i] == '$')
				{
					idx = i + 1;
					while (tmp->data[idx] && tmp->data[idx] != '$')
						idx++;
					if (idx == i + 1)
						s = ft_strrcat(s, '$');
					else
					{
						printf("%s::%s\n", ft_substr(tmp->data, i + 1, idx - i - 1), s);
						s = ft_strjoin(s, getenv(ft_substr(tmp->data, i + 1, idx - i - 1)));

					}
					i = idx - 1;
				}
			}
			tmp->data = s;
			free(s);
			tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
}
// $$