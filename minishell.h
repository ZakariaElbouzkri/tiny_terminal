/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asettar <asettar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 02:53:59 by asettar           #+#    #+#             */
/*   Updated: 2023/07/10 02:58:34 by asettar          ###   ########.fr       */
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
# include <readline/history.h>
# include <readline/readline.h>
# include "libft/libft.h"

typedef struct s_env
{
	char			*name;
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
	struct s_lex	*next;
	struct s_lex	*prev;
}	t_lex;

typedef struct s_redir
{
	t_tok			type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	t_list			*args;
	t_redir			*redir;
	int				fd[2];
	struct s_cmd	*next;
}	t_cmd;

void	parse_env(char **envp, t_env **env);
void	ft_env_add_back(t_env **env, t_env *node);
void	free_env(t_env	**env);
void	display_env(t_env *env);
void	display_lexer(t_lex *lex);
bool	lexer(char *cmd, t_env *env);
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

#endif
