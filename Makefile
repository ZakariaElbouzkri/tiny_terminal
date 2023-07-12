NAME = minishell

CC = cc -Wall -Wextra -Werror -g

LIBDIR = ./libft/
LIBFT = $(LIBDIR)/libft.a

RM = rm -f
SRC = main.c parse_env.c lexer/lexer.c  lexer/lexer_utils.c lexer/join_words.c lexer/expander.c \
		lexer/check_errors.c lexer/cmd_construct.c  builtins/echo.c builtins/export.c builtins/export2.c \
		exec/execute.c exec/init_redirections.c  

OBJ = $(SRC:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT) :
	make -C $(LIBDIR)

$(NAME) : $(OBJ) $(LIBFT)
	$(CC) -lreadline $^ -o $@

clean: 
	$(RM) $(OBJ)
	make -C $(LIBDIR) clean
fclean: clean 
	$(RM) $(NAME)
	make -C $(LIBDIR) fclean

re : fclean all


