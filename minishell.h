#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "libft/libft.h"
typedef	struct	s_env
{
	char	*name;
	char	*value;
	struct	s_env	*next;
}	t_env;

typedef enum e_tok
{
	WRD, SPA, DQU, SQU, 
	INP, OUT, HER, APP,
	PIP, 
} t_tok;

typedef struct s_lex
{
	t_tok	tok;
	char	*data;
	struct	s_lex	*next;
	struct	s_lex	*prev;
}	t_lex;

typedef	struct s_redir
{
	t_tok	type; // inp out her app
	char	*file;
	struct	s_redir	*next;
}	t_redir;


typedef	struct	s_cmd
{
	char	*cmd;
	char	**args;
	t_redir	*redir;
	int		fd[2];
	struct	s_cmd	*next;
}	t_cmd;



#endif
