# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <stdbool.h>
# include "readline/readline.h"
# include "readline/history.h"
# include "libft/libft.h"
# include <sys/errno.h>
# include <signal.h>
#include <sys/ioctl.h>



void sig_int(int s)
{
	(void)s;
	printf("\n");
	rl_on_new_line("");
}

int main()
{
	char 	*l;

	signal(SIGINT, sig_int);
	while (1)
	{
		l = readline("propmt$ ");
		if (!l)
			return (0);
	}
}