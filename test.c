#include "minishell.h"

int main()
{
	int fd = open("a",  O_CREAT | O_WRONLY | O_TRUNC);
	if (fd < 0)
	{
		perror("bash: a");
		exit(0);
	}
	// ft_putstr_fd("ach", fd);
}