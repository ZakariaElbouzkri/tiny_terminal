#include "minishell.h"
# include <readline/history.h>
# include <readline/readline.h>
// int main()
// {
// 	int fd = open("a",  O_CREAT | O_WRONLY | O_TRUNC);
// 	if (fd < 0)
// 	{
// 		perror("bash: a");
// 		exit(0);
// 	}
// 	// ft_putstr_fd("ach", fd);  
// }


	
void	sigint_handler()
{
	rl_replace_line("minishell$ ", "kkk");
	rl_redisplay();
	// prompt(env2);
}

int main()
{
	signal(SIGKILL, sigint_handler);
	while(1);
}