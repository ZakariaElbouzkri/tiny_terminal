#include <unistd.h>
#include <stdio.h>
#include "minishell.h"
#include <string.h>

char	*ft_readline(char *prompt)
{
	ft_printf("%s", prompt);
	return (get_next_line(0));
}


int main()
{
	char *line = ft_readline("minishell$ ");
	printf("%s", line);
}