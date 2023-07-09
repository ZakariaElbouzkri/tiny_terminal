#include "../minishell.h"

void	ft_cmd_add_back(t_cmd **cmd, t_cmd *new)
{	
	if (!cmd || !new)
		return ;
	if (*cmd == NULL)
	{
		*cmd = new;
		return ;
	}
	ft_cmd_add_back(&(*cmd)->next, new);
}

void	ft_redir_add_back(t_redir **red, t_redir *new)
{	
	if (!red || !new)
		return ;
	if (*red == NULL)
	{
		*red = new;
		return ;
	}
	ft_redir_add_back(&(*red)->next, new);
}

void	create_new_cmd(t_cmd **cmd, t_cmd **last, bool *new_cmd)
{
	t_cmd	*new;
	
	new = (t_cmd *)malloc(sizeof(t_cmd));
	new->args = NULL;
	new->redir = NULL;
	new->next = NULL;
	*new_cmd = false;
	ft_cmd_add_back(cmd, new);
	*last = new;
}

void	change_last_args(t_lex *lex, t_cmd *last)
{
	t_list *node;

	node = (t_list *)malloc(sizeof(node));
	node->content = ft_strdup(lex->data);
	node->next = NULL;
	ft_lstadd_back(&last->args, node);
}

void	change_last_redir(t_lex **lst, t_cmd *last)
{
	t_lex	*lex;
	t_redir *red;
	
	lex = *lst;
	while (lex && is_redir(lex))
	{
		red = (t_redir *)malloc(sizeof(t_redir));
		red->type = lex->tok;
		red->file = ft_strdup(lex->next->data);
		red->next = NULL;
		ft_redir_add_back(&last->redir, red);
		*lst = lex->next;
		lex = lex->next->next;
	}
}

void	construct_cmds(t_cmd **cmd, t_lex **lst)
{
	t_lex	*lex;
	bool	new_cmd;
	t_cmd	*last;

	lex = *lst;
	new_cmd = true;
	while (lex)
	{
		if (new_cmd)
			create_new_cmd(cmd, &last, &new_cmd);
		if (is_word(lex))
			change_last_args(lex, last);
		else if (is_redir(lex))
			change_last_redir(&lex, last);
		if (lex && lex->tok == PIP)
			new_cmd = true;
		lex = lex->next;
	}
}