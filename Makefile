NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

READLINE_DIR = $(shell brew --prefix readline)
RDL = -L$(READLINE_DIR)/lib  -lreadline  
RDL_INC = -I$(READLINE_DIR)/include

INC = minishell.h libft/libft.h 

SRC = parsing/check_errors.c parsing/cmd_construct.c parsing/expander.c  parsing/parsing_utils.c\
	parsing/join_words.c parsing/lexer.c parsing/lexer_utils.c parsing/parse_env.c parsing/parsing_utils2.c\
	execution/exec_commands.c execution/exec_utils.c execution/exec_utils3.c execution/execute.c \
	execution/execute_pipes.c execution/open_herdocs.c execution/open_redirs.c execution/exec_utils4.c \
	builtins/cd.c builtins/echo.c builtins/env.c builtins/exit.c builtins/export.c \
	builtins/export2.c builtins/pwd.c builtins/unset.c  main.c 


OBJ = $(SRC:.c=.o)
LIBFT = libft/libft.a

all : $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	@$(CC) $(CFLAGS) $(RDL) $(RDL_INC)  $^ $(LIBFT) -o $@
	@echo "$@ created"

%.o : %.c $(INC)
	@$(CC) $(CFLAGS) $(RDL_INC)  -c $< -o $@

clean:
	@$(RM) $(OBJ)
	@make -C libft clean
	@echo	"object files removed"

fclean: clean
	@$(RM) $(NAME)
	@make -C libft fclean
	@echo	"$(NAME) removed"

re: fclean all

.PHONY: clean fclean all re 
