/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 02:53:59 by asettar           #+#    #+#             */
/*   Updated: 2023/07/20 05:20:25 by zel-bouz         ###   ########.fr       */
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
# include "readline/readline.h"
# include "readline/history.h"
# include "libft/libft.h"
# include <sys/errno.h>
# include <sys/ioctl.h>

# define NO_INP -3
# define NO_OUT -3
# define FSIGNAL 128

typedef struct s_glob
{
	int	status;
	int	her;
	int	under_exec;
}		t_glob;

t_glob	g_glob;

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

typedef struct s_exec
{
	char	**path;
	char	**envp;
	t_cmd	**cmd;
	int		fd[2];
	t_env	**env;
}			t_exec;

// builtins :
int		ft_cd(t_exec *exec, t_cmd *cmd);
int		ft_echo(t_exec *exec, t_cmd *cmd);
int		ft_env(t_exec *exec, t_cmd *cmd);
int		ft_exit(t_exec *exec, t_cmd *cmd);
int		ft_export(t_exec *exec, t_cmd *cmd);
int		ft_pwd(t_exec *exec, t_cmd *cmd);
int		ft_unset(t_exec *exec, t_cmd *cmd);
void	construct_cmds(t_cmd **cmd, t_lex **lst);

// builtins -utils:
void	export_args(t_list *args, t_env **env);
bool	valid_identifer(char *s, int i);

// parsing :
void	parse_env(char **envp, t_env **env);
bool	lexer(char *cmd, t_env **env);
void	ft_expander(t_lex *lex, t_env *env);
void	join_words(t_lex **lex);
bool	check_errors(t_lex *lex);

// parsing utils:
void	ft_env_add_back(t_env **env, t_env *node);
void	ft_env_delete(t_env **env, t_env *node);
t_env	*env_find(char *s, t_env *env);
void	ft_lex_add_back(t_lex **lex, t_lex *new);
void	ft_cmd_add_back(t_cmd **cmd, t_cmd *new);
bool	is_token(char c);
bool	is_word(t_lex	*node);
bool	is_redir(t_lex *node);
char	*replace_dolar(char *data, t_env *env);
void	exec_builtins(t_exec *exec, t_cmd *node);

// execution:
void	execute(t_cmd	**cmd, t_env **env);
void	open_herdocs(t_cmd	*cmd, t_env *env);
void	exec_commands(t_cmd **cmd, t_env **env);
void	open_redirs(t_cmd *cmd);

// execution utils:
void	clear_and_exit(t_cmd **cmd, t_env **env);
bool	command_exist(char **cmd, char **path);
bool	is_builtin(char *s);
void	extract_args(t_cmd *cmd);
void	update_exit_status(int pid);
char	**extract_envp(t_env *env);
char	**get_path(t_env *env);
void	exec_pipes(t_exec *exec, int *pid, t_cmd *itr);
void	ft_dup2(int fdin, int fdout);
void	execute_child(t_exec *exec, t_cmd *itr);
void	send_to_exec(t_exec *exec, t_cmd	*node);
void	clear_and_exit_with_status(t_exec *exec, int status);
void	close_all_next_fds(t_cmd *itr);
void	free_dubptr(char **ptr);
void	ft_put_error(int n, ...);
void	free_cmd(t_cmd	**cmd);
void	free_env(t_env	**env);
char	*get_env(char *s, t_env *env);
void	init_child_signals(void);
void	ft_dup2(int fdin, int fdout);
void	sigint_handler(int sig);
bool	check_qutes(char *cmd);

#endif
