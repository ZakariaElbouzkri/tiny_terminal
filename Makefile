NAME = minishell

CC = cc -Wall -Wextra -Werror -fsanitize=address

LIBDIR = ./libft/
LIBFT = $(LIBDIR)/libft.a

RM = rm -f

SRC = main.c 

OBJ = $(SRC:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT) :
	make -C $(LIBDIR)

$(NAME) : $(OBJ) $(LIBFT)
	$(CC) $^ -o $@

clean: 
	$(RM) $(OBJ)
	make -C $(LIBDIR) clean
fclean: clean 
	$(RM) $(NAME)
	make -C $(LIBDIR) fclean

re : fclean all


