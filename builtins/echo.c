#include "../minishell.h"

bool	check_n_flag(char *s)
{
	int	i;

	if (!s || s[0] != '-' || s[1] != 'n')
		return (0);
	i = 0;
	while (s[++i])
	{
		if (s[i] != 'n')
			return (0);
	}
	return (1);
}

void	ft_put_content(t_list *args)
{
	if (args->content)
	{
		ft_putstr_fd(args->content, 1);
		if (args->next)
			ft_putchar_fd(' ', 1);
	}
}

int	ft_echo(t_exec *exec, t_cmd *cmd)
{
	bool	new_line;
	bool	next;
	t_list	*args;

	new_line = true;
	next = true;
	args = cmd->args->next;
	(void)exec;
	while (args)
	{
		if (next && check_n_flag(args->content))
			new_line = false;
		else
		{
			ft_put_content(args);
			next = false;
		}
		args = args->next;
	}
	if (new_line)
		ft_putchar_fd('\n', 1);
	return (0);
}
