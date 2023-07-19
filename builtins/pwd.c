#include "../minishell.h"

int	ft_pwd(t_exec *exec, t_cmd *cmd)
{
	char	path[10000];

	(void)exec;
	(void)cmd;
	getcwd(path, 10000);
	printf("%s\n", path);
	return (0);
}
