NAME = minishell

CC = cc -Wall -Wextra -Werror -I/Users/zel-bouz/.brew/opt/readline/include -g

RDL = -lreadline -L/Users/zel-bouz/.brew/opt/readline/lib -lhistory 

LIBDIR = ./libft/
LIBFT = $(LIBDIR)/libft.a

RM = rm -f
SRC = main.c parse_env.c lexer/lexer.c  lexer/lexer_utils.c lexer/join_words.c lexer/expander.c \
		lexer/check_errors.c lexer/cmd_construct.c  builtins/echo.c builtins/export.c builtins/export2.c \
		exec/execute.c exec/exec_herdocs.c exec/exec_commands

OBJ = $(SRC:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT) :
	make -C $(LIBDIR)

$(NAME) : $(OBJ) $(LIBFT)
	$(CC) $(RDL) $^ -o $@

clean: 
	$(RM) $(OBJ)
	make -C $(LIBDIR) clean
fclean: clean 
	$(RM) $(NAME)
	make -C $(LIBDIR) fclean

re : fclean all


