NAME = minishell

CC = cc -Wall -Wextra -Werror

LIBDIR = ./libft/
LIBFT = $(LIBDIR)/libft.a

RM = rm -f

SRC = main.c lexer/lexer.c  lexer/lexer_utils.c lexer/join_words.c

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


