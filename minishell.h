/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 02:53:59 by asettar           #+#    #+#             */
/*   Updated: 2023/07/18 05:30:07 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <stdbool.h>
#include "readline/readline.h"
#include "readline/history.h"
# include "libft/libft.h"
#include <sys/errno.h>

#define NO_INP -3
#define NO_OUT -3


int g_status;

typedef struct s_env
{
	char			*name;
	int				hidden;
	int				echo_val;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef enum e_tok
{
	WRD,
	SPA,
	DQU,
	SQU,
	INP,
	OUT,
	HER,
	APP,
	PIP,
}	t_tok;

typedef struct s_lex
{
	t_tok			tok;
	char			*data;
	bool			expanded;
	struct s_lex	*next;
}	t_lex;

typedef struct s_redir
{
	t_tok			type;
	char			*file;
	int				flag;
	int				fd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	t_list			*args;
	char			**cmd;
	t_redir			*redir;
	int				fd[2];
	int				inp;
	int				out;
	int				triger;
	struct s_cmd	*next;
}	t_cmd;

typedef	struct s_exec
{
	char	**path;
	char	**envp;
	t_cmd	**cmd;
	t_env	**env;
} t_exec;


void	parse_env(char **envp, t_env **env);
void	ft_env_add_back(t_env **env, t_env *node);
void	free_env(t_env	**env);
void	display_env(t_env *env);
void	display_lexer(t_lex *lex);
bool	lexer(char *cmd, t_env **env);
void	check_token_type(char *cmd, int *idx, t_lex *token);
void	ft_lex_add_back(t_lex **lex, t_lex *new);
bool	is_token(char c);
void	ft_expander(t_lex **lex, t_env *env);
void	replace_solar(t_lex *tmp, t_env *env);
void	join_words(t_lex **lex);
void	delete_last_node(t_lex **lst, t_lex *node_to_del);
bool	is_word(t_lex	*node);
char	*ft_strrcat(char *s, char c);
void	remove_white_spaces(t_lex **lex);
bool	check_errors(t_lex *lex);
bool	is_redir(t_lex *node);
void	construct_cmds(t_cmd **cmd, t_lex **lst);
void	ft_cmd_add_back(t_cmd **cmd, t_cmd *new);
void	create_new_cmd(t_cmd **cmd, t_cmd **last, bool *new_cmd);
void	change_last_args(t_lex *lex, t_cmd *last);
void	change_last_redir(t_lex **lst, t_cmd *last);
void	ft_redir_add_back(t_redir **red, t_redir *new);
void	free_cmd(t_cmd	**cmd);
void	display_cmd(t_cmd *cmd);
void	join_words2(t_lex **lex);

bool	valid_identifer(char *s, int i);

t_env	*env_find(char *s, t_env *env);

// buitins :
void	export_args(t_list *args, t_env **env);
int		ft_unset(t_exec *exec, t_cmd *cmd);
int		ft_export(t_exec *exec, t_cmd *cmd);
int		ft_pwd(t_exec *exec, t_cmd *cmd);
int		ft_env(t_exec *exec, t_cmd *cmd);
int		ft_echo(t_exec *exec, t_cmd *cmd);
int		ft_cd(t_exec *exec, t_cmd *cmd);
int		ft_exit(t_exec *exec, t_cmd *cmd);

char	*get_env(char *s, t_env *env);
void	init_redirections(t_cmd *cmd, t_env *env);
void	sigint_handler();
void	execute(t_cmd	**cmd, t_env **env);
void	ft_perror(char *err);
int		count_her(t_cmd *cmd, t_redir *redir);
void	exec_herdocs(t_cmd	*cmd, t_env *env);
void	exec_commands(t_cmd **cmd, t_env **env);
char	**get_path(t_env *env);
char	*find_cmd(char *cmd, char **path);
void	free_dubptr(char **ptr);

char	**get_path(t_env *env);
char	**extract_envp(t_env *env);
int		exec_pipes(t_exec *exec);
void	ft_put_error(int n, ...);
void	exec_cmd(t_cmd	*cmd, t_exec *exec);

// 
bool	command_exist(char **cmd, char **path);
bool	is_builtin(char *s);
void	ft_env_delete(t_env **env, t_env *node);
// int		exec_builtins(t_exec *exec);
char	*find_cmd(char *cmd, char **path);

#endif
